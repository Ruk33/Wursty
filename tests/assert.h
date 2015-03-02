#include <stdio.h>
#include <string.h>

void a(const char assertion, const char *msg)
{
	if (!assertion) {
		printf(">> %s\n", msg);
	}
}

void ec(const char *expected, const char *given)
{
	if (strcmp(expected, given) != 0) {
		printf(">> expected '%s' string but given '%s'\n", expected, given);
	}
}

void ei(const int expected, const int given)
{
	if (expected != given) {
		printf(">> expected '%d' int but given '%d'\n", expected, given);
	}
}