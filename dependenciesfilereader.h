#include <string.h>
#include <ctype.h>
#include "dependency.h"
#include "dependencycontainer.h"
#include "dependency.h"
#include "dstr.h"

#ifndef DEPENDENCIES_FILE_READER_H_INCLUDED
#define DEPENDENCIES_FILE_READER_H_INCLUDED

void get_all_dependencies_from_dependencies_file(const char *path, struct DependencyContainer *dc, char display_errors)
{
	FILE *dependency_file = fopen(path, "r");
	struct Dependency *dependency = NULL;
	char *line = NULL;
	char *dependency_url = NULL;
	char *dependency_version = NULL;
	char ch = NULL;

	if (!dependency_file) {
		return;
	}

	do {
		ch = fgetc(dependency_file);

		if (ch == '\n' || ch == EOF) {
			dependency_url = dstrcpy(dependency_url, line);
			dependency_version = strrchr(line, ',');

			if (dependency_version) {
				// Remove version from line so we get only the url
				dependency_url[strlen(dependency_url) - strlen(dependency_version)] = '\0';

				// Remove ","
				dependency_version++;
			}

			dependency = Dependency_create_from_url(dependency_url);
			Dependency_set_version(dependency, dependency_version);

			if (DependencyContainer_add(dc, dependency) == DEPENDENCY_CONTAINER_VERSION_ERROR) {
				if (display_errors) {
					printf(" [ERROR] Dependency %s is required in version %s but version %s is already registered\n", dependency->name, dependency->version, DependencyContainer_get_dependency_by_name(dc, dependency->name)->version);
				}
			}

			free(line);
			free(dependency_url);
			free(dependency_version);

			line = NULL;
			dependency_url = NULL;
			dependency_version = NULL;
		} else {
			line = dstrcatc(line, ch);
		}
	} while(ch != EOF);

	fclose(dependency_file);

	dependency_file = NULL;
	dependency = NULL;
}

#endif