#define _CRT_SECURE_NO_WARNINGS
#include "library.h"
#include "funcs.h"

#define MAX_UNDO 10
static Library* history[MAX_UNDO] = { nullptr };
static int history_count = 0;
int sort_fields[3];
int sort_dirs[3];
int sort_num = 0;

Library* createLib() {
	Library* lib = new Library();

	lib->count = 0;
	lib->capacity = 1;

	lib->books = new Book[lib->capacity];

	return lib; 
}

void reserveMemory(Library* lib) {
	if (lib->count >= lib->capacity) {
		int new_capacity = lib->capacity + lib->capacity / 2 + 1;
		Book* temp_arr = new Book[new_capacity];

		for (int i = 0; i < lib->count; ++i) { // переносим данные во временное "хранилище"
			temp_arr[i] = lib->books[i];
		}

		delete[] lib->books;

		lib->books = temp_arr;
		lib->capacity = new_capacity;
	}
}

void addBook(Library* lib) {
	saveHistory(lib);
	reserveMemory(lib); // проверяем нужно ли довыделить память. если если то она добавится без выделения памяти. иначе выделится доп память

	printf("\nдобавлена книга под номером %d\n", lib->count + 1);
	inputBook(&lib->books[lib->count]);

	lib->count++;
	printf("\nкнига успешно добавлена");
}

void deleteBook(Library* lib, const char* title) {
	for (int i = 0; i < lib->count; ++i) {
		if (strcmp(lib->books[i].title, title) == 0) {
			freeBookContent(&lib->books[i]); // чистим данные книги но место под саму книгу как элемента картотеки оставляем 

			for (int j = i; j < lib->count - 1; ++j) {
				lib->books[j] = lib->books[j + 1];
			}
				
			lib->count--;
			printf("книга успешно удалена\n");
			return;
		}
	}
	printf("такой книги в картотеке нет\n");
}

void deleteBookAction(Library* lib) { // созданим доп. функцию чтоб все функции картотеки имели одинаковую сигнатуру для меню
	saveHistory(lib);
	char buffer[2048] = { 0 } ;
	printf("введите название книги для удаления: ");

	while (1) {
		if (scanf(" %2047[^\n]", buffer) == 1) {
			int next = getchar();
			if (next != '\n' && next != EOF) {
				while (next != '\n' && next != EOF) next = getchar();
				printf("название слишком длинное. попробуйте снова.");
				continue;
			}
			deleteBook(lib, buffer);
			break;
		}
		else {
			clearInputBuffer();
			return;
		}
	}
}

void saveToFile(Library* lib, const char* filename) {
	FILE* f = fopen(filename, "w"); // "w" - создает файл для записи
	if (!f) {
		return;
	}

	fprintf(f, "%d\n", lib->count); // в самом начале записываем кол-во элементов картотеки чтоб потом считать
	for (int i = 0; i < lib->count; ++i) {
		fprintf(f, "%s|%s|%d|%s|%s\n",
			lib->books[i].author, lib->books[i].title, lib->books[i].year,
			lib->books[i].genre, lib->books[i].summary);
	}
	fclose(f);
}

void loadFromFile(Library* lib, const char* filename) {
	const char* dot = strrchr(filename, '.'); // ищем последнюю точку в имени файла. strrchr находит указатель на нужный символ
	if (!dot || strcmp(dot, ".txt") != 0) {
		printf("\nфайл %s имеет неверное расширение (ожидалось .txt)\n", filename);
		return;
	}
	FILE* f = fopen(filename, "r"); // "r" - только чтение
	if (!f) {
		printf("\nфайл %s не найден\n", filename);
		return;
	}

	if (lib->books != nullptr) {
		for (int i = 0; i < lib->count; ++i) {
			freeBookContent(&lib->books[i]); // чистим строчки для каждой книги 
		}
		delete[] lib->books;
		lib->books = nullptr;
	}

	int new_count;
	if (fscanf(f, "%d\n", &new_count) != 1) { // считываем число которое записывали в самом начале файла
		fclose(f);
		return;
	}

	lib->count = new_count; // теперь готовим массив нужного нам размера
	lib->capacity = new_count;
	lib->books = new Book[lib->capacity];

	char buffer[2048] = { 0 }; // буфер для чтения строк

	for (int i = 0; i < lib->count; ++i) { // считываем каждую книгу. считываем данные до разделителя |. при этом пробелы будут игнорироваться что позволит нам считывать строчки целиком

		lib->books[i].author = nullptr;
		lib->books[i].title = nullptr;
		lib->books[i].genre = nullptr;
		lib->books[i].summary = nullptr;
		lib->books[i].year = 0;

		if (fscanf(f, "%2047[^|]|", buffer) == 1) {
			lib->books[i].author = my_strdup(buffer);
		}

		if (fscanf(f, "%2047[^|]|", buffer) == 1) {
			lib->books[i].title = my_strdup(buffer);
		}

		if (fscanf(f, "%d|", &lib->books[i].year) != 1) {
			lib->books[i].year = 0; 
		}

		if (fscanf(f, "%2047[^|]|", buffer) == 1) {
			lib->books[i].genre = my_strdup(buffer);
		}
		// читаем аннотацию до конца строки '\n'
		if (fscanf(f, "%2047[^\n]\n", buffer) == 1) {
			lib->books[i].summary = my_strdup(buffer);
		}
	}

	fclose(f);
	printf("картотека успешно загружена (%d книг)\n", lib->count);
}

