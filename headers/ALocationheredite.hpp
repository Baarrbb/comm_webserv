#ifndef ALOCATIONHEREDITE_HPP
#define ALOCATIONHEREDITE_HPP

#include "Server.hpp"
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
#include <exception>
#include <unistd.h>

class Location : public Server
{
	public:
		Location();
		Location(std::string filename);
		~Location();
		Location(const Location &copy);
		Location & operator = (const Location &copy);
		void	WriteFilePath() const;
	private:
		std::string _file_path;
};

std::ostream	&operator<<(std::ostream &out, Location &to_write); // rajouter le const apr tt les tests


#endif