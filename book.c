#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "book.h"
#include "utils.h"

size_t openBookFile(const char* const filename, Book** const books) {
	FILE* file = fopen(filename, "r");

	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* string = (char*) malloc(fileSize + 1);
	fread(string, 1, fileSize, file);
	fclose(file);
	string[fileSize] = 0;

	char** lines;
	size_t linesCount = split(string, "\n\r", &lines);

	*books = NULL;
	Book* current = NULL;
	for(int i = 0; i < linesCount; ++i) {
		char** parts;
		size_t partsCount = split(lines[i], ",", &parts);
		if(partsCount == 5) {
			Book* book = (Book*) calloc(1, sizeof(Book));
			if(book == NULL) {
				printf("Failed to allocate!\n");
				return -1;
			}
			book->author = trim(parts[0]);
			book->name = trim(parts[1]);
			book->year = atoi(parts[2]);
			book->pageCount = atoi(parts[3]);
			book->price = atof(parts[4]);
			book->next = NULL;
			if(*books == NULL) {
				*books = book; // head
			} else {
				current->next = book;
			}
			current = book;
		} else {
			linesCount--;
			i--;
		}
	}
	return linesCount;
}

void removeBookFromLinkedList(Book* parent, Book* book) {
	parent->next = book->next;
}

void printHeader() {
	printf(TOP_LEFT);
	STR_REPEAT(HORIZONTAL_STRAIGHT, 42);
	printf(T_BOTTOM);
	STR_REPEAT(HORIZONTAL_STRAIGHT, 17);
	printf(T_BOTTOM);
	STR_REPEAT(HORIZONTAL_STRAIGHT, 6);
	printf(T_BOTTOM);
	STR_REPEAT(HORIZONTAL_STRAIGHT, 7);
	printf(T_BOTTOM);
	STR_REPEAT(HORIZONTAL_STRAIGHT, 8);
	printf(TOP_RIGHT "\n");
	printf(VERTICAL_STRAIGHT " %40s " VERTICAL_STRAIGHT " %15s " VERTICAL_STRAIGHT " %4s " VERTICAL_STRAIGHT " %5s " VERTICAL_STRAIGHT " %6s " VERTICAL_STRAIGHT "\n",
			"Name", "Author", "Year", "Pages", "Price");
	printf(T_RIGHT);
	STR_REPEAT(HORIZONTAL_STRAIGHT, 42);
	printf(CROSS);
	STR_REPEAT(HORIZONTAL_STRAIGHT, 17);
	printf(CROSS);
	STR_REPEAT(HORIZONTAL_STRAIGHT, 6);
	printf(CROSS);
	STR_REPEAT(HORIZONTAL_STRAIGHT, 7);
	printf(CROSS);
	STR_REPEAT(HORIZONTAL_STRAIGHT, 8);
	printf(T_LEFT "\n");

}

void printBook(const Book* const book) {
	printf(VERTICAL_STRAIGHT " %40s " VERTICAL_STRAIGHT " %15s " VERTICAL_STRAIGHT " %4d " VERTICAL_STRAIGHT " %5d " VERTICAL_STRAIGHT " %6.2f " VERTICAL_STRAIGHT "\n",
			book->name, book->author, book->year, book->pageCount, book->price);
}

int isBookPriceHigherThanAverage(Book* book, va_list args) {
	return book->price > va_arg(args, double);
}

double getTotalPrice(Book* books) {
	double price = .0;
	Book* book = books;
	while(book != NULL) {
		price += book->price;
		book = book->next;
	}
	return price;
}

void printBooks(Book* books, int (*condition)(Book*, va_list), ...) {
	Book* book = books;
	printHeader();
	va_list args;
	va_start(args, condition);
	while(book != NULL) {
		va_list b;
		va_copy(b, args);
		if(condition == NULL || condition(book, b)) {
			printBook(book);
		}
		book = book->next;
	}
	va_end(args);
	printf(BOTTOM_LEFT);
	STR_REPEAT(HORIZONTAL_STRAIGHT, 42);
	printf(T_TOP);
	STR_REPEAT(HORIZONTAL_STRAIGHT, 17);
	printf(T_TOP);
	STR_REPEAT(HORIZONTAL_STRAIGHT, 6);
	printf(T_TOP);
	STR_REPEAT(HORIZONTAL_STRAIGHT, 7);
	printf(T_TOP);
	STR_REPEAT(HORIZONTAL_STRAIGHT, 8);
	printf(BOTTOM_RIGHT "\n");

}

void writeBook(Book* book, FILE* file) {
	fprintf(file, "%s,%s,%d,%d,%f\n", book->author, book->name, book->year, book->pageCount, book->price);
}

void writeBooksToFile(char* filename, Book* books) {
	FILE* fp = fopen(filename, "w");
	Book* book = books;
	while(book != NULL) {
		writeBook(book, fp);
		book = book->next;
	}
	fclose(fp);
}

void sortBooks(Book** books, int (*compareFn)(Book* a, Book* b)) {
	Book* book, *bookPrev;
	while(1) {
		book = (*books)->next;
		bookPrev = *books;
		int sorted = 1;
		do {
			if(compareFn(book, bookPrev)) {
				swap(books, book, bookPrev);
				sorted = 0;
				break;
			}
		} while((bookPrev = book) && (book = book->next));

		if(sorted) break;
	}
}

int compareBooksByName(Book* a, Book* b) {
	return strcmp(a->name, b->name) < 0; 
}

int bookDoesntHaveOneOfSymbols(Book* book, va_list args) {
	char* symbols = va_arg(args, char*);
	for(int j = 0; j < strlen(symbols); ++j) {
		if(tolower(book->name[0]) == symbols[j]) {
			return 0;
		}
	}
	return 1;
}

void swap(Book **head_ref, Book* x, Book* y)
{
	if (x == y) return;

	Book *prevX = NULL, *currX = *head_ref;
	while (currX && currX != x)
	{
	    prevX = currX;
	    currX = currX->next;
	}

	Book *prevY = NULL, *currY = *head_ref;
	while (currY && currY != y)
	{
	    prevY = currY;
	    currY = currY->next;
	}

	if (currX == NULL || currY == NULL)
	    return;

	if (prevX != NULL)
	    prevX->next = currY;
	else
	    *head_ref = currY;

	if (prevY != NULL)
	    prevY->next = currX;
	else
	    *head_ref = currX;

	Book *temp = currY->next;
	currY->next = currX->next;
	currX->next = temp;
}
