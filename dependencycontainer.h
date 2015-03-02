#include <string.h>
#include "dependency.h"

#ifndef DEPENDENCY_CONTAINER_H_INCLUDED
#define DEPENDENCY_CONTAINER_H_INCLUDED

struct DependencyContainer
{
	struct Dependency **dependencies;
	int count;
};

struct DependencyContainer *DependencyContainer_create()
{
	struct DependencyContainer *instance = malloc(sizeof(struct DependencyContainer));

	instance->dependencies = malloc(sizeof(struct Dependency));
	instance->count = 0;

	return instance;
}

void DependencyContainer_destroy(struct DependencyContainer *dc)
{
	free(dc->dependencies);
	free(dc);
}

int DependencyContainer_add(struct DependencyContainer *dc, struct Dependency *d)
{
	int i;

	for (i = 0; i < dc->count; i++) {
		if (strcmp(d->name, dc->dependencies[i]->name) == 0) {
			if (strcmp(dc->dependencies[i]->version, d->version) == 0) {
				return 0;
			} else {
				return -1;
			}
		}
	}

	dc->dependencies[dc->count] = d;
	dc->count++;

	dc->dependencies = realloc(dc->dependencies, sizeof(struct Dependency) * dc->count);

	return 1;
}

#endif