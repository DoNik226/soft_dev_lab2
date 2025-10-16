#include <stdio.h>

#include "myfunc.h"
#include "equation.h"

int main()
{
    double root1, root2;
    printf("Hello World!\n");
    equation(1, -1, 5, &root1, &root2);
    
    return myfunc(2);
}
