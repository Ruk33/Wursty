#include <stdlib.h>
#include "assert.h"
#include "../dependencycontainer.h"
#include "../dependency.h"

void main()
{
	struct DependencyContainer *dc = DependencyContainer_create();
	struct Dependency *d = Dependency_create_from_url("github.com:Ruk33/something.git");
	struct Dependency *r = Dependency_create_from_url("github.com:Ruk33/something.git");
	struct Dependency *e = Dependency_create_from_url("github.com:Ruk33/lolipop.git");

	Dependency_set_version(r, "batman");

	ei(1, DependencyContainer_add(dc, d));
	ei(0, DependencyContainer_add(dc, d));
	ei(-1, DependencyContainer_add(dc, r));
	ei(1, DependencyContainer_add(dc, e));
	ei(2, dc->count);
	a(dc->dependencies[0] == d, "first dependency in dependencycontainer isnt correct");
	a(dc->dependencies[1] == e, "second dependency in dependencycontainer isnt correct");

	DependencyContainer_destroy(dc);
	free(d);
	free(r);
	free(e);
}