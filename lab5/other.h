#include <cstring>
//Прототипы используемых в данном задании функций:

void sort(char* pcFirst, int nNumber, int size,
     void (*Swap)(void*, void*), int (*Compare)(const void*, const void*) );

template <typename T> // если можно шаблоны то так можно место сэкономить сильно. если нет то ну просто две одинаковые функции будут 
//по функционалу но с разными типами
void swap_num(void* p1, void* p2) {
    T temp = *(T*)p1;
    *(T*)p1 = *(T*)p2;
    *(T*)p2 = temp;
}

double integrate(double (*func)(double), double down, double up, int amount);

template <typename T>
int cmp_num(const void* p1, const void* p2) {
    const T v1 = *(const T*)p1;
    const T v2 = *(const T*)p2;
    if (v1 > v2) {
        return 1;
    }
    else if (v1 < v2) {
        return -1;
    }
    else {
        return 0;
    }
}

int cmp_str(const void* p1, const void* p2);
void swap_str(void* p1, void* p2);

void print_max(int* arr, int n);
void print_min(int* arr, int n);
void sort_asc(int* arr, int n);
void sort_desc(int* arr, int n);
int cmp_desc(const void* a, const void* b);