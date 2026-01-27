#include "other.h"

/*void swap_str(void* p1, void* p2) {
    char* temp = *(char**)p1;
    *(char**)p1 = *(char**)p2;
    *(char**)p2 = temp;
}*/

int cmp_str(const char* const* p1, const char* const* p2) {
    return strcmp(*p1, *p2);
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
    sort(arr, n, cmp_num<int>);
    printf("сортировка по возрастанию: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void sort_desc(int* arr, int n) {
    sort(arr, n, cmp_desc);
    printf("сортировка по убыванию: ");
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

