#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "setstr.h"

#ifndef DEPENDENCY_H_INCLUDED
#define DEPENDENCY_H_INCLUDED

struct Dependency
{
	char *name;
	char *url;
	char *version;
};

/**
 *
 * @param  dependency
 * @param  path       Dependencies folder without trialing slash
 * @return            Command to be executed
 */
char *dependency_get_update_command(struct Dependency *dependency, const char *path)
{
	struct stat *s = malloc(sizeof(struct stat));
	char current_path[1024];

	char *dependency_path = NULL;
	char *command = NULL;

	getcwd(current_path, sizeof(current_path));

	dependency_path = setstr(current_path);
	dependency_path = appstr(dependency_path, "/");
	dependency_path = appstr(dependency_path, path);
	dependency_path = appstr(dependency_path, dependency->name);

	stat(dependency_path, s);

	command = setstr("cd ");
	command = appstr(command, dependency_path);
	command = appstr(command, " && ");

	// If dependency folder already exists
	if (s->st_mode & S_IFDIR) {
		command = appstr(command, "git pull origin master");
	} else {
		command = appstr(command, "git clone --progress --quiet ");
		command = appstr(command, dependency->url);
		command = appstr(command, " .");
	}

	free(s);
	free(dependency_path);

	s = NULL;
	dependency_path = NULL;

	return command;
}

void Dependency_update(struct Dependency *dependency, const char *path)
{
	char *command = NULL;

	if (dependency->name && dependency->url) {
		command = dependency_get_update_command(dependency, path);

		system(command);

		free(command);
		command = NULL;
	}
}

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