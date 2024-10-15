/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:00:18 by marvin            #+#    #+#             */
/*   Updated: 2024/10/15 21:08:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"

Response::Response( RequestClient req, std::vector<Server*> serv, std::string host, uint16_t port )
	: version("HTTP/1.1")
{
	std::cout << "host:port " << host << ":" << port << std::endl;

	try
	{
		Server	server = this->findConfig(serv, host, port);
	}
	catch(...)
	{
		return ;
	}

	this->addBody( serv, req.getTarget() );

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
					return *serv[i];
		}
	}

	throw Response::NoMatchingConfig();
}


void	Response::addBody( Server serv, std::string target )
{
	(void)serv;
	(void)target;
}

std::string Response::getFull( void )
{
	return this->full;
}