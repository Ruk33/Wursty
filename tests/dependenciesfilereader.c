#include "assert.h"
#include "../dependenciesfilereader.h"
#include "../dependencycontainer.h"

int main()
{
	struct DependencyContainer *dc = DependencyContainer_create();

	get_all_dependencies_from_dependencies_file("dependencies", dc);

	ec("Ruk33/WurstBuff", dc->dependencies[0]->name);
	ec("git@github.com:Ruk33/WurstBuff.git", dc->dependencies[0]->url);
	ec("master", dc->dependencies[0]->version);

	ec("Ruk33/wursty-test-dependency", dc->dependencies[1]->name);
	ec("git@github.com:Ruk33/wursty-test-dependency.git", dc->dependencies[1]->url);
	ec("master", dc->dependencies[1]->version);

	get_all_dependencies_from_dependencies_file("dependencies", dc);
	get_all_dependencies_from_dependencies_file("dependencies2", dc);

	ei(2, dc->count);

	DependencyContainer_destroy(dc);
	dc = NULL;
}