void saveToFileAction(Library* lib) {
	if (lib == nullptr || lib->count == 0) {
		printf("картотека пуста, сохранять нечего.\n");
		return;
	}

	char filename[256] = { 0 };
	printf("введите имя файла для сохранения (например, lib.txt): ");

	while (1) {
		if (scanf(" %255s", filename) == 1) {
			int next_char = getchar(); 

			if (next_char != '\n' && next_char != EOF) {
				while (next_char != '\n' && next_char != EOF) {
					next_char = getchar();
				}
				printf("ошибка: имя файла слишком длинное\n");
				printf("введите имя заново: ");
				continue;
			}

			const char* dot = strrchr(filename, '.');
			if (!dot || strcmp(dot, ".txt") != 0) {
				printf("ошибка: файл должен иметь расширение .txt\n");
				printf("введите имя заново: ");
				continue;
			}
			break;
		}
		else {
			printf("ошибка ввода. попробуйте еще раз: ");
			clearInputBuffer();
		}
	}

	saveToFile(lib, filename);
	printf("данные успешно сохранены в файл: %s\n", filename);
}

void loadFromFileAction(Library* lib) {
	saveHistory(lib);
	char filename[256] = { 0 };
	printf("введите имя файла для загрузки: ");
	while (1) {
		if (scanf(" %255s", filename) == 1) {
			int next_char = getchar();

			if (next_char != '\n' && next_char != EOF) {
				while (next_char != '\n' && next_char != EOF) {
					next_char = getchar();
				}
				printf("ошибка: имя файла слишком длинное\n");
				printf("введите имя заново: ");
				continue;
			}

			const char* dot = strrchr(filename, '.');
			if (!dot || strcmp(dot, ".txt") != 0) {
				printf("ошибка: файл должен иметь расширение .txt\n");
				printf("введите имя заново: ");
				continue;
			}
			break;
		}
		else {
			printf("ошибка ввода. попробуйте еще раз: ");
			clearInputBuffer();
		}
	}
}

void exitProg(Library* lib) {
	if (lib == nullptr) return;

	for (int i = 0; i < lib->count; ++i) {
		freeBookContent(&lib->books[i]);

	}

	if (lib->books != nullptr) {
		delete[] lib->books;
	}

	delete lib;
}

void showGenre(Library* lib) {
	if (lib == nullptr || lib->count == 0) {
		printf("библиотека пуста, жанров нет.\n");
		return;
	}

	int max_count = 0;
	const char* best_genre = "не определен";

	for (int i = 0; i < lib->count; ++i) { // проходим по каждой книге
		int current_count = 0;
		const char* current_genre = lib->books[i].genre;

		if (current_genre == nullptr) { continue; }

		// считаем, сколько раз встречается этот жанр в библиотеке
		for (int j = 0; j < lib->count; ++j) {
			if (lib->books[j].genre != nullptr &&
				strcmp(current_genre, lib->books[j].genre) == 0) {
				current_count++;
			}
		}

		// нашли жанр который встречается чаще => запоминаем его
		if (current_count > max_count) {
			max_count = current_count;
			best_genre = current_genre;
		}
	}

	printf("самый популярный жанр: %s (%d раз)\n", best_genre, max_count);
}

