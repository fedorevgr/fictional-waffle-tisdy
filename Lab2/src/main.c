#include "include/Table.h"
#include "include/Car.h"
#include "include/Service.h"

void
pooling(void);

int
main(void)
{

    pooling();
    return 0;
}

char getOption(void)
{
    char opt[2] = "";

    if (inputString(opt, 1) == OK)
        return opt[0];
    else
        return 'e';
}

void
pooling(void)
{
    bool exit = false;
    char option;

    do
    {
        printf(SPLITTER);
        printf(MENU);
        printf("Enter option: ");
        option = getOption();
        printf(SPACES);
        printf(SPLITTER);
        switch (option)
        {
            case '1':iPrintTable();
                break;
            case '2':iAddCar();
                break;
            case '3':iDeleteCar();
                break;
            case '4':assert(0); // not implemented
                break;
            case '5':iFindFields();
                break;
            case 'r':iRead();
                break;
            case 's':iSave();
                break;
            case 'q':exit = true;
                break;
            case 'i':printf(FIND_INFO);
                printf(SORT_INFO);
                break;
            case 'S':assert(0); // not implemented
                break;
            default:printf("Illegal option\n");
        }
    }
    while (!exit);

}
