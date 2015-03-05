#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "dstr.h"

#ifndef DEPENDENCY_H_INCLUDED
#define DEPENDENCY_H_INCLUDED

struct Dependency
{
	char *name;
	char *url;
	char *version;
	char *short_version;
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

	char *dependency_path = NULL;
	char *command = NULL;

	dependency_path = dstrcpy(dependency_path, path);
	dependency_path = dstrcat(dependency_path, "/");
	dependency_path = dstrcat(dependency_path, dependency->name);

	stat(dependency_path, s);

	// If dependency folder already exists
	if (s->st_mode & S_IFDIR) {
		command = dstrcpy(command, "cd ");
		command = dstrcat(command, dependency_path);
		command = dstrcat(command, " && git pull --quiet --progress origin master");
	} else {
		command = dstrcpy(command, "git clone --quiet --progress --no-checkout ");
		command = dstrcat(command, dependency->url);
		command = dstrcat(command, " ");
		command = dstrcat(command, dependency_path);
		command = dstrcat(command, " && cd ");
		command = dstrcat(command, dependency_path);
	}

	command = dstrcat(command, " && git checkout --quiet ");
	command = dstrcat(command, dependency->version);

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
	dependency->name = dstrcpy(dependency->name, name);
}

void Dependency_set_url(struct Dependency *dependency, const char *url)
{
	dependency->url = dstrcpy(dependency->url, url);
}

char *Dependency_set_short_version(struct Dependency *d)
{
	d->short_version = dstrcpy(d->short_version, d->version);

	if (strlen(d->short_version) == 40) {
		d->short_version[7] = '\0';
	}
}

void Dependency_set_version(struct Dependency *dependency, const char *version)
{
	if (version && strcmp(version, "") != 0) {
		dependency->version = dstrcpy(dependency->version, version);
	} else {
		dependency->version = dstrcpy(dependency->version, "master");
	}

	Dependency_set_short_version(dependency);
}

void Dependency_set_name_from_url(struct Dependency *dependency)
{
	char *full_name = NULL;
	char *name = NULL;

	if (dependency->url && strcmp(dependency->url, "") != 0) {
		full_name = dstrcpy(full_name, strchr(dependency->url, ':'));
	}

	if (full_name) {
		// Remove ":"
		full_name++;

		name = dstrcpy(name, strchr(full_name, '/'));

		if (name) {
			// Remove "/"
			name++;
			if (strlen(name) > 4) {
				// Remove ".git"
				name[strlen(name)-4] = '\0';
			}
		} else {
			//name = dstrcpy(name, NULL);
		}

		free(full_name);
	}

	Dependency_set_name(dependency, name);

	if (name) {
		free(name);
	}

	full_name = NULL;
	name = NULL;
}

struct Dependency *Dependency_create()
{
	struct Dependency *instance = malloc(sizeof(struct Dependency));

	instance->name = NULL;
	instance->url = NULL;
	instance->version = NULL;
	instance->short_version = NULL;

	Dependency_set_name(instance, NULL);
	Dependency_set_url(instance, NULL);
	Dependency_set_version(instance, NULL);

	return instance;
}

struct Dependency *Dependency_create_from_url(const char *url)
{
	struct Dependency *instance = Dependency_create();

	Dependency_set_url(instance, url);
	Dependency_set_name_from_url(instance);

	return instance;
}

void Dependency_destroy(struct Dependency *d)
{
	free(d->name);
	free(d->url);
	free(d->version);
	free(d->short_version);

	d->name = NULL;
	d->url = NULL;
	d->version = NULL;
	d->short_version = NULL;

	free(d);
	d = NULL;
}

#endif