#include "Webserv.hpp"

int Webserv::getMethod()
{
	logging("GET request", DEBUG);

	// 2 CGI FOR DOWNLOAD
	if (http_request->path.find("download.php") != std::string::npos && access("./over42/download.php", F_OK) == 0)
	{
		// std::cout << "./over42/download.php exists" << std::endl;
		return (getDownloadCgi());
	}
	else if (http_request->path.find("/over42/get_files.php") != std::string::npos && access("./over42/get_files.php", F_OK) == 0)
	{
		// std::cout << "/over42/get_files.php exists" << std::endl;
		return (getCgiFilesList());
	}
	else if (http_request->path.find("/over42/cgi-bin/index.py") != std::string::npos && access("./over42/cgi-bin/index.py", F_OK) == 0)
	{
		char *tmp = string_to_chararray(http_request->path);
		if (access("./over42/cgi-bin/index.py", X_OK) == 0)
		{

			// std::cout << "cgi-bin/index.py exists" << std::endl;
			// logging("cgi-bin/index.py exists", DEBUG);

			int pipefd[2];
			pipe(pipefd);
			if (fork() == 0)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				std::string tmp2 = "/over42/cgi-bin/index.py";
				delete[] tmp;
				tmp = string_to_chararray(tmp2);
				http_response->path = tmp2;
				char *const args[] = {tmp, NULL};
				execve(tmp, args, env);
			}
			else
			{
				close(pipefd[1]);
				char buffer[1024];
				std::string scriptOutput;
				ssize_t bytesRead;
				while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0)
				{
					buffer[bytesRead] = '\0';
					scriptOutput += buffer;
				}
				// std::cout << "scriptOutput: " << scriptOutput << std::endl;
				http_response->path = scriptOutput;
				// std::cout << "scripted http_request.path: " << http_request.path << std::endl;
				waitpid(-1, NULL, WUNTRACED);
			}
		}
		delete[] tmp;
		// http_response->isFile = true;
		return 200;
	}

	char *tmp = string_to_chararray(http_request->path);
	if (access(tmp, F_OK) == 0)
	{

		struct stat path_stat;
		stat(tmp, &path_stat);
		bool is_directory = S_ISDIR(path_stat.st_mode);

		if (!is_directory)
		{

			if (access(tmp, R_OK) == 0)
			{
				http_response->path = tmp;
				http_response->isFile = true;
				delete[] tmp;
				return 200;
			}
			else
			{
				delete[] tmp;
				return 404;
			}
		}
		else if (is_directory)
		{
			if (isSameLocation && !currentLocation->getAutoindex())
			{
				delete[] tmp;
				return 403;
			}

			if (http_request->path[http_request->path.size() - 1] != '/')
			{
				// Redirect to the path with a trailing slash
				// http_response->status_code = 301; // or 302
				http_response->headers["Location"] = http_request->path + "/";
				delete[] tmp;
				return 403;
			}
			std::string tmp2 = "." + http_request->path;

			http_response->path = autoindex(tmp2); // AUTOINDEX HERE
		}
		delete[] tmp;
		return 200;
	}
	else
	{
		logging("file doesn't exist", DEBUG);
		// std::cout << "file doesn't exist" << std::endl;
	}
	delete[] tmp;
	return 404;
}

int Webserv::getDownloadCgi()
{
	char *tmp = string_to_chararray(http_request->path);
	if (access("./over42/download.php", X_OK) == 0)
	{
		int pipefd[2];
		pipe(pipefd);
		if (fork() == 0)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);

			size_t filenamePTR = http_request->path.find("file=");
			std::string filename = http_request->path.substr(filenamePTR + 5);
			std::string fullName = "file=" + filename;

			std::string tmp2 = "/over42/download.php";
			delete[] tmp;
			tmp = string_to_chararray(tmp2);
			http_response->path = tmp2;
			char *const args[] = {tmp, strdup(fullName.c_str()), NULL};
			// std::cout << "tmp: " << tmp << " args: " << args[0] << std::endl;
			execve(tmp, args, env);
		}
		else
		{
			close(pipefd[1]);
			std::vector<char> buffer(1024);
			std::vector<char> content;

			ssize_t bytesRead;
			while ((bytesRead = read(pipefd[0], buffer.data(), buffer.size())) > 0)
			{
				content.insert(content.end(), buffer.begin(), buffer.begin() + bytesRead);
			}
			std::string bytedtoStr(content.begin(), content.end());
			http_response->path = bytedtoStr;
			// std::cout << "scripted http_request->path: " << http_request->path << std::endl;
			waitpid(-1, NULL, WUNTRACED);
		}
		delete[] tmp;
		return 777;
	}
	delete[] tmp;
	return 500;
}

int Webserv::getCgiFilesList()
{
	char *tmp = string_to_chararray(http_request->path);
	if (access("./over42/get_files.php", X_OK) == 0)
	{
		int pipefd[2];
		pipe(pipefd);
		if (fork() == 0)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			std::string tmp2 = "/over42/get_files.php";
			delete[] tmp;
			tmp = string_to_chararray(tmp2);
			http_response->path = tmp2;
			char *const args[] = {tmp, NULL};
			execve(tmp, args, env);
		}
		else
		{
			close(pipefd[1]);
			char buffer[1024];
			std::string scriptOutput;
			ssize_t bytesRead;
			while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0)
			{
				buffer[bytesRead] = '\0';
				scriptOutput += buffer;
			}
			http_response->path = scriptOutput;
			waitpid(-1, NULL, WUNTRACED);
		}
		delete[] tmp;
		return 999;
	}
	delete[] tmp;
	return 500;
}