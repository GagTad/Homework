#include "json.h"
#include <iostream>

using namespace json;

json_data json_util::read(const char* filename) {
	//std::ifstream file(filename);
	//std::string ret = "";
	//if (!file.is_open())
	//{
	//	std::cout << "ERRROOOOOOOOOOOOOOOOOOR" << std::endl;
	//}
	//else{
	//	std::stringstream sstream;
	//	sstream << file.rdbuf();
	//	ret = sstream.str();
	//}
	//file.close();
	
	return json_data::parse(readFile(filename));
}

bool json_util::write(const char* filename, json_data val) {
	return writeFile(filename, val.stringify());
}