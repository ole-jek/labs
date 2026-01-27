#ifndef OTHER_H
#define OTHER_H

#include <cstring>
#include <cstdio>
//Прототипы используемых в данном задании функций:
template <typename T>
void sort(T* arr, int nNum, int (*Compare)(const T*, const T*)) { // из-за того что уже на этапе сборки будет известен тип сортируемых элемнтов нам не нужен аргумент swap и переменная size
    for (int i = 0; i < nNum; ++i) {
        for (int j = nNum - 1; j > i; --j) {
            if (Compare(&arr[j - 1], &arr[j]) > 0) {
                T temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

/*template <typename T> // если можно шаблоны то так можно место сэкономить сильно. если нет то ну просто две одинаковые функции будут 
//по функционалу но с разными типами
void swap_num(void* p1, void* p2) {
    T temp = *(T*)p1;
    *(T*)p1 = *(T*)p2;
    *(T*)p2 = temp;
}
*/
double integrate(double (*func)(double), double down, double up, int amount);

template <typename T>
int cmp_num(const T* p1, const T* p2) {
    if (*p1 > *p2) {
        return 1;
    }
    else if (*p1 < *p2) {
        return -1;
    }
    else {
        return 0;
    }
}

template <typename T>
int cmp_desc(const T* a, const T* b) {
    return cmp_num<T>(b, a); // меняем аргументы местами
}

int cmp_str(const char* const* p1, const char* const* p2);
//void swap_str(void* p1, void* p2);

void print_max(int* arr, int n);
void print_min(int* arr, int n);
void sort_asc(int* arr, int n);
void sort_desc(int* arr, int n);
#endif