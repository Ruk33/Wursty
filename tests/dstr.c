#include "assert.h"
#include "../dstr.h"

void main()
{
	char *copy_str = NULL;
	char *append_str = NULL;
	char ch = 'c';

	copy_str = dstrcpy(copy_str, "something");
	ec("something", copy_str);

	copy_str = dstrcpy(copy_str, "lorem");
	ec("lorem", copy_str);

	copy_str = dstrcpy(copy_str, NULL);
	ec("", copy_str);

	append_str = dstrcat(append_str, NULL);
	ec("", append_str);

	append_str = dstrcat(append_str, "im");
	ec("im", append_str);

	append_str = dstrcat(append_str, " awesome");
	ec("im awesome", append_str);

	append_str = dstrcatc(append_str, ch);
	append_str = dstrcatc(append_str, ch);
	append_str = dstrcatc(append_str, '\t');
	ec("im awesomecc\t", append_str);

	free(copy_str);
	free(append_str);
}