#include <stdio.h>
#include <math.h>

#include "matrix.h"

void transformPoint(double *point, double *tMatrix, double *result) {
    for (int i = 0; i < 4; i++) {
        result[i] = 0;
        for (int j = 0; j < 4; j++) {
            result[i] += tMatrix[i*4+j] * point[j];
        }
    }
}

void multiplyTransMatrices(double *A, double *B, double *result) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i*4+j] = 0;
            for (int k = 0; k < 4; k++) {
                result[i*4+j] += A[i*4+k] * B[k*4+j];
            }
        }
    }
}

void rotateY(double *matrix, double angle, double *result) {
    double rotMat[16];
    identityMatrix(rotMat);

    rotMat[0] = cos(angle);
    rotMat[2] = sin(angle);
    rotMat[8] = -sin(angle);
    rotMat[10] = cos(angle);

    multiplyTransMatrices(rotMat, matrix, result);
}

void rotateX(double *matrix, double angle, double *result) {
    double rotMat[16];
    identityMatrix(rotMat);

    rotMat[5] = cos(angle);
    rotMat[6] = -sin(angle);
    rotMat[9] = sin(angle);
    rotMat[10] = cos(angle);

    multiplyTransMatrices(rotMat, matrix, result);
}

void translate(double *matrix, double dx, double dy, double dz, double *result) {
    double transMat[16];
    identityMatrix(transMat);

    transMat[3] = dx;
    transMat[7] = dy;
    transMat[11] = dz;

    multiplyTransMatrices(transMat, matrix, result);
}

void project(double *matrix, double fov, double aspect, double near, double far, double* result) {
    double yScale = 1.0 / tan(fov / 2.0);
    double xScale = yScale * aspect;

    double m[16];
    identityMatrix(m);
    m[0] = xScale;
    m[5] = yScale;
    m[10] = far / (far - near);
    m[11] = 1.0;
    m[14] = (-far*near) / (far - near);
    m[15] = 0.0;

    multiplyTransMatrices(m, matrix, result);
}

void normalize(double* point, double* result) {
    for (int i = 0; i < 3; i++) {
        result[i] = point[i] / point[3];
    }
    result[3] = 1.0;
}


void identityMatrix(double *result) {
    for (int i = 0; i < 16; i++) {
        if (i % 5 == 0) {
            result[i] = 1;
        } else {
            result[i] = 0;
        }
    }
}

void printMatrix(double *matrix) {
    for (int i = 0; i < 16; i++) {
        printf("%f ", matrix[i]);
        if ((i+1) % 4 == 0) {
            printf("\n");
        }
    }
}

void printPoint(double *point) {
    for (int i = 0; i < 4; i++) {
        printf("%f ", point[i]);
    }
    printf("\n");
}
