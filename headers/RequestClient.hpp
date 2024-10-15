/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestClient.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:41:14 by marvin            #+#    #+#             */
/*   Updated: 2024/10/15 18:09:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTCLIENT_HPP
#define REQUESTCLIENT_HPP

#include "Webserv.hpp"
// #include "Server.hpp"
// #include <exception>
// #include <vector>
// #include <map>



class RequestClient
{
	public:
		RequestClient(std::string &);
		~RequestClient( void );

		std::string	getTarget( void );
		int			getError( void );
		std::string	getMsgError( void );

		void		setTarget(std::string);
		void		setError(int);

	private:
		RequestClient( void );
		void	badSyntax( std::string line );

		int		checkIfHost( void );
		void	addMethod( std::string );
		void	addHost( void );
		int		addTarget( std::string );
		void	addOptions( std::string );

		void	othersOptions( std::string );

		int									error;
		std::string							msgError;
		std::string							method;
		std::string							target;
		std::string							host;
		std::string							query; // jsp si je prends en charge :'(
		std::map<std::string, std::string>	options;

	public:
		class ErrorRequest : public std::exception
		{
			public:
				ErrorRequest(int code, std::string file, std::string msg)
				{
					this->code = code;
					this->filename = file;
					this->msg = msg;
				}
				virtual ~ErrorRequest ( void ) throw() {}

				int	getError( void )
				{
					return this->code;
				}

				std::string	getTarget( void )
				{
					return this->filename;
				}

				std::string	getMsg( void )
				{
					return this->msg;
				}

			private:
				int			code;
				std::string	filename;
				std::string	msg;
		};
};

std::string	badRequest( std::string  );
std::string	notAllowed( std::string  );
std::string	badVersion( std::string );
std::string	reqResponse(RequestClient &);

#endif