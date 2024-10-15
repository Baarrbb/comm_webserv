/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:00:18 by marvin            #+#    #+#             */
/*   Updated: 2024/10/15 23:17:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"

Response::Response( RequestClient req, std::vector<Server*> serv, std::string host, uint16_t port )
	: version("HTTP/1.1")
{
	std::cout << "host:port " << host << ":" << port << std::endl;

	try
	{
		Server	server;
		server = this->findConfig(serv, host, port);
		// std::cout << "2 " << server << std::endl;
		this->addBody(server, req.getTarget());
	}
	catch(...)
	{
		return ;
	}

	if (!req.getError())
	{
		this->code = "200";
		this->msg = "OK";
	}
	else
	{
		std::stringstream ss;
		ss << req.getError();
		this->code = ss.str();
		this->msg = req.getMsgError();
	}
	
	this->full = this->version + " " + this->code + " " + this->msg + "\n\n";
	this->full += this->body;
}

Response::~Response( void )
{
}

Server	Response::findConfig( std::vector<Server*> serv, std::string host, uint16_t port)
{
	std::stringstream ssport;
	ssport << port;
	std::string sport = ssport.str();

	for (size_t i = 0; i < serv.size(); i++)
	{
		for (size_t j = 0; j < serv[i]->GetPort().size(); j++ )
		{
			std::cout << i << ":" << serv[i]->GetHost(j) << std::endl;
			std::cout << i << ":" << serv[i]->GetPort(j) << std::endl;

			if ((serv[i]->GetHost(j).compare(host) || serv[i]->GetHost(j).compare("0.0.0.0"))
				&& serv[i]->GetPort(j).compare(sport))
				{
					// std::cout << "1 " << *serv[i] << std::endl;
					return (*serv[i]);
				}
		}
	}

	std::cout << "G PAS DE CONFIG ??" << std::endl;
	throw Response::NoMatchingConfig();
}


void	Response::addBody( Server serv, std::string target )
{
	std::cout << "KKKKKKKKKKK" << std::endl;
	std::cout << serv << std::endl;
	std::string			path = serv.GetRoot();
	std::ifstream		file;
	std::stringstream	fileStream;
	std::string			filename;
	
	if (!target.compare("/"))
	{
		size_t i = 0;
		for(; i < serv.GetIndex().size(); i++)
		{
			std::cout << "index " << serv.GetIndex(i) << std::endl;
			filename = path.append("/").append(serv.GetIndex(i));
			std::cout << "filename " << filename << std::endl;
			file.open(filename.c_str());
			if (file.is_open())
				break ;
		}
		if (i == serv.GetIndex().size())
			throw RequestClient::ErrorRequest(404, "./not_found/404.html", "Not Found");
	}
	else
		filename = path.append(target);
	
	std::cout << "j'ai segfault AVANT ??" << std::endl;

	if (!target.compare("/"))
		file.open(filename.c_str());
	if (!file.is_open())
		throw RequestClient::ErrorRequest(404, "./not_found/404.html", "Not Found");
	std::cout << "j'ENCORE segfault AVANT ??" << std::endl;
	fileStream << file.rdbuf();
	std::string	fileContent = fileStream.str();
	this->body = fileContent;
}

std::string Response::getFull( void )
{
	return this->full;
}