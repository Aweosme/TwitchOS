#ifndef TWITCHOS_MATH_H
#define TWITCHOS_MATH_H

#define PI 3.14159265358979323846

#define E 2.7182818284590452354

//Raise a base number to an exponent power
double pow(double, double);

//Natural logarithm
double log(double);
//ln is an alias for log
#define ln log

//Logarithm in base 10
double log10(double);

//Logarithm in a certain base
double logbase(double, double);

//Sine
double sin(double);

//Cosine
double cos(double);

//Tangent
double tan(double);

//Maximum value
double max(double, double);

//Minimum value
double min(double, double);

//Round a number up
double ceil(double);

//Round a number down
double floor(double);

#endif
