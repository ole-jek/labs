#ifndef MATRIX_H // защита от повторного включения
#define MATRIX_H

typedef struct {
    double* data; // указатель на массив double в котором данные будем хранить "одномерно". 
    // обращаемся к элементам через (cols * i + j) - индекс элемента в строке i  и столбце j.
    int rows = 0;
    int cols = 0;
} Matrix;

void m_zero(Matrix* A, int m, int n);
void m_id(Matrix* A, int n);
void m_free(Matrix* A);
void m_copy(const Matrix* src, Matrix* dst);
int m_width(const Matrix* A);
int m_height(const Matrix* A);
double m_get(const Matrix* A, int i, int j);
void m_set(Matrix* A, int i, int j, double value);

int m_add(Matrix* A, const Matrix* B);
void m_neg(Matrix* A);
int m_mult(const Matrix* A, const Matrix* B, Matrix* dst);

#endif