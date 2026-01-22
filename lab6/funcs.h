#ifndef FUNCS_H
#define FUNCS_H
#include <cstring>
#include <cstdio>

char* my_strdup(const char* str);
void clearInputBuffer();
void sort(char* pcFirst, int nNumber, int size, void (*Swap)(void*, void*), int (*Compare)(const void*, const void*));
int cmp_books_multi(const void* p1, const void* p2);
void swap_book(void* p1, void* p2);
#endif