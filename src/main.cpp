#include "../models/demo.h"
#include "app/Application.h"
#include "log.h"

int main()
{	
	Application* app = new Application(15, 5);

	while(app->isRunning())
		app->run();

	delete app;
	return 0;
}
