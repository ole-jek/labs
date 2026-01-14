#define _CRT_SECURE_NO_WARNINGS
#include "funcs.h"
#include "book.h"

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
