
typedef enum Program_
{
    BUILD,
    EXIT_PROGRAM,
    MEASURE_SORTS
} Program;

Program getProgram(void);

int
main(void)
{
    Program program;

    do
    {
        program = getProgram();
    }
    while (program != EXIT_PROGRAM);

    return 0;
}


