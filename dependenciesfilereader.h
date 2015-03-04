#include <string.h>
#include <ctype.h>
#include "dependency.h"
#include "dependencycontainer.h"
#include "dependency.h"
#include "dstr.h"

#ifndef DEPENDENCIES_FILE_READER_H_INCLUDED
#define DEPENDENCIES_FILE_READER_H_INCLUDED

int get_all_dependencies_from_dependencies_file(const char *path, struct DependencyContainer *dc)
{
	FILE *dependency_file = fopen(path, "r");
	struct Dependency *dependency = NULL;
	char *line = NULL;
	char *dependency_url = NULL;
	char *dependency_version = NULL;
	char ch = NULL;

	if (!dependency_file) {
		return 0;
	}

	dependency = Dependency_create();

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

			Dependency_set_url(dependency, dependency_url);
			Dependency_set_name_from_url(dependency);
			Dependency_set_version(dependency, dependency_version);

			DependencyContainer_add(dc, dependency);

			line = dstrcpy(line, NULL);

			free(dependency_version);
			dependency_version = NULL;
		} else {
			line = dstrcatc(line, ch);
		}
	} while(ch != EOF);

	Dependency_destroy(dependency);

	fclose(dependency_file);

	free(line);
	free(dependency_url);

	dependency_file = NULL;
	dependency = NULL;
	line = NULL;
	dependency_url = NULL;

	return 1;
}

#endif