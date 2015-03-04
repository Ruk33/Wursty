#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef SETSTR_H_INCLUDED
#define SETSTR_H_INCLUDED

/**
 * Dinamic strings, damn!
 * 
 * Be careful of leaks
 *
 * char *s = setstr("something");
 * free(s); // --> before using it again, free the memory!
 * s = setstr("another thing");
 */
char *setstr(const char *d)
{
	if (d)
		return strcpy(malloc(sizeof(char) * (strlen(d)+1)), d);
	else
		return strcpy(malloc(sizeof(char)), "");
}

char *appstr(char *s, const char *d)
{
	size_t slen = 0;
	size_t dlen = 0;
	char *ns;

	if (s)
		slen = strlen(s);

	if (d)
		dlen = strlen(d);

	ns = malloc(sizeof(char) * (slen+dlen+1));
	strcpy(ns, "");

	if (s)
		strcat(ns, s);

	if (d)
		strcat(ns, d);

	free(s);

	return ns;
}

#endif