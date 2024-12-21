#include <math.h>
#include <stdio.h>

int main() {
    double angle = 90.0;  // Angle in degrees
    double radians = angle * (M_PI / 180.0);  // Convert angle to radians

    // Calculate sin, cos, and tan of the angle
    double sin_val = sin(radians);
    double cos_val = cos(radians);
    double tan_val = tan(radians);

    // Print results
    printf("sin(%.2f) = %.2f\n", angle, sin_val);
    printf("cos(%.2f) = %.2f\n", angle, cos_val);
    printf("tan(%.2f) = %.2f\n", angle, tan_val);

    return 0;
}