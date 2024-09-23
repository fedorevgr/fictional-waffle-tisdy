//
// Created by Fedor Evgr on 22/09/2024.
//

const char *getSpaces(char *str, int amount)
{
    for (int i = 0; i < amount; i++)
        str[i] = ' ';
    return str;
}
