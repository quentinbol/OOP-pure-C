#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "objectTest/pos.h"

int main()
{
    Object *pos = __NEW__(MyPos);

    pos->callMethod(pos, "set_x", 10);
    printf("pos x: %d\n", __GET_FIELD__(pos, x));
    int x;
    pos->callMethod(pos, "get_x", &x);
    printf("pos x: %d\n", x);

    __DELETE__(pos);
    return 0;
}