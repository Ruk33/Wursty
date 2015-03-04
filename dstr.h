#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef DSTR_H_INCLUDED
#define DSTR_H_INCLUDED

char *dstrcpy(char *source, const char *to_copy)
{
	if (source != NULL) {
		free(source);
	}

	if (to_copy != NULL) {
		source = malloc(sizeof(char) * (strlen(to_copy)+1));
		source = strcpy(source, to_copy);
	} else {
		source = calloc(0, sizeof(char));
	}

	if (source[strlen(source)+1] != '\0') {
		source[strlen(source)+1] = '\0';
	}

	return source;
}

char *dstrcat(char *source, const char *append)
{
	if (source == NULL) {
		source = dstrcpy(source, NULL);
	}

	if (append != NULL) {
		source = realloc(source, sizeof(char) * (strlen(source)+strlen(append)+1));
		source = strcat(source, append);
	}

	return source;
}

char *dstrcatc(char *source, const char append)
{
	if (source == NULL) {
		source = dstrcpy(source, NULL);
	}

	if (append != '\0') {
		source = realloc(source, sizeof(char) * (strlen(source)+2));
		sprintf(source, "%s%c", source, append);
	}

	return source;
}

#endif