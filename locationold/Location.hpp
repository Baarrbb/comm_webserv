#ifndef LOCATION_HPP
#define LOCATION_HPP


#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <cerrno>
#include <cstdlib>


class Location
{
	public:
		Location();
		Location(std::string filename);
		~Location();
		Location(const Location &copy);
		Location & operator = (const Location &copy);
		void					fonction(std::istringstream &iss, std::string directive, std::map<std::string, std::string>& option);
		int						LProcessDirective(const std::string& line, std::ifstream &file);
		int						LocationParse(std::ifstream &file);
		//int						InitLocation(std::istringstream &iss, std::string directive, std::ifstream &file);
		//setter / getters
		// template get/seter
		int	Gettest() const;
		void Settest(int test);
	private:
		std::string 						_file_path;
		std::vector<Location*>				_locations;
		std::map<std::string, std::string>	server_name;
		std::map<std::string, std::string>	port;
		std::map<std::string, std::string>	host;
		std::map<std::string, std::string>	root;
		std::map<std::string, std::string>	index;
		std::map<std::string, std::string>	allow_methods;
		std::map<std::string, std::string>	alias;
		std::map<std::string, std::string>	cgi_pass;
		std::map<std::string, std::string>	client_body_buffer_size;
		std::map<std::string, std::string>	error_page;
		int			test;
};

std::ostream	&operator<<(std::ostream &out, Location &to_write); // rajouter le const apr tt les tests

#endif