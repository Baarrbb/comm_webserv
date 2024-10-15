#include "Config.hpp"

int	main(int argc, char **argv, char **envp)
{
	if (argc != 2)
	{
		std::cout << "Please insert a config file there." << std::endl;
		std::cout << "./webserv [configuration file]" << std::endl;
		return 0;
	}
	(void)argv;
	std::string file_name = argv[1];
	Config test(file_name);
	if (test.ParseGlobal() == 1)
		return (1);
	std::cout << test << std::endl;
	if (test.ServerStart(envp) == 1)
		return (1);
	return (0);
}

