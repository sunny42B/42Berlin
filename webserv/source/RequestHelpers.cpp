#include "Webserv.hpp"

void Webserv::newOrAppendRequest(size_t i)
{
	int clientFD = poll_fd[i].fd;

	if (http_requests.count(clientFD) > 0)
	{
		http_request = http_requests[clientFD];
		// std::cout << "Content size before append: " << http_request->content.size() <<std::endl;

		http_request->content.insert(http_request->content.end(), in_request[clientFD].begin(),
									 in_request[clientFD].end());

		http_requests[clientFD] = http_request;
		// std::cout << "APPEND REQUEST" << std::endl;
		// std::cout << "Content size after append: " << http_request->content.size() <<std::endl;
	}
	else
	{

		http_request = parse_http_request(in_request[clientFD]);
		http_requests[clientFD] = http_request;
		// std::cout << "NEW REQUEST" << std::endl;
	}
}

bool isDelim(const std::vector<uint8_t> &request, std::size_t position, const std::vector<uint8_t> &delimiter)
{
	for (size_t i = 0; i < delimiter.size(); ++i)
	{
		if (position + i >= request.size() || request[position + i] != delimiter[i])
		{
			return false;
		}
	}
	return true;
}

void Request::parseBodyReq()
{
	std::istringstream sstream(std::string(this->body.begin(), this->body.end()));
	// The request line format is: METHOD PATH HTTP/VERSION
	sstream >> this->method >> this->path >> this->http_version;
	// Parse each header line
	std::string line;
	while (std::getline(sstream, line) && !line.empty())
	{

		size_t colonPos = line.find(": ");
		if (colonPos != std::string::npos)
		{
			// Extract key and value
			std::string key = line.substr(0, colonPos);
			std::string value = line.substr(colonPos + 2);

			// Remove leading and trailing whitespace from the value
			value.erase(0, value.find_first_not_of(" \t\r"));
			value.erase(value.find_last_not_of(" \t\r") + 1);

			this->headers[key] = value;
		}
	}
	if (this->headers.find("Content-Type") != this->headers.end())
	{
		std::string boundaryPrefix = "boundary=";
		std::string contentType = this->headers["Content-Type"];
		size_t boundaryOffset = contentType.find(boundaryPrefix);
		if (boundaryOffset != std::string::npos)
		{
			boundaryOffset += boundaryPrefix.length();
			size_t boundaryLen = contentType.length() - boundaryOffset;
			this->boundary = contentType.substr(boundaryOffset, boundaryLen);
			this->boundary += "\r\n";
		}
	}
}

bool canSeparate(const std::vector<uint8_t> &request, size_t &delimIndex)
{
	const uint8_t delimArray[] = {13, 10, 13, 10};
	const std::vector<uint8_t> delim(delimArray, delimArray + sizeof(delimArray) / sizeof(delimArray[0]));

	for (size_t i = 0; i < request.size(); ++i)
	{
		if (isDelim(request, i, delim))
		{
			delimIndex = i;
			return true;
		}
	}
	return false;
}

Request *Webserv::parse_http_request(const std::vector<uint8_t> &request)
{

	http_request = new Request();

	size_t delimIndex = 0;

	if (canSeparate(request, delimIndex))
	{
		http_request->body.assign(request.begin(), request.begin() + delimIndex + 4);
		http_request->content.assign(request.begin() + delimIndex + 4, request.end());
	}
	if (!http_request->body.empty())
	{
		http_request->parseBodyReq();
	}
	return http_request;
}

void Webserv::deleteRequest(int i)
{
	std::map<int, Request *>::iterator it = http_requests.find(i);

	if (it != http_requests.end())
	{
		Request *http_request = it->second;

		// Erase the entry from the map
		http_requests.erase(it);

		// Delete the object (free the memory)
		delete http_request;
	}
	else
	{
		logging("I DONT DELETE REQUEST", DEBUG);
		// std::cout << "I DONT DELETE REQUEST\n";
	}
}

// void Request::parseCookies() {
//     // Parse incoming cookies from headers and update internal data structures
//     // Find the "Cookie" header in the headers map
//     auto cookieHeader = headers.find("Cookie");

//     // If "Cookie" header is found
//     if (cookieHeader != headers.end()) {
//         // Extract the cookie header value
//         std::string cookieValue = cookieHeader->second;

//         // Tokenize the cookie value based on the semicolon and space separator
//         std::istringstream cookieStream(cookieValue);
//         std::string cookie;
//         while (std::getline(cookieStream, cookie, ';')) {
//             // Split each token into key-value pairs based on the equal sign
//             size_t equalPos = cookie.find('=');
//             if (equalPos != std::string::npos) {
//                 std::string name = cookie.substr(0, equalPos);
//                 std::string value = cookie.substr(equalPos + 1);

//                 // Add the cookie to your internal data structure
//                 cookies[name] = value;
//             }
//         }
//     }
// }

// std::map<std::string, std::string> Request::getCookies() const {
//     return cookies;
// }