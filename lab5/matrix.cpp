#include "matrix.h"

void m_zero(Matrix* A, int m, int n) {
    A->rows = m;
    A->cols = n;
    A->data = new double[m * n];

    for (int i = 0; i < m * n; ++i) {
        A->data[i] = 0.0;
    }
}

void m_id(Matrix * A, int n) {
    A->rows = n;
    A->cols = n;
    A->data = new double[n * n];

    for (int i = 0; i < n; ++i) { // идем по строкам
        for (int j = 0; j < n; ++j) { // идем по столбцам
            // если индексы совпадают, ставим 1.0, иначе 0.0
            if (i == j) {
                A->data[i * n + j] = 1.0;
            }
            else {
                A->data[i * n + j] = 0.0;
            }
        }
    }
}

void m_free(Matrix* A) {
    delete[] A->data;
    A->data = nullptr;
}

void m_copy(const Matrix* src, Matrix* dst) {

    m_free(dst); // чистим память для той матрицы dst 

    dst->rows = src->rows;
    dst->cols = src->cols;

    int num_of_elements = src->rows * src->cols;
    dst->data = new double[num_of_elements]; // выделяем нужную память под копируемые элементы

    for (int i = 0; i < num_of_elements; ++i) {
        dst->data[i] = src->data[i]; // копируем элементы
    }
}

int m_width(const Matrix* A) {
    return A->cols; // выводим кол-во столбцов
}

int m_height(const Matrix* A) {
    return A->rows; // выводим кол-во строк
}

double m_get(const Matrix* A, int i, int j) {
    return A->data[i * A->cols + j]; // выводим элемент по формуле приведенной в заголовчном файле
}

void m_set(Matrix* A, int i, int j, double value) {
    A->data[i * A->cols + j] = value; // выводим элемент по формуле приведенной в заголовчном файле
}

int m_add(Matrix* A, const Matrix* B) {
    if (A->cols == B->cols && A->rows == B->rows) { // проверяем на возможность сложить
        for (int i = 0; i < A->rows * A->cols; ++i) {
            A->data[i] += B->data[i]; // удобнее складывать так как они лежат (то бишь одномерно)
        }
        return 0;
    }
    return 1;
}
void m_neg(Matrix* A) {
    for (int i = 0; i < A->cols * A->rows; ++i) {
        A->data[i] *= -1; // меняем знак у каждого элемента
    }
}

int m_mult(const Matrix* A, const Matrix* B, Matrix* dst) {
    if (A->cols == B->rows) {

        m_free(dst);

        dst->rows = A->rows;
        dst->cols = B->cols;
        dst->data = new double[dst->rows * dst->cols];

        for (int i = 0; i < A->rows; ++i) { // идем по строкам A
            for (int j = 0; j < B->cols; ++j) { // идем по столбцам B
                double sum = 0;
                for (int k = 0; k < A->cols; ++k) { // формула: dst[i][j] = SIGMA(from k = 1 to A->cols) A[i][k] * B[k][j].
                    // ну короче просто формула умножения матриц я не знаю как ее по человечески в строку записать
                    sum += A->data[i * A->cols + k] * B->data[k * B->cols + j];
                }
                dst->data[i * dst->cols + j] = sum;
            }
        }
        return 0;
    }
    return 1;
}