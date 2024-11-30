#include "Common.h"

#include "PrimitiveInput.h"
#include <string.h>
#include <stdio.h>

Mode getMode(void)
{
    printf(OPERATION_MENU);
    char buff[MAX_BUFFER_LENGTH + 2] = "";

    InputError er = inputString(buff);
    if (er != INPUT_OK && strlen(buff) == 1)
        return OP_ERROR;

    return buff[0];
}

int enterFile(char *filename)
{
    printf("Enter file with numbers: ");
    if (inputString(filename) != INPUT_OK)
    {
        printf("Error: input string\n");
        return -1;
    }

    {
        FILE *file = fopen(filename, "r");
        if (!file)
        {
            printf("File may not exist, creating...\n");
            file = fopen(filename, "w");

            if (!file)
            {
                printf("Error: file\n");
                return -1;
            }
            fclose(file);
            printf("File %s created\n", filename);
        }
        fclose(file);
    }
    return 0;
}