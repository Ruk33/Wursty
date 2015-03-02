#include <stdlib.h>
#include "assert.h"
#include "../dependency.h"

void main()
{
	struct Dependency *d = Dependency_create();
	struct Dependency *from_url = Dependency_create_from_url("github.com:Ruk33/something.git");
	struct Dependency *from_invalid_url = Dependency_create_from_url(NULL);

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

	free(d);
	free(from_url);
	free(from_invalid_url);
}