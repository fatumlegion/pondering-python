#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include <memory>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

class Application
{
private:
	static std::unique_ptr<Application> m_App;
		
	bool parseArguments(int argc, char **argv);
	void printUsage(const char* name);
	bool parseFile();
	int calculate();
	
	std::vector<std::vector<int> > lines;
	std::fstream file;
	
	std::string filename;
	bool doFancyOutput;
public:
	static std::unique_ptr<Application> getSingleton();
	
	void initialize();
	int run(int argc, char **argv);
};
#endif