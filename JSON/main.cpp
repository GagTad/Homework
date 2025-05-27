#include <iostream>

#include "json.h"

using namespace json;

int main()
{

	std::cout << "Hello , JSON ! " << std::endl;

	json_data d = json_util::read("data.json");



   json_data root ; 

   // ???????


   root["employeers"]["1"]["name"] = "Armen";
   root["employeers"]["1"]["age"] = 26;
   root["employeers"]["1"]["country"] = "Hayastan";

   root["employeers"]["2"]["age"] = 70;
   root["employeers"]["2"]["name"] = "Armenak";
   root["employeers"]["2"]["country"] = "Rusastan";
   

   // ????????
   json_util::write("data_modified.json", root);

    std::cout << "DONE!\n";
	return 0;
}
