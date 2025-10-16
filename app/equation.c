#include <stdio.h>
#include <math.h>
#include <complex.h>

int equation(double a, double b, double c, double double *root1, double double *root2) {
    double d = b * b - 4 * a * c;

    if (d > 0) {
        *root1 = (-b + sqrt(d)) / (2 * a);
        *root2 = (-b - sqrt(d)) / (2 * a);
        printf("Два действительных корня:\n");
        printf("x1 = %.2lf\n", *root1);
        printf("x2 = %.2lf\n", *root2);
        return 2;
    } else if (d == 0) {
        *root1 = -b / (2 * a);
        *root2 = 0;
        printf("Один действительный корень:\n");
        printf("x = %.2lf\n", *root1);
        return 1;
    } else {
        *root1 = -b / (2 * a);     // Действительная часть
        *root2 = sqrt(-d) / (2 * a); // Мнимая часть
        printf("Комплексные корни:\n");
        printf("x1 = %.2lf + %.2lfi\n", *root1, *root2);
        printf("x2 = %.2lf - %.2lfi\n", *root1, *root2);
        return 0;
    }
}
