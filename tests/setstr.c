#include <stdlib.h>
#include "assert.h"
#include "../setstr.h"

void main()
{
	const char *long_str = "lorem ipsum dolor sit amet";
	const char *short_str = "batman";
	char *str;
	char *s;

	str = setstr(long_str);
	ec(str, long_str);
	free(str);

	str = setstr(short_str);
	ec(str, short_str);
	free(str);

	str = setstr(NULL);
	ec(str, "");
	free(str);

	str = setstr("im ");
	str = appstr(str, "awesome");
	ec("im awesome", str);
	free(str);

	str = appstr(NULL, "awesome");
	ec("awesome", str);
	free(str);

	str = appstr("yeah", NULL);
	ec("yeah", str);
	free(str);

	str = appstr(NULL, NULL);
	ec("", str);
	free(str);

	s = appstr("leel", NULL);
	ec("leel", s);
	free(s);
}