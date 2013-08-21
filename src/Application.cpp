#include "Application.hpp"
#include <stdio.h>
#include <string.h>

std::unique_ptr<Application> Application::m_App = nullptr;

std::unique_ptr<Application> Application::getSingleton()
{
	if (m_App == nullptr)
		m_App = std::unique_ptr<Application>(new Application);
	return std::move(m_App);
}

void Application::initialize()
{
	doFancyOutput = false;
}

bool Application::parseFile()
{
	file.open(filename.c_str());
	
	if (!file)
	{
		printf("Oh no!  The file \"%s\" doesn't exist.\n", filename.c_str());
		return false;
	}
	else
	{
		std::string line;
		int number;
		
		while (std::getline(file, line))
		{
			lines.push_back(std::vector<int>());
			std::istringstream iss(line);
			while (iss >> number)
			{
				lines.back().push_back(number);
			}
		}
		
		std::reverse(lines.begin(), lines.end());
	}
	
	return true;
}

int Application::calculate()
{
	for (int i = 0; i < lines.size() - 1; ++i)
	{
		std::vector<int> &current = lines.at(i);
		std::vector<int> &next = lines.at(i + 1);

		for (int j = 0; j < current.size() - 1; ++j)
		{
			if (current[j] >= current[j + 1])
			{
				next[j] += current[j];
			}
			else
			{
				next[j] += current[j + 1];
			}
		}
	}

	return lines.back()[0];
}

void Application::printUsage(const char *name)
{
	printf("usage: %s [-f, --file <file name>] [-v, --version] [-F, --fancy]\n", name);
}

bool Application::parseArguments(int argc, char **argv)
{
	if (argc == 1)
	{
		printUsage(argv[0]);
		return false;
	}
	else
	{
		for (int i = 1; i < argc; ++i)
		{
			if ((strcmp(argv[i], "-f") == 0) || (strcmp(argv[i], "--file") == 0))
			{
				if (argv[i + 1] == NULL)
				{
					printUsage(argv[0]);
					return false;
				}
				
				filename = argv[i + 1];
			}
			else if ((strcmp(argv[i], "-v") == 0) || (strcmp(argv[i], "--version") == 0))
			{
				printf("Version: %s\n", "13.37");
				return false;
			}
			else if ((strcmp(argv[i], "-F") == 0) || (strcmp(argv[i], "--fancy") == 0))
			{
				//requires the user to have "toilet" installed on their system
				doFancyOutput = true;
			}
			else
			{
				if (argv[i][0] == '-')
					printf("Warning: Unrecognized argument \"%s\".\n", argv[i]);
			}
		}
	}
	
	if (filename.empty())
	{
		printUsage(argv[0]);
		return false;
	}
	
	return true;
}

int Application::run(int argc, char **argv)
{
	if (!parseArguments(argc, argv)) return 1;
	
	if (parseFile())
	{
		int number = calculate();
	
		if (doFancyOutput == true)
		{
			//Using system() here sense we don't need to do anything with the data returned
			std::ostringstream oss;
			oss << "toilet -f mono9 -F gay " << number;
			system(oss.str().c_str());
		}
		else
		{
			printf("=======================================\n");
			printf("Result: %i\n", number);
			printf("=======================================\n");
		}
	}
		
	file.close();
	
	return 0;
}