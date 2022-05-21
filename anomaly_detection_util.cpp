//
// Hod Amar and Ofek Avergil
//
#include <iostream>
#include "anomaly_detection_util.h"
#include <cmath>
/*
 * Returns avg of floats array.
 */
float avg(float *x, int size){
    float mu = 0;
    for (int i = 0; i < size; ++i) {
        mu += x[i];
    }
    return (mu / size);
}

/*
 * Returns avg of multiplication of 2 arrays (x,y).
 */

float averageDuplicate(float *x, float *y, int size){
    float mu = 0;
    for (int i = 0; i < size; ++i) {
        mu = mu + (x[i] * y[i]);
    }
    return (mu / size);
}

/*
 * returns the variance of X and Y.
 */

float var(float* x, int size){
    if (nullptr == x || size <= 0){
        ////add if size of x != size
        return 0;
    }
    float sum = 0;
    float mu = avg(x, size);
    for (int i = 0; i < size; ++i) {
        sum += pow((x[i] - mu), 2.0);
    }
    float var = (sum / size);
    return var;
}
/*
 * returns the covariance of X and Y.
 * by the formula:
 * 𝑐𝑜𝑣(𝑋, 𝑌) = 𝐸(𝑋𝑌) − 𝐸(𝑋)𝐸(𝑌) = 𝐸((𝑋 − 𝐸(𝑋))(𝑌 − 𝐸(𝑌)).
 */

float cov(float* x, float* y, int size) {
    float xy[size];
    for (int i = 0; i < size; ++i) {
        xy[i] = x[i] * y[i];
    }
    float avergXY = averageDuplicate(x, y, size);
    float avergX = avg(x, size);
    float avergY = avg(y, size);
    float covariance = avergXY - (avergX * avergY);
    return covariance;
}

/*
 * returns the Pearson correlation coefficient of X and Y.
 */

float pearson(float* x, float* y, int size){
    float sqrtVarX = sqrt(var(x, size));
    float sqrtVarY = sqrt(var(y, size));
    float covXY = cov(x, y, size);
return (covXY / (sqrtVarX * sqrtVarY));
}

/*
 * performs a linear regression and return s the line equation
 */

Line linear_reg(Point** points, int size){
    float a = 0 , b= 0 ;
    float arrX[size];
    float arrY[size];
    int i;
    for (i = 0; i < size; i++){
        arrX[i] = points[i]->x;
        arrY[i] = points[i]->y;
    }
    a = cov(arrX, arrY, size) / var(arrX, size);
    float avergX = avg(arrX, size);
    float avergY = avg(arrY, size);
    b = avergY - a * avergX;
    Line l1(a, b);
    return l1;
}
/*
 * returns the deviation between point p and the line equation of the points.
 */

float dev(Point p,Point** points, int size){
    Line l = linear_reg(points, size);
    return dev(p, l);
}

/*
 * returns the deviation between point p and the line.
 */

float dev(Point p,Line l){
    float y = p.y;
    float fx = l.a * p.x + l.b;
    if(fx > y){
        return fx-y;
    }
    return y - fx;
}



