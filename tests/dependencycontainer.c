#include <stdlib.h>
#include "assert.h"
#include "../dependencycontainer.h"
#include "../dependency.h"

void main()
{
	struct DependencyContainer *dc = DependencyContainer_create();
	struct Dependency *i = Dependency_create();
	struct Dependency *d = Dependency_create_from_url("github.com:Ruk33/something.git");
	struct Dependency *r = Dependency_create_from_url("github.com:Ruk33/something.git");
	struct Dependency *e = Dependency_create_from_url("github.com:Ruk33/lolipop.git");
	struct Dependency *s = Dependency_create_from_url("github.com:Ruk33/something.git");

	Dependency_set_version(r, "batman");

	ei(DEPENDENCY_CONTAINER_INVALID_DEPENDENCY, DependencyContainer_add(dc, NULL));

	ei(DEPENDENCY_CONTAINER_INVALID_DEPENDENCY, DependencyContainer_add(dc, i));
	Dependency_set_url(i, "github.com:Ruk33/lorem.git");
	ei(DEPENDENCY_CONTAINER_ADDED_CORRECTLY, DependencyContainer_add(dc, i));

	ei(DEPENDENCY_CONTAINER_ADDED_CORRECTLY, DependencyContainer_add(dc, d));

	ei(DEPENDENCY_CONTAINER_ALREADY_ADDED, DependencyContainer_add(dc, d));
	ei(DEPENDENCY_CONTAINER_VERSION_ERROR, DependencyContainer_add(dc, r));

	ei(DEPENDENCY_CONTAINER_ADDED_CORRECTLY, DependencyContainer_add(dc, e));

	a(dc->dependencies[0] == i, "first dependency in dependencycontainer isnt correct");
	a(dc->dependencies[1] == d, "second dependency in dependencycontainer isnt correct");
	a(dc->dependencies[2] == e, "third dependency in dependencycontainer isnt correct");

	ei(3, dc->count);

	a(DependencyContainer_dependency_is_registered(dc, d->name), "dependency d doesnt show up as registered in dc");
	a(!DependencyContainer_dependency_is_registered(dc, NULL), "null shouldnt be mark as registered in dc");
	a(!DependencyContainer_dependency_is_registered(NULL, d->name), "d shouldnt be marked as registered in a null dependency container");
	a(DependencyContainer_dependency_is_registered(dc, s->name), "s should be marked as registered in dc");
	a(!DependencyContainer_dependency_is_registered(dc, "pocho"), "pocho shouldnt be marked as registered in dc");

	DependencyContainer_destroy(dc);

	free(d);
	free(r);
	free(e);
	free(s);

	d = NULL;
	r = NULL;
	e = NULL;
	s = NULL;
}