void findBookByName(Library* lib) {
	printf("введите название книги: ");

	char buffer[2048] = { 0 }; // создаем буфер для ввода названия
	int num = -1;

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
			break;
		}
		else {
			printf("ошибка ввода. попробуйте еще раз.\n");
			clearInputBuffer();
		}
	}

	for (int i = 0; i < lib->count; ++i) {
		if (lib->books[i].title != nullptr && strcmp(buffer, lib->books[i].title) == 0) { // сравниваем введенное название со всеми назвниями книг
			num = i;
			break;
		}
	}

	if (num == -1) {
		printf("такой книги в библиотеке нет.\n");
		return;
	}

	printf("вот ваша книга.\n");
	printBook(&lib->books[num]);
}

void saveHistory(Library* lib) {
	if (history_count == MAX_UNDO) {
		exitProg(history[0]); // чистим первое действие чтоб добавить новое
		for (int i = 0; i < MAX_UNDO - 1; i++) { 
			history[i] = history[i + 1]; 
		}
		history_count--;
	}

	Library* snap = new Library(); // создаем копию текущего состояния библиотеки
	snap->count = lib->count;
	snap->capacity = lib->count;
	snap->books = new Book[snap->capacity];

	for (int i = 0; i < lib->count; i++) {
		snap->books[i].year = lib->books[i].year;
		snap->books[i].author = my_strdup(lib->books[i].author); // копируем строки через самодельную функцию дублирования которая 
		// копирует поведение strdup. саму strdup мы использовать не будем потому что в ней память выделяется по стандартам си что будет конфликтовать с new и delete
		snap->books[i].title = my_strdup(lib->books[i].title);
		snap->books[i].genre = my_strdup(lib->books[i].genre);
		snap->books[i].summary = my_strdup(lib->books[i].summary);
	}

	history[history_count++] = snap;
}

void undo(Library* lib) {
	if (history_count == 0) {
		printf("\nистория пуста. отменять нечего.\n");
		return;
	}

	int n;
	printf("сколько действий отменить? (доступно %d): ", history_count);
	if (scanf("%d", &n) != 1) {
		clearInputBuffer();
		return;
	}
	clearInputBuffer();

	if (n > history_count) {
		n = history_count;
	}

	if (n <= 0) {
		return; 
	}

	int target_idx = history_count - n; // находим нужный нам индекс среди всех откатов
	Library* target_snap = history[target_idx]; // запоминаем нужный откат

	for (int i = 0; i < lib->count; i++) {
		freeBookContent(&lib->books[i]);
	}
	delete[] lib->books;

	lib->count = target_snap->count;
	lib->capacity = target_snap->capacity;
	lib->books = target_snap->books;

	for (int i = target_idx; i < history_count; i++) {
		if (i == target_idx) {
			delete history[i]; // удаляем только структуру, массив книг передали в lib
		} 
		else {
			exitProg(history[i]); // остальные чистим полностью
		}
		history[i] = nullptr;
	}

	history_count = target_idx;
	printf("\nотменено %d действий.\n", n);
}


void printLibrary(Library* lib) {
	if (lib == nullptr || lib->count == 0) {
		printf("\nбиблиотека пуста или не инициализирована\n");
		return;
	}

	printf("\nвот все наши книги\n\n");

	for (int i = 0; i < lib->count; ++i) {
		printf("----книга номер %d----\n", i+1);
		printBook(&lib->books[i]); // выводим книги по одной
	}
}

void sortLib(Library* lib) {
	if (lib == nullptr || lib->count < 2) {
		printf("\nэлементов для сортировки недостаточно\n");
		return;
	}

	printf("введите количество полей для сортировки (1-3): ");
	if (scanf("%d", &sort_num) != 1) sort_num = 1;
	if (sort_num < 1) {
		printf("введенное число меньше возможного. засчитаем его за 1 по умолчанию");
		sort_num = 1;
	}
	if (sort_num > 3) {
		printf("введенное число больше возможного. засчитаем его за 3 по умолчанию");
		sort_num = 3;
	}

	for (int i = 0; i < sort_num; ++i) {
		printf("\nКритерий №%d:\n", i + 1);
		printf("Выберите поле (1-автор, 2-название, 3-год): ");
		while (1) {
			if (scanf("%d", &sort_fields[i]) != 1 || sort_fields[i] < 1 || sort_fields[i] > 3) {
				printf("\nошибка. введите число от 1 до 3\n");
				clearInputBuffer();
				continue;
			}
			break;
		}
		printf("Направление (1-возрастание, -1-убывание): ");
		while (1) {
			if (scanf("%d", &sort_dirs[i]) != 1 ||  ( sort_dirs[i] != 1 && sort_dirs[i] != -1) ) {
				printf("\nошибка. введите число 1 для возрастания или -1 для убывания\n");
				clearInputBuffer();
				continue;
			}
			break;
		}
		
	}
	clearInputBuffer();

	saveHistory(lib); // сохраняем состояние для Undo

	// вызываем sort
	sort((char*)lib->books, lib->count, sizeof(Book), swap_book, cmp_books_multi);

	printf("\nбиблиотека успешно отсортирована.");
}

