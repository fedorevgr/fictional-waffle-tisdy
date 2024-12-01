#include "HashService.h"

#include "IterCounters.h"
#include "Common.h"
#include "PrimitiveInput.h"

#include <stdio.h>

#include "HashMap/HashMapPrivate.h"
#include "HashMap/HashMapPublic.h"
#include "File.h"

void serviceHash(bool private)
{
    char filename[MAX_BUFFER_LENGTH + 2] = "";
    if (enterFile(filename) != 0)
        return;

    int *elements = nullptr;
    size_t elemAmount = readFile(filename, &elements);

    HashMapPrivate *hashMapPrivate = (private) ? hashPriMapInit(INIT_SIZE) : nullptr;
    HashMapPub *hashMapPublic = (private) ? nullptr : hashPubMapInit(INIT_SIZE);

    if (elements && elemAmount)
    {
        for (int I = 0; I < elemAmount; ++I)
            (private) ? hashPriMapAdd(&hashMapPrivate, elements[I]) : hashPubMapAdd(&hashMapPublic, elements[I]);

        free(elements);
    }

    Mode mode;
    HashMapRC error;
    int elemBuffer;
    size_t size;
    do
    {
        size = (private) ? hashPriSize(hashMapPrivate) : hashPubSize(hashMapPublic);
        printf("Current size: %lu bytes\n", size);
        mode = getMode();

        if (mode == ADD || mode == DELETE || mode == FIND)
        {
            long newElement;
            printf("Input element value: ");
            if (inputSigned(&newElement) != INPUT_OK)
            {
                printf("Illegal number\n");
                mode = OP_ERROR;
            }
            elemBuffer = (int) newElement;
        }

        counterGet();
        switch (mode)
        {
            case ADD:
                error = (private) ? hashPriMapAdd(&hashMapPrivate, elemBuffer) : hashPubMapAdd(&hashMapPublic, elemBuffer);
                printf("Compares: %d\n", counterGet());

                if (error == HM_EXISTS)
                    printf("Error: Element exists\n");

                break;
            case DELETE:
                error = (private) ? hashPriMapRemove(hashMapPrivate, elemBuffer) : hashPubMapRemove(hashMapPublic, elemBuffer);
                printf("Compares: %d\n", counterGet());

                if (error == HM_EMPTY)
                    printf("Error: No such element\n");

                break;
            case FIND:
                error = (private) ? hashPriMapIn(hashMapPrivate, elemBuffer) : hashPubMapIn(hashMapPublic, elemBuffer);
                printf("Compares: %d\n", counterGet());

                if (error == HM_EMPTY)
                    printf("Error: No such element\n");

                break;
            case PRINT:
                (private) ? hashPriPrint(hashMapPrivate) : hashPubPrint(hashMapPublic);
                break;
            case QUIT:printf("Quitting...\n");
                break;
            case OP_ERROR:printf("Error, try again...\n");
                break;
        }
    }
    while (mode != QUIT);
    (private) ? hashPriMapDestroy(hashMapPrivate) : hashPubMapDestroy(hashMapPublic);
}


