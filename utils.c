#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

size_t split(const char* const originalString, const char* const delimiters, char*** const parts) {
	size_t length = strlen(originalString);
	size_t delimitersLength = strlen(delimiters);

	char* string = (char*) malloc(length + 1);

	strcpy(string, originalString);

	size_t partsCount = 1;

	for(int i = 0; i < length; ++i) {
		for(int j = 0; j < delimitersLength; ++j) {
			if(string[i] == delimiters[j]) {
				partsCount++;
				string[i] = 0;
				break;
			}
		}
	}
	if(partsCount == 1) {
		*parts = &string;
		return 1;
	}
	*parts = (char**) calloc(partsCount, sizeof(char*));

	if(*parts == NULL) {
		// TODO print error
		return 0;
	}
	for(int i = 0; i < partsCount; ++i) {
		size_t partLength = strlen(string);
		if(partLength == 0) {
			i--;
			partsCount--;
			string += partLength + 1;
			continue;
		}
		(*parts)[i] = (char*) malloc(partLength + 1);
		strcpy((*parts)[i], string);
		string += partLength + 1;
	}
	return partsCount;
}

char* trim(const char* const originalString) {
	char* string = (char*) originalString;
	size_t length = strlen(string);
	while(1) {
		if(string[0] == ' ') {
			string++;
		} else break;
	}
	return string;
}
