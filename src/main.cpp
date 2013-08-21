#include "Application.hpp"

int main(int argc, char **argv)
{
	std::unique_ptr<Application> p = Application::getSingleton();
	p->initialize();
	return p->run(argc, argv);
}