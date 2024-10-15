/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:00:18 by marvin            #+#    #+#             */
/*   Updated: 2024/10/16 01:30:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"

Response::Response( RequestClient req, std::vector<Server*> serv, std::string host, uint16_t port )
	: version("HTTP/1.1")
{
	std::cout << "host:port " << host << ":" << port << std::endl;

	Server	server;
	try
	{
		int err = req.getError();
		server = this->findConfig(serv, host, port);
		this->file = this->findFile(server, req.getTarget(), err);
	}
	catch(RequestClient::ErrorRequest& e)
	{
		req.setError(e.getError());
		req.setTarget(e.getTarget());
		req.setMsgError(e.getMsg());
		this->file = req.getTarget();
	}
	
	this->addBody(this->file);

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
	
	this->full = this->version + " " + this->code + " " + this->msg + "\n";
	this->full += "Content-Length: " + lengthBody() + "\n";
	this->full += "\n";
	this->full += this->body + "\n";
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
			if ((serv[i]->GetHost(j).compare(host) || serv[i]->GetHost(j).compare("0.0.0.0"))
				&& serv[i]->GetPort(j).compare(sport))
					return (*serv[i]);
		}
	}

	std::cout << "G PAS DE CONFIG ??" << std::endl;
	throw Response::NoMatchingConfig();
}

std::string	Response::lengthBody( void )
{
	std::stringstream len;
	len << this->body.length();
	return len.str();
}

std::string	Response::findFile( Server serv, std::string target, int err )
{
	std::string			path = serv.GetRoot();
	std::ifstream		file;
	std::string			filename;
	
	if (!target.compare("/"))
	{
		size_t i = 0;
		for(; i < serv.GetIndex().size(); i++)
		{
			filename = path.append("/").append(serv.GetIndex(i));
			file.open(filename.c_str());
			if (file.is_open())
			{
				file.close();
				return filename;
			}
		}
		if (i == serv.GetIndex().size())
			throw RequestClient::ErrorRequest(404, "./not_found/404.html", "Not Found");
	}
	else if (!err)
		filename = path.append(target);
	
	std::cout << filename << std::endl;
	file.open(filename.c_str());
	if (!file.is_open())
		throw RequestClient::ErrorRequest(404, "./not_found/404.html", "Not Found");

	file.close();
	return filename;
}

void	Response::addBody(std::string filename)
{
	std::ifstream		file(filename.c_str());
	std::stringstream	fileStream;
	fileStream << file.rdbuf();

	std::string	fileContent = fileStream.str();
	this->body = fileContent;
}

std::string Response::getFull( void )
{
	return this->full;
}
