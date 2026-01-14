#ifndef BOOK_H // защита от повторного включени€
#define BOOK_H

const int MAX_LENGTH = 40; // 40 дл€ нагл€дности позже в работе

typedef struct {
    char author[MAX_LENGTH];      // автор 
    char title[MAX_LENGTH];       // название 
    int year;          // год 
    double price;      // цена 
    char category[MAX_LENGTH];    // категори€
} Book;

void safeBookFill(char* buf, const char* text, int max_size);
void printBook(const Book& book);
void inputBook(Book* b);
void clearInputBuffer();

#endif