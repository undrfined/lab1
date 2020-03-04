#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "book.h"

#define DATA_FILE_NAME "data.txt"

int main(void) {
	Book* books;
	size_t booksCount = openBookFile(DATA_FILE_NAME, &books);
	int i = 0;
	char* symbols = "pkl";
	Book* bookPrev = NULL;
	Book* book = books;
	printf("All books:\n");
	printHeader();
	while(book != NULL) {
		printBook(book);
		book = book->next;
	}

	printf("Sorted:\n");
	printHeader();

	while(1) {
		book = books->next;
		bookPrev = books;
		int sorted = 1;
		do {
			if(strcmp(book->name, bookPrev->name) < 0) {
				swap(&books, book, bookPrev);
				sorted = 0;
				break;
			}
		} while((bookPrev = book) && (book = book->next));

		if(sorted) break;
	}
	book = books;
	while(book != NULL) {
		printBook(book);
		book = book->next;
	}

	printf("\n");
	printf("Books without P,K,L:\n");
	bookPrev = NULL;
	book = books;
	printHeader();
	while(book != NULL) {
		int br = 0;
		for(int j = 0; j < strlen(symbols); ++j) {
			if(tolower(book->name[0]) == symbols[j]) {
				// Remove element from linked list
				br = 1;
				if(bookPrev == NULL) {
					book = books->next;
				} else {
					bookPrev->next = book->next;
					book = bookPrev->next;
				}
				break;
			}
		}
		if(br) continue;
		printBook(book);
		bookPrev = book;
		book = book->next;
	}

	return 0;
}
