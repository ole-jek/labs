#include "other.h"
#include <cstring>
#include <cstdio>

void sort(char* pcFirst, int nNumber, int size,
     void (*Swap)(void*, void*), int (*Compare)(const void*, const void*) ) {
    for ( int i = 1; i < nNumber; i++ )
        for ( int j = nNumber - 1; j >= i; j-- )
        {
            char* pCurrent = pcFirst + j * size;
            char* pPrevious = pcFirst + ( j - 1 ) * size;
            if ((*Compare)(pPrevious, pCurrent) > 0) {
                (*Swap)(pPrevious, pCurrent);
            }
        }
}

void swap_str(void* p1, void* p2) {
    char* temp = *(char**)p1;
    *(char**)p1 = *(char**)p2;
    *(char**)p2 = temp;
}

int cmp_str(const void* p1, const void* p2) {
    const char* f_str = *(const char**)p1;
    const char* s_str = *(const char**)p2;
    return strcmp(f_str, s_str);
}

double integrate(double (*func)(double), double down, double up, int amount) {
    if (amount <= 0) {
        printf("Ошибка");
        return 0;
    }
    double integrate_sum = 0;
    double h = (up - down) / amount; // шаг интегрирования
    for (int i = 0; i < amount; ++i) {
        double x = down + h * i;
        integrate_sum += func(x);
    }

    return integrate_sum * h; // умножаем сумму высот на ширину шага
}

int cmp_desc(const void* a, const void* b) { 
    return cmp_num<int>(b, a); // меняем аргументы местами
} 

void print_max(int* arr, int n) {
    if (n <= 0) {
        return;
    }
    int max = arr[0];
    for (int i = 0; i < n; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    printf("максимальный элемент: %d\n", max);
}

void print_min(int* arr, int n) {
    if (n <= 0) {
        return;
    }
    int min = arr[0];
    for (int i = 0; i < n; ++i) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    printf("минимальный элемент: %d\n", min);
}

void sort_asc(int* arr, int n) {
    sort(reinterpret_cast<char*>(arr), n, sizeof(int), swap_num<int>, cmp_num<int>);
    printf("сортировка по возрастанию: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void sort_desc(int* arr, int n) {
    sort(reinterpret_cast<char*>(arr), n, sizeof(int), swap_num<int>, cmp_desc);
    printf("сортировка по убыванию: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

