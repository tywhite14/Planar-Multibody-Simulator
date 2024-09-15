#include "../models/demo.h"
#include "app/Application.h"
#include "log.h"

int main()
{	
	Application* app = new Application;

	while(app->isRunning())
		app->run();

	return 0;
}
