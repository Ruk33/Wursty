#include "dependenciesfilereader.h"
#include "dependencycontainer.h"
#include "dependency.h"
#include "dstr.h"

int main(int argc, char *args[])
{
    struct DependencyContainer *dc = DependencyContainer_create();
    char *dependencies_file_path = NULL;
    int i;

    if (argc == 2) {
        dependencies_file_path = dstrcpy(dependencies_file_path, args[1]);
    } else {
        dependencies_file_path = dstrcpy(dependencies_file_path, "wurst/vendor/dependencies");
    }

    printf("\n'%s'\n", dependencies_file_path);

    get_all_dependencies_from_dependencies_file(dependencies_file_path, dc, 1);

    for (i = 0; i < dc->count; i++) {
        printf("%s\n", dc->dependencies[i]->name);
    }

    free(dependencies_file_path);
    dependencies_file_path = NULL;

    return 0;
}