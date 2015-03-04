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
	a(copy_str[strlen(copy_str)+1] == '\0', "copy_str doesnt have eof");

	append_str = dstrcat(append_str, NULL);
	ec("", append_str);
	a(append_str[strlen(append_str)+1] == '\0', "append_str doesnt have eof");

	append_str = dstrcat(append_str, "im");
	ec("im", append_str);

	append_str = dstrcat(append_str, " awesome");
	ec("im awesome", append_str);

	append_str = dstrcatc(append_str, ch);
	append_str = dstrcatc(append_str, ch);
	append_str = dstrcatc(append_str, '\t');
	ec("im awesomecc\t", append_str);
	a(append_str[strlen(append_str)+1] == '\0', "a doesnt have eof");

	free(copy_str);
	free(append_str);
}