#include "Location.hpp"

Location::Location()
{
	this->_locations = std::vector<Location*>();
	this->_file_path = "default";
	this->server_name["default"] = "Default Value";
	this->port["default"] = "Default Value";
	this->host["default"] = "Default Value";
	this->root["default"] = "Default Value";
	this->index["default"] = "Default Value";
	this->allow_methods["default"] = "Default Value";
	this->alias["default"] = "Default Value";
	this->cgi_pass["default"] = "Default Value";
	this->client_body_buffer_size["default"] = "Default Value";
	this->error_page["default"] = "Default Value";
}
Location::Location(std::string filename)
{
	this->_file_path = filename;
	this->_locations = std::vector<Location*>();
	this->server_name["default"] = "Default Value";
	this->port["default"] = "Default Value";
	this->host["default"] = "Default Value";
	this->root["default"] = "Default Value";
	this->index["default"] = "Default Value";
	this->allow_methods["default"] = "Default Value";
	this->alias["default"] = "Default Value";
	this->cgi_pass["default"] = "Default Value";
	this->client_body_buffer_size["default"] = "Default Value";
	this->error_page["default"] = "Default Value";
}
Location::~Location()
{
	for (size_t i = 0; i < _locations.size(); ++i)
		delete _locations[i];
}

Location::Location (const Location &copy)
{
	*this = copy;
}

Location & Location::operator = (const Location &copy)
{
	if (this != &copy)
		this->test = copy.test;
	return *this;
}
int	Location::Gettest() const
{
	return this->test;
}

void	Location::Settest(int test)
{
	this->test = test;
}

std::ostream	&operator<<(std::ostream &out, Location &to_write) // rajouter le const apr tt les tests
{
	out << "salut test " << to_write.Gettest();
	return (out);
}