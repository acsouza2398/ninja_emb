#include <stdio.h>

int calc(void)
{
    int buf[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int result = 0;
    int i;
 
    for (i = 0; i < 10; i++) {
        result += buf[i];
    }
    return result;
}
 
int main(void)
{
    int a = calc();
    printf(a);
    return 0;
}
