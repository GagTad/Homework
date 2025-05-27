
#include <iostream>
#include <fstream>
#include "json.h"

using namespace json;

int main() {
    std::cout << "Hello, JSON!" << std::endl;

    json_data d = json_util::read("data.json");

  
    d["employees"][0]["country"] = "Austria";

    
    std::cout << d.stringify() << std::endl;

    
    std::ofstream out("data.json");
    out << d.stringify();
    out.close();

    std::cout << d["employees"][0]["name"].stringify() << std::endl;
}
