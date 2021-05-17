#include "WinApp.h"
#include <memory>

int main()
{
	std::unique_ptr<WinApp> app = std::make_unique<WinApp>();
	app->StartOpenGL();
}