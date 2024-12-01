#include "PrimitiveInput.h"
#include <stdio.h>

#include "Services/TreeService.h"
#include "Services/HashService.h"
#include "Services/StatsService.h"

#define MENU "Enter program \n" \
                "\tB - Build bin tree\n"             \
                "\tA - Build AVL tree\n"             \
                "\tO - Build open hash\n"          \
                "\tP - Build private hash\n"       \
                "\tS - Get statistics\n"           \
                "\tq - quit\n"                     \
                "-> "

typedef enum Program_
{
    BUILD_BIN_TREE = 'B',
    BUILD_AVL = 'A',
    BUILD_OPEN = 'O',
    BUILD_PRIVATE = 'P',
    STATS = 'S',
    EXIT_PROGRAM = 'q',
} Program;

Program
getProgram(void);

int
main(void)
{
    Program program;

    do
    {
        printf(MENU);
        program = getProgram();
        switch (program)
        {
            case BUILD_BIN_TREE:serviceTree(false);
                break;
            case BUILD_AVL:serviceTree(true);
                break;
            case BUILD_OPEN:serviceHash(false);
                break;
            case BUILD_PRIVATE:serviceHash(true);
                break;
            case STATS:
                serviceStatistics();
                break;
            case EXIT_PROGRAM:break;
            default:printf("ERROR: Unknown option\n");
        }
    }
    while (program != EXIT_PROGRAM);

    return 0;
}

#include <string.h>
Program
getProgram(void)
{
    char buff[MAX_BUFFER_LENGTH + 2] = "";

    InputError er = inputString(buff);
    if (er != INPUT_OK)
        return -1;
    if (strlen(buff) != 1)
        return -1;

    return buff[0];
}
