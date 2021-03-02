#include "ChiliException.h"
#include <sstream>

ChiliException::ChiliException(int line, const char * file) noexcept
	:line(line),
	file(file)
{}

char const * ChiliException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char * ChiliException::GetType() const noexcept
{
	return "Chil Exception";
}

int ChiliException::GetLine() const noexcept
{
	return line;
}

std::string ChiliException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[file] " << file << std::endl
		<< "[line] " << line;
	return oss.str();
}
