

// This is the math library that contains all the functions needed to perform
// the numerical integration
//
// Theodore Ikehara Due: Jan 17, 2022
// CSE13s Assignment 2 Numerical integration
// This is the library of all the mathamatical functions inorder to compute the
// integration

#include "mathlib.h"

#include <stdio.h>

// Power function for the other functions
double power(double base, double raised) {
    double answer = base;

    // Considering if the base is 0, if base is zero always equal to 1

    if (raised == 0) {
        return 1;
    }

    // Iterating and multiplying the base until reached the raised amount

    for (int i = 1; i < raised; i++) {
        answer = answer * base;
    }

    return answer;
}

// This is a factorial function for the other functions
double facto(double num) {
    double answer = num;

    // This considers if you are taking the factorial of 0
    if (num == 0) {
        return 1;
    }

    // This is iterating and multiplying the numbers coming after for factorial
    for (int i = num - 1; i > 0; i--) {
        answer = answer * i;
    }

    return answer;
}

// This is the function that performs exponential functions
// This uses the psudo code provided in the lab man
// This is based off of the equation shown in the Design doc
double Exp(double x) {
    double trm = 1.0;
    double sum = trm;
    double k = 1;

    while (trm > EPSILON) {
        trm *= Abs(x) / k;
        sum += trm;
        k += 1;
    }

    if (x > 0) {
        return sum;
    } else {
        return 1 / sum;
    }
}

// This function takes a value x and computes the sin using the Taylor series as
// described in the design doc
// This is following the form of the formula as seen in the first and second
// parts of the Taylor series summation
double Sin(double x) {
    // This is k for the iteration of the summation
    int k = 0;
    // This is the -1^k part of the equation
    double first;
    // This is the numerator of the fraction
    double secondUp;
    // This is the denomenator of the fraction
    double secondDown;
    // final summation: combining everything
    double finalSum = 1;
    // the total answer
    double answer = 0;
    // the preivious
    double previous = 1.0;
    while (Abs(previous) > EPSILON) {
        // This is doing the individual parts of the summation (Taylor Series)
        first = power(-1, k);
        secondUp = power(x, (2 * k) + 1);
        secondDown = facto((2 * k) + 1);

        // This is the part where the summation is calculated
        finalSum = first * (secondUp / secondDown);

        // Here we sum together our answer and to the grand total
        answer = answer + finalSum;

        previous = finalSum;
        // Here we add to the iteration
        k++;
    }

    return answer;
}

// This function computes the cos of x using the Taylor series
// This uses the psudo code provided in the lab man very similar to the code
// seen above of sin
double Cos(double x) {
    // This is k for the iteration of the summation
    int k = 0;
    // This is the -1^k part of the equation
    double first;
    // This is the numerator of the fraction
    double secondUp;
    // This is the denomenator of the fraction
    double secondDown;
    // final summation: combining everything
    double finalSum = 1;
    // the total answer
    double answer = 0;
    // the preivious
    double previous = 1.0;
    while (Abs(previous) > EPSILON) {
        // This is doing the individual parts of the summation (Taylor Series)
        first = power(-1, k);
        secondUp = power(x, (2 * k));
        secondDown = facto((2 * k));

        // This is the part where the summation is calculated
        finalSum = first * (secondUp / secondDown);

        // Here we sum together our answer and to the grand total
        answer = answer + finalSum;

        previous = finalSum;
        // Here we add to the iteration
        k++;
    }

    return answer;
}

// This is the implementation of the square root function
// This is using the psudo code provided in the lab man
double Sqrt(double x) {
    double z = 0.0;
    double y = 1.0;

    while (Abs(y - z) > EPSILON) {
        z = y;
        y = 0.5 * (z + x / z);
    }

    return y;
}

// This is the log function using the psudo code in the lab man
double Log(double x) {
    double y = 1.0;
    double p = Exp(y);

    while (Abs(p - x) > EPSILON) {
        y = y + x / p - 1;
        p = Exp(y);
    }

    return y;
}

// integrating with Simpson's 1/3 Rule
// as shown in the lab man
double integrate(double (*f)(double), double a, double b, uint32_t n) {

    // integrating by finding the parts individually
    double aFunc = (*f)(a);
    double bFunc = (*f)(b);
    double abFunc = (*f)((a + b) / n) * 4;

    double answer = 0;

    answer = (b - a) / 6;

    return answer * (aFunc + bFunc + abFunc);
}
