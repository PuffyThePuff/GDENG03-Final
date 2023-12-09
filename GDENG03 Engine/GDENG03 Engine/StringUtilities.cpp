#include"StringUtilities.h"

std::vector<std::string> StringUtilities::split(const std::string& long_string, char delim_char) {
	std::stringstream stringStream(long_string);
	std::string item;
	std::vector<std::string> elements;
	while (std::getline(stringStream, item, delim_char)) {
		elements.push_back(item);
	}
	return elements;
}