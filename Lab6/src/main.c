#include "TreeOperationService.h"
#include <stdio.h>

typedef enum Program_
{
    BUILD_TREE = 'b',
    EXIT_PROGRAM = 'q',
    MEASURE_SORTS = 'm'
} Program;

Program getProgram(void);

int
main(void)
{
    Program program;

    do
    {
        printf("Enter program (b - init tree, q - exit, m - stats): ");
        program = getProgram();
        switch (program)
        {
            case BUILD_TREE:service();
                break;
            case EXIT_PROGRAM:printf("Quitting...");
                break;
            case MEASURE_SORTS: // todo do
                break;
        }
    }
    while (program != EXIT_PROGRAM);

    return 0;
}
#include "PrimitiveInput.h"
Program getProgram(void)
{
    char buff[MAX_BUFFER_LENGTH + 2] = "";

    InputError er = inputString(buff);
    if (er != INPUT_OK)
        return -1;

    return buff[0];
}
