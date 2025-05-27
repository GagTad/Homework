#include <iostream>

#include "json.h"

using namespace json;

int main()
{
	std::string s = "[10, 20, 30]";
	int i = 1;
	auto vec = getObj(s, i);
	// vec = [10, 20, 30] ????? json_data list

	std::cout << "Hello , JSON ! " << std::endl;
	//d["employers"]["name"] = "Michael";
	//d["employers"]["age"] = 30;
	
	json_data d = json_util::read("data.json");

	std::cout  << d.stringify() << std::endl;
	return 0;
}
//#include "json.h"
//#include <iostream>
//
//using namespace json;
//
//
//int main() {
//    json_data root = json_util::read("data.json");
//
//    // ???????
//
//
//    root["employeers"]["1"]["name"] = "Armen";
//    root["employeers"]["1"]["age"] = 26;
//    root["employeers"]["1"]["country"] = "Hayastan";
//
//    root["employeers"]["2"]["age"] = 70;
//    root["employeers"]["2"]["name"] = "Armenak";
//    root["employeers"]["2"]["country"] = "Rusastan";
//    
//
//    // ????????
//    json_util::write("data_modified.json", root);
//
//    std::cout << "DONE!\n";
//}
