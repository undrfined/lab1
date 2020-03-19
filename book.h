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
void printBooks(Book* books, int (*condition)(Book* book, va_list args), ...);
void printHeader();
int isBookPriceHigherThanAverage(Book* book, va_list args);

void swap(Book** head, Book* a, Book* b);
void writeBook(Book* book, FILE* file);
void writeBooksToFile(char* filename, Book* books);
void sortBooks(Book** books, int (*compareFn)(Book* a, Book* b));
int bookDoesntHaveOneOfSymbols(Book* book, va_list args);
int compareBooksByName(Book* a, Book* b);
double getTotalPrice(Book* books);
#endif
