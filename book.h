#ifndef BOOK_H_
#define BOOK_H_

typedef struct Book {
	char* author;
	char* name;
	unsigned short year;
	unsigned int pageCount;
	double price;

	struct Book* next;
} Book;

size_t openBookFile(const char* const fileName, Book** const books);
void removeBookFromLinkedList(Book* parent, Book* book);
void printBook(const Book* const book);
void printHeader();

void swap(Book** head, Book* a, Book* b);
void writeBook(Book* book, FILE* file);
#endif
