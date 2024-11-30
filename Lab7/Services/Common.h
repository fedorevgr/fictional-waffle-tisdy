#ifndef LAB7_SERVICES_COMMON_H
#define LAB7_SERVICES_COMMON_H

#define OPERATION_MENU "Actions:\n" \
                        "\ta - add\n" \
                        "\td - delete\n" \
                        "\tf - find\n" \
                        "\tp - print\n"  \
                        "\tq - quit\n" \
                        "-> "


typedef enum Operation_
{
    ADD = 'a',
    DELETE = 'd',
    FIND = 'f',
    PRINT = 'p',
    QUIT = 'q',
    OP_ERROR
} Mode;

Mode getMode(void);
int enterFile(char *filename);


#endif //LAB7_SERVICES_COMMON_H
