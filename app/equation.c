#include <stdio.h>
#include <math.h>
#include <complex.h>

int equation(double a, double b, double c, double _Complex *root1, double _Complex *root2) {
    double d = b * b - 4.0 * a * c;
    double den = 2.0 * a;

    if (d > 0) {
        double r1 = (-b - sqrt(d)) / den;
        double r2 = (-b + sqrt(d)) / den;
        *root1 = r1 + 0.0*I;
        *root2 = r2 + 0.0*I;
        return 2;
    } else if (d == 0) {
        double r = -b / den;
        *root1 = r + 0.0*I;
        *root2 = r + 0.0*I;
        return 1;
    } else {
        *root1 = (-b + I * sqrt(-d)) / den;
        *root2 = (-b - I * sqrt(-d)) / den;
        return 0;
    }
}
