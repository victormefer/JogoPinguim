#ifndef EXCECOES_H
#define EXCECOES_H

#include <exception>
#include <string>

class ExcecaoTextura : public std::exception
{
public:

	ExcecaoTextura(std::string msg)
	{
		this->msg = msg;
	}

	virtual const char* what() const throw()
	{
		return msg.c_str();
	}

private:
	std::string msg;
};

class ExcecaoArquivo : public std::exception
{
public:

	ExcecaoArquivo(std::string msg)
	{
		this->msg = msg;
	}

	virtual const char* what() const throw()
	{
		return msg.c_str();
	}

private:
	std::string msg;
};


#endif // EXCECOES_H