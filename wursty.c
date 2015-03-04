#include <unistd.h>
#include "dependenciesfilereader.h"
#include "dependencycontainer.h"
#include "dependency.h"
#include "dstr.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

void update_all_dependencies(struct DependencyContainer *dc, struct Dependency *d, const char *package_root_folder_path, const char *package_folder_path)
{
	struct DependencyContainer *ddc = DependencyContainer_create();
	char *dependency_file_path = NULL;
	char *dependency_package_folder = NULL;
	int i;

	dependency_file_path = dstrcpy(dependency_file_path, package_folder_path);
	dependency_file_path = dstrcat(dependency_file_path, "/dependencies");

	if (!get_all_dependencies_from_dependencies_file(dependency_file_path, ddc)) {
		printf("\n >> [WARN] dependencies file was not found\n");
	}

	for (i = 0; i < ddc->count; i++) {
		switch (DependencyContainer_add(dc, ddc->dependencies[i])) {
			case DEPENDENCY_CONTAINER_ADDED_CORRECTLY:
				if (d) {
					printf("\n >> Dependency %s requested by %s\n", ddc->dependencies[i]->name, d->name);
				} else {
					printf("\n >> Dependency %s\n", ddc->dependencies[i]->name);
				}

				printf(ANSI_COLOR_GREEN"    >> [OK] Updating dependency\n\n"ANSI_COLOR_RESET);

				dependency_package_folder = dstrcpy(dependency_package_folder, package_root_folder_path);
				dependency_package_folder = dstrcat(dependency_package_folder, "/");
				dependency_package_folder = dstrcat(dependency_package_folder, ddc->dependencies[i]->name);

				Dependency_update(ddc->dependencies[i], package_root_folder_path);
				update_all_dependencies(dc, ddc->dependencies[i], package_root_folder_path, dependency_package_folder);

				break;

			case DEPENDENCY_CONTAINER_VERSION_ERROR:
				if (d) {
					printf("\n >> Dependency %s requested by %s\n", ddc->dependencies[i]->name, d->name);
				} else {
					printf("\n >> Dependency %s\n", ddc->dependencies[i]->name);
				}
				printf(
					ANSI_COLOR_RED
					"    >> [ERROR] Dependency is required in version %s\n    >> but version %s is already registered by %s\n"
					ANSI_COLOR_RESET,
					ddc->dependencies[i]->version,
					DependencyContainer_get_dependency_by_name(dc, ddc->dependencies[i]->name)->version,
					DependencyContainer_get_dependency_by_name(dc, ddc->dependencies[i]->name)->name
				);

				break;
		}
	}

	DependencyContainer_destroy(ddc);

	free(dependency_file_path);
	free(dependency_package_folder);

	ddc = NULL;
	dependency_file_path = NULL;
	dependency_package_folder = NULL;
}

int main(int argc, char *args[])
{
	struct DependencyContainer *dc = DependencyContainer_create();
	char *project_root_path = NULL;
	char *dependencies_folder_path = NULL;
	char current_path[1024];

	if (argc == 2) {
		project_root_path = dstrcpy(project_root_path, args[1]);
	} else {
		getcwd(current_path, sizeof(current_path));
		project_root_path = dstrcpy(project_root_path, current_path);
	}

	dependencies_folder_path = dstrcpy(dependencies_folder_path, project_root_path);
	dependencies_folder_path = dstrcat(dependencies_folder_path, "/wurst/vendor");

	printf("\n >> Welcome to Wursty!\n");
	update_all_dependencies(dc, NULL, dependencies_folder_path, project_root_path);

	DependencyContainer_destroy(dc);

	free(project_root_path);
	free(dependencies_folder_path);

	dc = NULL;
	project_root_path = NULL;
	dependencies_folder_path = NULL;

	return 0;
}