#include "GLException.h"

#include <iostream>

GLException::GLException(const std::string& message, const char* file, const int line) noexcept
	: m_message(message)
	, m_file(file)
	, m_line(line) {}

const char* GLException::what() const noexcept {
	std::cerr << "Exception in file " << m_file << " (line " << std::to_string(m_line) << "):" << std::endl;
	return m_message.c_str();
}
