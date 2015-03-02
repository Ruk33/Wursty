#include <string.h>
#include <stdlib.h>
#include "setstr.h"

#ifndef DEPENDENCY_H_INCLUDED
#define DEPENDENCY_H_INCLUDED

struct Dependency
{
	char *name;
	char *url;
	char *version;
};

void Dependency_set_name(struct Dependency *dependency, const char *name)
{
	free(dependency->name);
	dependency->name = setstr(name);
}

void Dependency_set_url(struct Dependency *dependency, const char *url)
{
	free(dependency->url);
	dependency->url = setstr(url);
}

void Dependency_set_version(struct Dependency *dependency, const char *version)
{
	free(dependency->version);

	if (version && strcmp(version, "") != 0) {
		dependency->version = setstr(version);
	} else {
		dependency->version = setstr("HEAD");
	}
}

void Dependency_set_name_from_url(struct Dependency *dependency)
{
	char *name = strchr(dependency->url, ':');

	if (name) {
		// Remove ":"
		name++;

		// Remove .git from name
		name[strlen(name)-4] = '\0';
	} else {
		name = "";
	}

	Dependency_set_name(dependency, name);
}

struct Dependency *Dependency_create()
{
	struct Dependency *instance = malloc(sizeof(struct Dependency));

	instance->name = "";
	instance->url = "";
	instance->version = "";

	Dependency_set_version(instance, "HEAD");

	return instance;
}

struct Dependency *Dependency_create_from_url(const char *url)
{
	struct Dependency *instance = Dependency_create();

	Dependency_set_url(instance, url);
	Dependency_set_name_from_url(instance);

	return instance;
}

#endif