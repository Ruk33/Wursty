#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "dependency.h"

#define UPDATE_ARGUMENT "run"
#define MAX_DEPENDENCIES 20
#define DEPENDENCIES_FOLDER "wurst/vendor/"

/**
 * Store dependencies who has been already loaded (to avoid cyclic problems)
 */
char loaded_dependencies[MAX_DEPENDENCIES][1024];

/**
 * Amount of loaded dependencies
 */
int loaded_dependencies_count = 0;

/**
 * @todo
 */
void display_help()
{
	printf("Displaying help\n");
}

void get_name_from_dependency_url(char *name, const char *url)
{
	char *r = strchr(url, ':');

	// Remove ":"
	r++;

	strcpy(name, r);

	// Remove .git from name
	name[strlen(name)-4] = '\0';
}

char dependency_is_already_loaded(const char *dependency)
{
	char is_loaded = 0;
	int i;

	for (i = 0; i <= loaded_dependencies_count; i++) {
		if (strcmp(dependency, loaded_dependencies[i]) == 0) {
			is_loaded = 1;
			break;
		}
	}

	return is_loaded;
}

void mark_dependency_as_loaded(const char *dependency)
{
	strcpy(loaded_dependencies[loaded_dependencies_count], dependency);
	loaded_dependencies_count++;
}

void update_dependency(const char *dependency)
{
	char dependency_name[1024];
	char dependency_path[1024];
	char current_path[1024];
	char command[100];
	struct stat s;

	get_name_from_dependency_url(dependency_name, dependency);

	strcpy(dependency_path, "");

	strcat(dependency_path, DEPENDENCIES_FOLDER);
	strcat(dependency_path, dependency_name);

	strcpy(command, "");

	stat(dependency_path, &s);

	// If folder already exists
	if (s.st_mode & S_IFDIR) {
		getcwd(current_path, sizeof(current_path));
		strcat(current_path, "/");
		strcat(current_path, dependency_path);

		strcat(command, "cd ");
		strcat(command, dependency_path);
		strcat(command, "&& git pull origin master");
	} else {
		strcat(command, "git clone --progress --quiet ");
		strcat(command, dependency);
		strcat(command, " ");
		strcat(command, dependency_path);
	}

	system(command);
	mark_dependency_as_loaded(dependency);
}

void get_all_dependencies_from_file(FILE *dependency_file, char dependencies[MAX_DEPENDENCIES][1024], int *dependencies_count)
{
	char has_dependencies = 0;
	int i = 0;
	char ch;

	*dependencies_count = 0;

	if (!dependency_file) {
		return;
	}

	while ((ch = fgetc(dependency_file)) != EOF) {
		has_dependencies = 1;

		if (ch == '\n') {
			++*dependencies_count;
			i = 0;
		} else {
			dependencies[*dependencies_count][i] = ch;
			i++;
		}
	}

	if (has_dependencies) {
		++*dependencies_count;
	}
}

void get_all_unload_dependencies_from_file(FILE *dependency_file, char dependencies[MAX_DEPENDENCIES][1024], int *dependencies_count)
{
	char all_dependencies[MAX_DEPENDENCIES][1024];
	int all_dependencies_count;
	int i;

	get_all_dependencies_from_file(dependency_file, all_dependencies, &all_dependencies_count);

	*dependencies_count = 0;

	for (i = 0; i < all_dependencies_count; i++) {
		if (dependency_is_already_loaded(all_dependencies[i]) == 0) {
			strcpy(dependencies[*dependencies_count], all_dependencies[i]);
			++*dependencies_count;
		}
	}
}

void run_update_command(const char *path)
{
	char dependency_file_path[1024];
	FILE *dependency_file;

	char dependencies[MAX_DEPENDENCIES][1024];
	int dependencies_count;

	char dependency_name[1024];
	char dependency_dependencies_file_path[1024];

	int i;

	strcpy(dependency_file_path, "");

	strcat(dependency_file_path, path);
	strcat(dependency_file_path, "dependencies");

	dependency_file = fopen(dependency_file_path, "r");

	get_all_unload_dependencies_from_file(dependency_file, dependencies, &dependencies_count);

	for (i = 0; i < dependencies_count; i++) {
		get_name_from_dependency_url(dependency_name, dependencies[i]);

		printf("\n >> Updating dependency %s\n", dependency_name);
		
		strcpy(dependency_dependencies_file_path, "");

		strcat(dependency_dependencies_file_path, DEPENDENCIES_FOLDER);
		strcat(dependency_dependencies_file_path, dependency_name);
		strcat(dependency_dependencies_file_path, "/");

		update_dependency(dependencies[i]);
		run_update_command(dependency_dependencies_file_path);
	}

	fclose(dependency_file);
}

int main(int argc, char *args[])
{
	if (argc > 1) {
		if (strcmp(args[1], UPDATE_ARGUMENT) == 0) {
			printf("\nUpdating the dependencies\n");
			
			run_update_command("");

			printf("\nAll dependencies updated\n");
		} else {
			display_help();
		}
	} else {
		display_help();
	}
	
	return 0;
}