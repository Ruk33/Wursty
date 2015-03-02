#include <string.h>
#include "dependency.h"
#include "dependencycontainer.h"
#include "dependency.h"
#include "setstr.h"

#ifndef DEPENDENCIES_FILE_READER_H_INCLUDED
#define DEPENDENCIES_FILE_READER_H_INCLUDED

void get_all_dependencies_from_dependencies_file(const char *path, struct DependencyContainer *dc)
{
	FILE *dependency_file = fopen(path, "r");
	struct Dependency *dependency;
	char *dependency_url = NULL;
	char *dependency_version = NULL;
	char in_version = 0;
	char ch = NULL;

	do {
		ch = fgetc(dependency_file);

		if (ch == '\n' || ch == EOF) {
			dependency = Dependency_create_from_url(dependency_url);

			if (DependencyContainer_add(dc, dependency) == -1) {
				printf("we got a version error");
			} else {
				printf("dependency added\n");
			}

			free(dependency_url);
			free(dependency_version);

			dependency_url = NULL;
			dependency_version = NULL;

			in_version = 0;
		} else if (ch == ',') {
			in_version = 1;
		} else {
			if (in_version == 0) {
				dependency_url = appstr(dependency_url, &ch);
			} else {
				dependency_version = appstr(dependency_version, &ch);
			}
		}
	} while(ch != EOF);

	printf("%s\n", dependency_url);
	printf("%s\n", dependency_version);

	fclose(dependency_file);

	dependency_file = NULL;
	dependency = NULL;
}

#endif