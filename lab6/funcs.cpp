#define _CRT_SECURE_NO_WARNINGS
#include "funcs.h"
#include "book.h"
#include "library.h"

char* my_strdup(const char* str) {
	if (!str) {
		return nullptr;
	}
	char* res = new char[strlen(str) + 1];
	strcpy(res, str);
	return res;
}

void clearInputBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void sort(char* pcFirst, int nNumber, int size,
    void (*Swap)(void*, void*), int (*Compare)(const void*, const void*)) {
    for (int i = 1; i < nNumber; i++)
        for (int j = nNumber - 1; j >= i; j--)
        {
            char* pCurrent = pcFirst + j * size;
            char* pPrevious = pcFirst + (j - 1) * size;
            if ((*Compare)(pPrevious, pCurrent) > 0) {
                (*Swap)(pPrevious, pCurrent);
            }
        }
}

int cmp_books_multi(const void* p1, const void* p2) {
    const Book* b1 = (const Book*)p1;
    const Book* b2 = (const Book*)p2;

    for (int i = 0; i < sort_num; ++i) {
        int res = 0;
        if (sort_fields[i] == 1) {
            res = strcmp(b1->author, b2->author);
        }
        else if (sort_fields[i] == 2) {
            res = strcmp(b1->title, b2->title);
        }
        else if (sort_fields[i] == 3) {
            res = b1->year - b2->year; 
        }

        if (res != 0) {
            return res * sort_dirs[i]; // возвращаем результат, если нашли различие
        }
    }
    return 0; // книги идентичны по всем выбранным полям
}

void swap_book(void* p1, void* p2) {
    Book* b1 = (Book*)p1;
    Book* b2 = (Book*)p2;

    Book temp = *b1;
    *b1 = *b2;
    *b2 = temp;
}