/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:43:52 by fhassoun          #+#    #+#             */
/*   Updated: 2024/01/22 14:04:07 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server()
{
}

Server::~Server()
{
}

Server::Server(Server const &src)
{
	*this = src;
}

Server &Server::operator=(Server const &src)
{
	if (this == &src)
		return (*this);
	return (*this);
}

std::map<int, std::string> Server::getInRequest()
{
	return (in_request);
}

std::map<int, std::string> Server::getOutResponse()
{
	return (out_response);
}

int Server::getSockfd()
{
	return (sockfd);
}

void Server::setInRequest(std::map<int, std::string> in_request)
{
	this->in_request = in_request;
}

void Server::setOutResponse(std::map<int, std::string> out_response)
{
	this->out_response = out_response;
}

void Server::parseConfig(char *path)
{
	// open the file
	std::fstream conf;
	std::string str;
	Config tmpConf;

	// memset(&tmpConf, 0, sizeof(tmpConf));
	std::vector<Config>::iterator iter = this->_config.begin();

	conf.open(path, std::ifstream::in);
	if (!conf.is_open())
	{
		std::cout << "Error : could not open config-file.\nUsing Default!" << std::endl;
	}

	// if (std::getline(conf, str).eof())
	// {
	// 	std::cout << "Error : File empty or no data in.\nUsing Default!" << std::endl;
	// }

	while (!std::getline(conf, str).eof())
	{
		if (str.compare("server {") == 0)
		{

			// tmpConf = new Config();

			std::cout << "server start" << std::endl;
		}
		else if (str.compare("}") == 0)
		{

			this->_config.push_back(tmpConf);

			// std::cout << "after push_back start this: " << this->_config.begin()->getListen() << std::endl;
			// delete tmpConf;
			iter++;
			std::cout << "server end" << std::endl;
		}
		else
		{
			// std::cout << str << std::endl;
			// if (str.find("listen") != std::string::npos)
			// {
			// 	// std::cout << "listen" << std::endl;
			// 	tmpConf.setListen(str);
			// 	std::cout << "parsed port: " << tmpConf.getListen() << std::endl;
			// }
		}
	}

	// read the file
	// parse the file
	// create a config object
	// add the config object to the vector
	// repeat for the next config

	std::cout << "config parsed :)" << std::endl;
	conf.close();
}

void Server::init_server(int port, int backlog)
{

	// int sockfd;
	int rc, on;
	// pollfd fds[200];

	rc = 0;
	on = 1;
	sockaddr_in sockaddr;
	std::vector<Client> clients;

	// Create a socket (IPv4, TCP)
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	// std::cout << "sockfd: " << sockfd << std::endl;
	if (sockfd == -1)
	{
		std::cout << "Failed to create socket. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}

	// Allow socket descriptor to be reuseable
	rc = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
	if (rc < 0)
	{
		std::cout << "setsockopt() failed" << std::endl;
		close(sockfd);
		exit(EXIT_FAILURE);
	}
	rc = fcntl(sockfd, F_SETFL, O_NONBLOCK, FD_CLOEXEC);
	if (rc < 0)
	{
		std::cout << "fcntl() failed" << std::endl;
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	// Listen to port  on any address
	ft_memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = INADDR_ANY;
	ft_memcpy(&sockaddr.sin_addr, &sockaddr.sin_addr.s_addr,
			  sizeof(sockaddr.sin_addr.s_addr)); // do we need this line it?

	sockaddr.sin_port = htons(port); // htons is necessary to convert a number to
	// network byte order

	// Bind the socket to the specified IP address
	rc = bind(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));
	if (rc < 0)
	{
		std::cout << "Failed to bind to port " << port << ". errno: " << errno << std::endl;
		close(sockfd);
		exit(EXIT_FAILURE);
	}
	// Start listening. Hold at most 100 connections in the queue
	rc = listen(sockfd, backlog);
	if (rc < 0)
	{
		std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	// setup poll structure
	//  ft_memset(fds, 0 , sizeof(fds));
	this->sockfd = sockfd;
}

// void Server::handleRequest(Request& request, Response& response) {
//     // Check for valid session cookies, generate new session ID if needed
//     // Retrieve or create session data based on session ID
//     // Process the request and generate the response

// 		// request.parseCookies();

//     // // Now, you can access the parsed cookies from the cookies map
//     // std::map<std::string, std::string> cookies = request.getCookies();
// 		// if (cookies.find("session_id") != cookies.end()) {
//     //     // Session ID exists in cookies
//     //     // Perform logic based on session ID
//     // } else {
// 		// 		// Session ID does not exist in cookies
// 		// 		// Generate a new session ID and store it in the cookies map
// 		// 		cookies["session_id"] = generateSessionId();
// 		// }
// 		// Check for valid session cookies, generate new session ID if needed
//     request.parseCookies();
//     std::map<std::string, std::string> cookies = request.getCookies();

//     if (cookies.find("session_id") != cookies.end()) {
//         // Session ID exists in cookies
//         // Perform logic based on session ID
//         response.setStatusCode(200);
//         response.setBody("Welcome, existing user!");
//     } else {
//         // Session ID does not exist in cookies
//         // Generate a new session ID and store it in the cookies map
//         cookies["session_id"] = generateSessionId();
//         response.setStatusCode(200);
//         response.setBody("Welcome, new user!");

//         // Set the session ID cookie in the response
//         response.setCookie("session_id", cookies["session_id"]);
//     }
// }

// std::string Server::generateSessionId() {
//     // You can use a library or your own logic to generate a unique session ID
//     // For simplicity, let's use a basic method for illustration
//     srand(time(NULL));
//     const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
//     const int sessionIdLength = 32;  // Adjust the length as needed

//     std::string sessionId;
//     for (int i = 0; i < sessionIdLength; ++i) {
//         sessionId += chars[rand() % chars.length()];
//     }

//     return sessionId;
// }