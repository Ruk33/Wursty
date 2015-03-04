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
	int i;

	for (i = 0; i < dc->count; i++) {
		Dependency_destroy(dc->dependencies[i]);
		dc->dependencies[i] = NULL;
	}

	free(dc->dependencies);
	dc->dependencies = NULL;

	free(dc);
	dc = NULL;
}

struct Dependency *DependencyContainer_get_dependency_by_name(struct DependencyContainer *dc, const char *name)
{
	int i;

	for (i = 0; i < dc->count; i++) {
		if (strcmp(name, dc->dependencies[i]->name) == 0) {
			return dc->dependencies[i];
		}
	}

	return NULL;
}

char DependencyContainer_dependency_is_registered(struct DependencyContainer *dc, const char *dependency_name)
{
	if (dc && dependency_name) {
		return DependencyContainer_get_dependency_by_name(dc, dependency_name) != NULL;
	}

	return 0;
}

int DependencyContainer_add(struct DependencyContainer *dc, struct Dependency *d)
{
	struct Dependency *dependency;
	int result = DEPENDENCY_CONTAINER_ADDED_CORRECTLY;
	int i;

	if (!d || strlen(d->url) == 0) {
		return DEPENDENCY_CONTAINER_INVALID_DEPENDENCY;
	}

	dependency = Dependency_create(d->url);

	Dependency_set_name(dependency, d->name);
	Dependency_set_url(dependency, d->url);
	Dependency_set_version(dependency, d->version);

	for (i = 0; i < dc->count; i++) {
		// Check dependency already registered
		if (strcmp(dependency->name, dc->dependencies[i]->name) == 0) {
			// Dependency is already registered, so lets check its version
			if (strcmp(dc->dependencies[i]->version, dependency->version) == 0) {
				result = DEPENDENCY_CONTAINER_ALREADY_ADDED;
			} else {
				result = DEPENDENCY_CONTAINER_VERSION_ERROR;
			}

			break;
		}
	}

	if (result == DEPENDENCY_CONTAINER_ADDED_CORRECTLY) {
		dc->dependencies[dc->count] = dependency;
		dc->count++;

		dc->dependencies = realloc(dc->dependencies, sizeof(struct Dependency) * dc->count);
	} else {
		Dependency_destroy(dependency);
	}

	dependency = NULL;

	return result;
}

#endif