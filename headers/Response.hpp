/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:36:45 by marvin            #+#    #+#             */
/*   Updated: 2024/10/16 00:12:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP


#include "Webserv.hpp"

class RequestClient;
class Server;

class Response
{
	public:
		Response( RequestClient, std::vector<Server*>, std::string, uint16_t );
		~Response( void );

		std::string	getFull( void );

	private:
		std::string	version;
		std::string	code;
		std::string	msg;
		std::string	body;
		std::string	full;
		std::string	file;

		Server		findConfig( std::vector<Server*>, std::string, uint16_t );
		std::string	findFile( Server, std::string, int );
		void		addBody( std::string );
		std::string	lengthBody( void );

	class NoMatchingConfig : public std::exception
	{
		public :
			
	};

};

#endif