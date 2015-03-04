#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef DSTR_H_INCLUDED
#define DSTR_H_INCLUDED

char *dstrcpy(char *source, const char *to_copy)
{
	size_t to_copy_len = 0;

	if (to_copy != NULL) {
		to_copy_len = strlen(to_copy);
	}

	if (source == NULL) {
		source = malloc(sizeof(char) * (to_copy_len+1));
	} else {
		source = realloc(source, sizeof(char) * (strlen(source)+to_copy_len+1));
	}

	if (to_copy != NULL) {
		source = strcpy(source, to_copy);
	} else {
		source = strcpy(source, "");
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
	size_t slen;

	if (source == NULL) {
		source = dstrcpy(source, NULL);
	}

	slen = strlen(source);

	if (append == '\0' && source[slen+1] == '\0') { // avoid multiple eof

	} else {
		source = realloc(source, sizeof(char) * (slen+2));
		sprintf(source, "%s%c", source, append);
	}

	return source;
}

#endif