void changeBook(Library* lib) {
	if (lib == nullptr || lib->count == 0) {
		printf("картотека пуста.\n");
		return;
	}

	char search_buffer[2048] = { 0 };
	printf("введите название книги для изменения: "); // делаем то же самое что и в findBookByName
	while (1) {
		if (scanf(" %2047[^\n]", search_buffer) == 1) {
			int next = getchar();
			if (next != '\n' && next != EOF) {
				while (next != '\n' && next != EOF) next = getchar();
				printf("название слишком длинное. попробуйте снова.");
				continue;
			}
			break;
		}
		else {
			clearInputBuffer();
			return;
		}
	}

	int index = -1;
	for (int i = 0; i < lib->count; ++i) {
		if (strcmp(lib->books[i].title, search_buffer) == 0) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		printf("книга не найдена.\n");
		return;
	}

	Book* b = &lib->books[index];

	printf("давайте ее изменим!\n");
	printf("(если хотите оставить поле неизменным ввведите \"-\")\n");

	char buffer[2048] = { 0 }; // буфер для чтения строки

	while (1) {
		printf("автор");
		if (scanf(" %2047[^\n]", buffer) == 1) {
			int next = getchar();
			if (next != '\n' && next != EOF) {
				while (next != '\n' && next != EOF) next = getchar();
				printf("данные обрезаны. 1 - ввести заново, 2 - оставить как есть: ");
				int choice;
				if (scanf("%d", &choice) == 1 && choice == 1) {
					clearInputBuffer();
					continue; 
				}
				clearInputBuffer();
			}

			if (strcmp(buffer, "-") != 0) {
				delete[] b->author;
				b->author = my_strdup(buffer);
			}
			break;
		}
	}

	while (1) {
		printf("название");
		if (scanf(" %2047[^\n]", buffer) == 1) {
			int next = getchar();
			if (next != '\n' && next != EOF) {
				while (next != '\n' && next != EOF) next = getchar();
				printf("данные обрезаны. 1 - ввести заново, 2 - оставить как есть: ");
				int choice;
				if (scanf("%d", &choice) == 1 && choice == 1) {
					clearInputBuffer();
					continue;
				}
				clearInputBuffer();
			}
			if (strcmp(buffer, "-") != 0) {
				delete[] b->title;
				b->title = my_strdup(buffer);
			}
			break;
		}
	}

	printf("год (0 - оставить): ");
	int new_year;
	if (scanf("%d", &new_year) == 1 && new_year != 0) {
		if (new_year >= 868 && new_year <= GLOBAL_MAX_YEAR) {
			b->year = new_year;
		}
		else {
			printf("ошибка: некорректный год.\n");
		}
	}
	clearInputBuffer();


	while (1) {
		printf("жанр");
		if (scanf(" %2047[^\n]", buffer) == 1) {
			int next = getchar();
			if (next != '\n' && next != EOF) {
				while (next != '\n' && next != EOF) next = getchar();
				printf("данные обрезаны. 1 - ввести заново, 2 - оставить как есть: ");
				int choice;
				if (scanf("%d", &choice) == 1 && choice == 1) {
					clearInputBuffer();
					continue;
				}
				clearInputBuffer();
			}
			if (strcmp(buffer, "-") != 0) {
				delete[] b->genre;
				b->genre = my_strdup(buffer);
			}
			break;
		}
	}
	while (1) {
		printf("краткое описание");
		if (scanf(" %2047[^\n]", buffer) == 1) {
			int next = getchar();
			if (next != '\n' && next != EOF) {
				while (next != '\n' && next != EOF) next = getchar();
				printf("данные обрезаны. 1 - ввести заново, 2 - оставить как есть: ");
				int choice;
				if (scanf("%d", &choice) == 1 && choice == 1) {
					clearInputBuffer();
					continue;
				}
				clearInputBuffer();
			}
			if (strcmp(buffer, "-") != 0) {
				delete[] b->summary;
				b->summary = my_strdup(buffer);
			}
			break;
		}
	}
	printf("\nданные обновлены!");
}

