#include "precomp.h"
#include "common/config.h"
#include "app/VsApp.h"
#include <memory>

int main(int argc, char *argv[])
{
    std::unique_ptr<VsApp> app(std::make_unique<VsApp>());
    if ( !app->Init() ) {
		std::cerr << "Cannot initialize the program!" << std::endl;
		return 1;
	}
	return app->Run();
}
