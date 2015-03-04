#include <stdlib.h>
#include <unistd.h>
#include "assert.h"
#include "../setstr.h"
#include "../dependency.h"

void main()
{
	struct Dependency *d = Dependency_create();
	struct Dependency *from_url = Dependency_create_from_url("github.com:Ruk33/something.git");
	struct Dependency *from_invalid_url = Dependency_create_from_url(NULL);
	struct Dependency *c = Dependency_create();
	char current_path[1024];
	char *command;

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
	ec("Ruk33/something", d->name);

	ec("HEAD", d->version);
	Dependency_set_version(d, "15654651");
	ec("15654651", d->version);

	Dependency_set_version(d, NULL);
	ec("HEAD", d->version);

	Dependency_set_version(d, "");
	ec("HEAD", d->version);

	ec("Ruk33/something", from_url->name);
	ec("", from_invalid_url->name);

	ec("HEAD", from_url->version);
	ec("HEAD", from_invalid_url->version);

	Dependency_set_name(c, "testdependency");
	Dependency_set_url(c, "google.com");

	getcwd(current_path, sizeof(current_path));

	command = setstr("cd ");
	command = appstr(command, current_path);
	command = appstr(command, "/testdependency && git pull origin master");

	ec(command, dependency_get_update_command(c, ""));

	free(command);

	Dependency_set_name(c, "dependency");

	command = setstr("cd ");
	command = appstr(command, current_path);
	command = appstr(command, "/dependency && git clone --progress --quiet google.com .");
	ec(command, dependency_get_update_command(c, ""));

	free(d);
	free(from_url);
	free(from_invalid_url);
	free(c);
	free(command);

	d = NULL;
	from_url = NULL;
	from_invalid_url = NULL;
	c = NULL;
	command = NULL;
}