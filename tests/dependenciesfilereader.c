#include "assert.h"
#include "../dependenciesfilereader.h"
#include "../dependencycontainer.h"

int main()
{
	struct DependencyContainer *dc = DependencyContainer_create();

	get_all_dependencies_from_dependencies_file("dependencies", dc, 1);

	ei(1, dc->count);
}