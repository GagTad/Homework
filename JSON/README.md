# JSON Parser & Editor in C++

This project is a simple JSON parser and editor implemented in C++.  
It allows you to read, modify, and write JSON files without using any external libraries.

## Features

- Read JSON files (`json_util::read`)
- Modify JSON data (change, add, or remove fields)
- Write JSON data back to a file (`json_util::write` or using `std::ofstream`)
- Print JSON data as a string (`json_data::stringify`)
- Access and print specific fields or array elements

## Main Functions

- **`json_util::read(const char* filename)`**  
  Reads a JSON file and returns a `json_data` object representing the data.

- **`json_util::write(const char* filename, json_data val)`**  
  Writes a `json_data` object to a JSON file.

- **`json_data::stringify()`**  
  Converts the JSON data to a formatted string.

- **`json_data::parse(std::string str)`**  
  Parses a JSON string and returns a `json_data` object.

- **`operator[]`**  
  Allows you to access or modify fields and array elements in the JSON data.

## Detailed Example

Suppose you have a `data.json` file like this:
```json
{
    "employees": [
        {
            "name": "Alexander",
            "age": 30,
            "country": "Puerto Rico",
            "isManager": false
        },
        {
            "name": "George",
            "age": 50,
            "country": "US",
            "isManager": true
        }
    ]
}
```

You can read the file, modify the first employee's country, and print the result:

```cpp
#include <iostream>
#include "json.h"

using namespace json;

int main() {
    // Read the JSON file
    json_data d = json_util::read("data.json");

    // Change the country of the first employee
    d["employees"][0]["country"] = "Austria";

    // Print the updated JSON data
    std::cout << d.stringify() << std::endl;

    // Save the changes back to the file
    json_util::write("data.json", d);

    // Print only the name of the first employee
    std::cout << "First employee's name: " << d["employees"][0]["name"].stringify() << std::endl;

    return 0;
}
```

**Explanation:**  
- `json_util::read("data.json")` reads the file and parses it into a `json_data` object.
- `d["employees"][0]["country"] = "Austria";` changes the country field of the first employee.
- `d.stringify()` converts the updated data to a JSON string for printing or saving.
- `json_util::write("data.json", d);` writes the changes back to the file.
- `d["employees"][0]["name"].stringify()` prints only the name of the first employee.

## Where to Use

- Small and medium projects that need basic JSON manipulation in C++
- Educational purposes to understand how JSON parsing works in C++

## Project Structure

- `json.h`, `json_data.cpp`, `json_util.cpp` — Core JSON logic
- `util.h`, `util.cpp` — Utility functions for file and string operations
- `main.cpp` — Example usage and entry point

