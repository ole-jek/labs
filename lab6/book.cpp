#define _CRT_SECURE_NO_WARNINGS
#include "book.h"

inline const int GLOBAL_MAX_YEAR = getCurrentYear();

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

    while (1) {
        printf("автор (макс. 2047 символов): ");

        if (scanf(" %2047[^\n]", buffer) == 1) {
            int next_char = getchar();

            if (next_char != '\n' && next_char != EOF) {
                while (next_char != '\n' && next_char != EOF) {
                    next_char = getchar();
                }

                printf("данные были обрезаны под лимит буфера.\n");
                printf("1 - ввести заново, 2 - оставить как есть: ");

                int choice;
                if (scanf("%d", &choice) == 1) {
                    clearInputBuffer();
                    if (choice == 1) {
                        continue;
                    }
                }
                else {
                    clearInputBuffer();
                }
            }
            b->author = my_strdup(buffer);
            break;
        }
        else {
            printf("ошибка ввода. попробуйте еще раз.\n");
            clearInputBuffer();
        }
    }

    while (1) {
        printf("название (макс. 2047 символов): ");

        if (scanf(" %2047[^\n]", buffer) == 1) {
            int next_char = getchar();

            if (next_char != '\n' && next_char != EOF) {
                while (next_char != '\n' && next_char != EOF) {
                    next_char = getchar();
                }

                printf("данные были обрезаны под лимит буфера.\n");
                printf("1 - ввести заново, 2 - оставить как есть: ");

                int choice;
                if (scanf("%d", &choice) == 1) {
                    clearInputBuffer();
                    if (choice == 1) {
                        continue;
                    }
                }
                else {
                    clearInputBuffer();
                }
            }
            b->title = my_strdup(buffer);
            break;
        }
        else {
            printf("ошибка ввода. попробуйте еще раз.\n");
            clearInputBuffer();
        }
    }

    while (1) {
        printf("год издания (не ранее 868 г. и до текущего года): "); // оставим логику такой же какой она была в прошлой лабораторной. 
        if (scanf("%d", &b->year) != 1) {
            printf("ошибка! введите число.\n");

        }
        else if (b->year < 868 || b->year > GLOBAL_MAX_YEAR) {
            printf("ошибка: некорректный год.\n");
        }
        else {
            clearInputBuffer();
            break;
        }
        clearInputBuffer();
    }

    while (1) {
        printf("жанр (макс. 2047 символов): ");

        if (scanf(" %2047[^\n]", buffer) == 1) {
            int next_char = getchar();

            if (next_char != '\n' && next_char != EOF) {
                while (next_char != '\n' && next_char != EOF) {
                    next_char = getchar();
                }

                printf("данные были обрезаны под лимит буфера.\n");
                printf("1 - ввести заново, 2 - оставить как есть: ");

                int choice;
                if (scanf("%d", &choice) == 1) {
                    clearInputBuffer();
                    if (choice == 1) {
                        continue; // идем на новый круг ввода жанра
                    }
                }
                else {
                    clearInputBuffer();
                }
            }
            b->genre = my_strdup(buffer);
            break;
        }
        else {
            printf("ошибка ввода. попробуйте еще раз.\n");
            clearInputBuffer();
        }
    }

    while (1) {
        printf("краткая сводка (макс. 2047 символов): ");

        if (scanf(" %2047[^\n]", buffer) == 1) {
            int next_char = getchar();

            if (next_char != '\n' && next_char != EOF) {
                while (next_char != '\n' && next_char != EOF) {
                    next_char = getchar();
                }

                printf("данные были обрезаны под лимит буфера.\n");
                printf("1 - ввести заново, 2 - оставить как есть: ");

                int choice;
                if (scanf("%d", &choice) == 1) {
                    clearInputBuffer();
                    if (choice == 1) {
                        continue; // идем на новый круг ввода жанра
                    }
                }
                else {
                    clearInputBuffer();
                }
            }
            b->summary = my_strdup(buffer);
            break;
        }
        else {
            printf("ошибка ввода. попробуйте еще раз.\n");
            clearInputBuffer();
        }
    }
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