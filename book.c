#include <stdio.h>
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
	printf("| %40s | %15s | %4s | %5s | %6s |\n", "Name", "Author", "Year", "Pages", "Price");
}

void printBook(const Book* const book) {
	printf("| %40s | %15s | %4d | %5d | %6.2f |\n", book->name, book->author, book->year, book->pageCount, book->price);
}

void writeBook(Book* book, FILE* file) {
	fprintf(file, "%s,%s,%d,%d,%f\n", book->author, book->name, book->year, book->pageCount, book->price);
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
