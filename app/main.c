#include <stdio.h>

#include "myfunc.h"
#include "equation.h"

int main()
{
    double root1, root2;
    int rootsCount;
    printf("Hello World!\n");
    equation(1, -1, 5, &root1, &root2);

    printf("x1 = %.2lf\n", root1);
    printf("x2 = %.2lf\n", root2);
    
    return myfunc(2);
}
