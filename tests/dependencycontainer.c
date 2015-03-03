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

	ei(DEPENDENCY_CONTAINER_INVALID_DEPENDENCY, DependencyContainer_add(dc, NULL));
	ei(DEPENDENCY_CONTAINER_ADDED_CORRECTLY, DependencyContainer_add(dc, d));
	ei(DEPENDENCY_CONTAINER_ALREADY_ADDED, DependencyContainer_add(dc, d));
	ei(DEPENDENCY_CONTAINER_VERSION_ERROR, DependencyContainer_add(dc, r));
	ei(DEPENDENCY_CONTAINER_ADDED_CORRECTLY, DependencyContainer_add(dc, e));
	a(dc->dependencies[0] == d, "first dependency in dependencycontainer isnt correct");
	a(dc->dependencies[1] == e, "second dependency in dependencycontainer isnt correct");
	ei(2, dc->count);

	DependencyContainer_destroy(dc);
	free(d);
	free(r);
	free(e);
}