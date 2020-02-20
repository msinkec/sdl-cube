
void transformPoint(double *point, double *tMatrix, double *result);
void multiplyTransMatrices(double *A, double *B, double *result);
void rotateY(double* matrix, double angle, double *result);
void rotateX(double *matrix, double angle, double *result);
void translate(double *matrix, double dx, double dy, double dz, double *result);
void project(double *matrix, double fov, double aspect, double near, double far, double* result);
void normalize(double* point, double* result);
void identityMatrix(double* result);
void printMatrix(double* matrix);
void printPoint(double* point);
