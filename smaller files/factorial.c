#include<stdio.h>

int factorial(int num)
{
    if(!num)
    {
        return 1;
    }
    return num * factorial(num - 1);
}

int main()
{
   int result = factorial(5);
   printf("%d", result);
}