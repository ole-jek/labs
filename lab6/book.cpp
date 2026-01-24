#define _CRT_SECURE_NO_WARNINGS
#include "book.h"


Book* createBook() {
	Book* new_book = new Book();
	return new_book;
}

void freeBookContent(Book* b) {
    if (b != nullptr) {
        delete[] b->author;  
        b->author = nullptr;
        delete[] b->title;   
        b->title = nullptr;
        delete[] b->genre;   
        b->genre = nullptr;
        delete[] b->summary; 
        b->summary = nullptr;

    }
}
void freeBook(Book* b) {
    if (b != nullptr) {
        freeBookContent(b);
        delete b;
    }
}

void inputBook(Book* b) {
    char buffer[2048] = { 0 }; // буфер для чтения строки
    printf("введите данные о книге:\n");

    printf("автор: ");
    if (scanf(" %2047[^\n]", buffer) != 1) { // как и в одной из прошлых лаб используем [^\n] чтобы считать имя целиком а не до пробела
        printf("ошибка ввода");
        clearInputBuffer();
        return;
    }
    b->author = new char[strlen(buffer) + 1]; // выделяем память ровно под размер текста + \0
    strcpy(b->author, buffer);
    clearInputBuffer();

    printf("название: ");
    if (scanf(" %2047[^\n]", buffer) != 1) { 
        printf("ошибка ввода");
        clearInputBuffer();
        return;
    }
    b->title = new char[strlen(buffer) + 1];
    strcpy(b->title, buffer);
    clearInputBuffer();

    while (1) {
        printf("год издания (не ранее 868 г. до 2026 г.): "); // оставим логику такой же какой она была в прошлой лабораторной. 
        if (scanf("%d", &b->year) != 1) {
            printf("ошибка! введите число.\n");

        }
        else if (b->year < 868 || b->year > 2026) {
            printf("ошибка: некорректный год.\n");
        }
        else {
            clearInputBuffer();
            break;
        }
        clearInputBuffer();
    }

    printf("жанр: ");
    if (scanf(" %2047[^\n]", buffer) != 1) {
        printf("ошибка ввода");
        clearInputBuffer();
        return;
    }
    b->genre = new char[strlen(buffer) + 1];
    strcpy(b->genre, buffer);
    clearInputBuffer();

    printf("краткое описание: ");
    if (scanf(" %2047[^\n]", buffer) != 1) { 
        printf("ошибка ввода");
        clearInputBuffer();
        return;
    }
    b->summary = new char[strlen(buffer) + 1];
    strcpy(b->summary, buffer);
    clearInputBuffer();
}

void printBook(Book* b) {
    if (b == nullptr) {
        printf("ошибка: указатель на книгу пуст.\n");
        return;
    }

    printf("----информация о книге----\n");

    // используем тернарный оператор, чтобы вместо падения программы 
    // при пустом указателе выводить текст "не указано"
    printf("автор: %s\n", (b->author ? b->author : "не указано"));
    printf("название: %s\n", (b->title ? b->title : "не указано"));
    printf("год: %d\n", b->year);
    printf("жанр: %s\n", (b->genre ? b->genre : "не указано"));
    printf("аннотация: %s\n", (b->summary ? b->summary : "не указано"));
    printf("--------------------------\n");
}