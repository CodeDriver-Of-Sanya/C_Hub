#include "Circulate.h"

Circulate* createEmptyCir()
{
    Circulate* cir = calloc(1, sizeof(Circulate));
    if (!cir)
    {
        printf("createEmptyCir calloc failed!\n");
        return NULL;
    }

    return cir;
}

Circulate* createByStr(const char* str)
{
    Circulate* cir = calloc(1, sizeof(Circulate));
    if (!cir)
    {
        printf("createByStr calloc failed!\n");
        return NULL;
    }

    int ret = sscanf(str, "%llu %d %s %s %s", &cir->readerID, &cir->bookNo, cir->borrowData, cir->returnData, cir->comment);
    if (ret <= 0)
    {
        printf("createByStr sscanf failed!\n");
        return NULL;
    }

    return cir;
}

void cir_print(Circulate* c)
{
    printf("%-8llu %-8d %-10s %-10s %s\n", c->readerID, c->bookNo, c->borrowData, c->returnData, c->comment);
}
