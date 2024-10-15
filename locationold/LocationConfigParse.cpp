#include "Location.hpp"

/*int	Location::InitLocation(std::istringstream &iss, std::string directive, std::ifstream &file)
{
	struct stat info;
	std::string path;
	if (iss >> path && stat(path.c_str(), &info) == 0 && S_ISDIR(info.st_mode))
		this->AddLocation(path);
	else
		return (std::cout << "chemin pas valide\n", 0);
	if (iss >> path && path == "{")
		this->GetLocation(1)->LocationParse(file);
	else
		return (std::cout << "pas de {\n", 0);
	return (1);
}*/

void	Location::fonction(std::istringstream &iss, std::string directive, std::map<std::string, std::string>& option)
{
	std::string serverName;
	std::map<std::string, std::string>::iterator it = option.begin();
	option[it->first] = directive;
	if (iss >> serverName)
		option[it->second] = serverName;
	std::cout << option[it->first] << " ";
	std::cout << option[it->second] << std::endl;
}

int	Location::LProcessDirective(const std::string& line, std::ifstream &file)
{
	std::istringstream iss(line);
	std::string directive;
	std::vector<std::string> options;
	options.push_back("server_name");
	options.push_back("listen");
	options.push_back("root");
	options.push_back("index");
	options.push_back("allow_methods");
	options.push_back("location");
	options.push_back("alias");
	options.push_back("cgi_pass");
	options.push_back("client_body_buffer_size");
	options.push_back("}");
	options.push_back("host");

	if (!(iss >> directive)) {
		return 0;
	}
	std::vector<std::string>::iterator it = std::find(options.begin(), options.end(), directive);
	if (it != options.end()) {
		std::cout << "YIPI "<< directive << std::endl;
		int index = std::distance(options.begin(), it);
		switch(index)
		{
			case 0:
				std::cout<< "test\n";
				fonction(iss, directive, this->server_name);
				break;
			case 1:
				std::cout<< directive << "port\n";
				fonction(iss, directive, this->port);
				break;
			case 2:
				std::cout << "2" << std::endl;
				fonction(iss, directive, this->root);
				std::cout << "Found root" << std::endl;
				break;
			case 3:
				std::cout << "3" << std::endl;
				fonction(iss, directive, this->index);
				std::cout << "Found index" << std::endl;
				break;
			case 4:
				std::cout << "4" << std::endl;
				fonction(iss, directive, this->allow_methods);
				std::cout << "Found allow_methods" << std::endl;
				break;
			case 5:
				// a faire demain cheh
				std::cout << "5" << std::endl;
				//if (InitLocation(iss, directive, file) == 0)
				//	return (0);
				std::cout << "Found location" << std::endl;
				break;
			case 6:
				std::cout << "6" << std::endl;
				fonction(iss, directive, this->alias);
				std::cout << "Found alias" << std::endl;
				break;
			case 7:
				std::cout << "7" << std::endl;
				fonction(iss, directive, this->cgi_pass);
				std::cout << "Found cgi_pass" << std::endl;
				break;
			case 8:
				std::cout << "8" << std::endl;
				fonction(iss, directive, this->alias);
				std::cout << "Found client_body_buffer_size" << std::endl;
				break;
			case 9:
				std::cout << "9";
				std::cout << "end of server" << std::endl;
				return (2);
			case 10:
				std::cout << "10";
				fonction(iss, directive, this->host);
				std::cout << "host" << std::endl;
				break;
			case 11:
				std::cout << "11";
				fonction(iss, directive, this->error_page);
				std::cout << "errorpage"<< std::endl;
				break;
			default:
				std::cout << "Error : Unknown directive found" << std::endl;
		}
	}
	else
	{
		std::cout << "the directive " << directive << "is not inside the table !" << std::endl;
		return (0);
	}
	return (1);
}

int	Location::LocationParse(std::ifstream &file)
{
	std::string line;

	if (file.is_open())
		while (std::getline(file, line))
			if (LProcessDirective(line, file) == 2)
				break;
	std::cout << line;
	return(0);
}