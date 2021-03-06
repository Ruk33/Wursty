#include <stdlib.h>
#include <unistd.h>
#include "assert.h"
#include "../dstr.h"
#include "../dependency.h"

void main()
{
	struct Dependency *d = Dependency_create();
	struct Dependency *from_url = Dependency_create_from_url("github.com:Ruk33/something.git");
	struct Dependency *from_invalid_url = Dependency_create_from_url(NULL);
	struct Dependency *c = Dependency_create();
	char current_path[1024];
	char *update_path = NULL;
	char *command = NULL;

	ec("", d->name);

	Dependency_set_name(d, "batman");
	ec("batman", d->name);

	Dependency_set_name(d, NULL);
	ec("", d->name);
	ec("", d->url);

	Dependency_set_url(d, "github.com:Ruk33/something.git");
	ec("github.com:Ruk33/something.git", d->url);

	Dependency_set_url(d, NULL);
	ec("", d->url);

	Dependency_set_name_from_url(d);
	ec("", d->name);

	Dependency_set_url(d, "github.com:Ruk33/something.git");
	Dependency_set_name_from_url(d);
	ec("something", d->name);

	ec("master", d->version);
	ec("master", d->short_version);

	Dependency_set_version(d, "a74d8ce387e2d11be02d93dc463855379f04d066");
	ec("a74d8ce387e2d11be02d93dc463855379f04d066", d->version);
	ec("a74d8ce", d->short_version);

	Dependency_set_version(d, NULL);
	ec("master", d->version);

	Dependency_set_version(d, "");
	ec("master", d->version);

	ec("something", from_url->name);
	ec("", from_invalid_url->name);

	ec("github.com:Ruk33/something.git", from_url->url);

	ec("master", from_url->version);
	ec("master", from_invalid_url->version);

	Dependency_set_name(c, "testdependency");
	Dependency_set_url(c, "google.com");
	Dependency_set_version(c, "1234");

	getcwd(current_path, sizeof(current_path));

	command = dstrcpy(command, "cd ");
	command = dstrcat(command, current_path);
	command = dstrcat(command, "/testdependency && git pull --quiet --progress origin master && git checkout --quiet ");
	command = dstrcat(command, c->version);

	ec(command, dependency_get_update_command(c, current_path));

	Dependency_set_name(c, "dependency");

	command = dstrcpy(command, "git clone --quiet --progress --no-checkout google.com ");
	command = dstrcat(command, current_path);
	command = dstrcat(command, "/dependency && cd ");
	command = dstrcat(command, current_path);
	command = dstrcat(command, "/dependency && git checkout --quiet 1234");
	ec(command, dependency_get_update_command(c, current_path));

	Dependency_destroy(d);
	Dependency_destroy(from_url);
	Dependency_destroy(from_invalid_url);
	Dependency_destroy(c);

	free(command);
	command = NULL;
}