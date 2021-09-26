#pragma once

#include <exception>
#include <string>

class GLException : std::exception
{
public:
	GLException(const std::string& message, const char* file, const int line) noexcept;
	virtual const char* what() const noexcept override;

protected:
	std::string m_message;
	std::string m_file;
	int m_line;
};
