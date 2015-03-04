#include <string.h>
#include "dependency.h"

#ifndef DEPENDENCY_CONTAINER_H_INCLUDED
#define DEPENDENCY_CONTAINER_H_INCLUDED

#define DEPENDENCY_CONTAINER_INVALID_DEPENDENCY -2
#define DEPENDENCY_CONTAINER_VERSION_ERROR -1
#define DEPENDENCY_CONTAINER_ADDED_CORRECTLY 0
#define DEPENDENCY_CONTAINER_ALREADY_ADDED 1

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

	dc->dependencies = NULL;
}

int DependencyContainer_add(struct DependencyContainer *dc, struct Dependency *d)
{
	int i;

	if (!d) {
		return DEPENDENCY_CONTAINER_INVALID_DEPENDENCY;
	}

	for (i = 0; i < dc->count; i++) {
		// Check dependency already registered
		if (strcmp(d->name, dc->dependencies[i]->name) == 0) {
			// Dependency is already registered, so lets check its version
			if (strcmp(dc->dependencies[i]->version, d->version) == 0) {
				return DEPENDENCY_CONTAINER_ALREADY_ADDED;
			} else {
				return DEPENDENCY_CONTAINER_VERSION_ERROR;
			}
		}
	}

	dc->dependencies[dc->count] = d;
	dc->count++;

	dc->dependencies = realloc(dc->dependencies, sizeof(struct Dependency) * dc->count);

	return DEPENDENCY_CONTAINER_ADDED_CORRECTLY;
}

#endif