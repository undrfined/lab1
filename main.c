#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "book.h"


int main(void) {
	char filename[255];

	printf("Enter file to read from:\n");
	scanf("%s", filename);

	Book* books;
	size_t booksCount = openBookFile(filename, &books);

	double avg = getTotalPrice(books) / (double)booksCount;
	char* symbols = "pkl";

	printf("All books (unsorted):\n");
	printBooks(books, NULL);

	printf("Books with cost over %lf:\n", avg);
	printBooks(books, isBookPriceHigherThanAverage, avg);

	printf("Sorted:\n");
	sortBooks(&books, compareBooksByName);
	printBooks(books, NULL);

	printf("Books without P, K, L:\n");
	printBooks(books, bookDoesntHaveOneOfSymbols, symbols);


	printf("Enter file to write to:\n");
	scanf("%s", filename);
	writeBooksToFile(filename, books);


	return 0;
}
