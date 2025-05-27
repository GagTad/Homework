#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <filesystem>

namespace fs = std::filesystem;

// ANSI color codes
const std::string RED = "\033[1;31m";
const std::string RESET = "\033[0m";

// Highlights all regex matches in a line
std::string highlight_match(const std::string& line, const std::regex& pattern) {
    std::string result;
    std::sregex_iterator begin(line.begin(), line.end(), pattern);
    std::sregex_iterator end;

    size_t last_pos = 0;
    for (auto it = begin; it != end; ++it) {
        std::smatch match = *it;
        result += line.substr(last_pos, match.position() - last_pos);
        result += RED + match.str() + RESET;
        last_pos = match.position() + match.length();
    }

    result += line.substr(last_pos);
    return result;
}

// Searches for pattern matches in a given file
void search_in_file(const std::string& filename, const std::regex& regex_pattern, bool count_only, bool show_filename) {
    std::ifstream file(filename);
    if (!file) return;

    std::string line;
    int line_number = 1;
    int match_count = 0;

    while (std::getline(file, line)) {
                  if (std::regex_search(line, regex_pattern)) {
            match_count++;
            if (!count_only) {
                std::string highlighted = highlight_match(line, regex_pattern);
                if (show_filename)
                    std::cout << filename << ":";
                std::cout << line_number << ": " << highlighted << std::endl;
            }
        }
        line_number++;
    }

    if (count_only && match_count > 0) {
        std::cout << filename << ":" << match_count << std::endl;
    }
}

int main(int argc, char* argv[]) {
    bool ignore_case = false;
    bool count_only = false;
    bool recursive = false;
    std::string pattern;
    std::string target;

    int arg_index = 1;

    // Parse flags
    while (arg_index < argc && argv[arg_index][0] == '-') {
        std::string flag = argv[arg_index];
        if (flag == "-i") ignore_case = true;
        else if (flag == "--count") count_only = true;
        else if (flag == "-r") recursive = true;
        else {
            std::cerr << "Unknown flag: " << flag << std::endl;
            return 1;
        }
        arg_index++;
    }

    if (arg_index >= argc) {
        std::cerr << "Usage: " << argv[0] << " [-r] [-i] [--count] <pattern> [file|dir]" << std::endl;
        return 1;
    }

    pattern = argv[arg_index++];

    if (arg_index < argc)
        target = argv[arg_index];
    else
        target = ""; // for stdin input

    // Compile regex pattern
    std::regex regex_pattern;
    try {
        regex_pattern = ignore_case ?
            std::regex(pattern, std::regex_constants::icase) :
            std::regex(pattern);
    } catch (std::regex_error& e) {
        std::cerr << "Invalid regex pattern: " << e.what() << std::endl;
        return 1;
    }

    if (recursive) {
        if (target.empty()) {
            std::cerr << "Error: -r flag requires a directory." << std::endl;
            return 1;
        }
        for (const auto& entry : fs::recursive_directory_iterator(target)) {
            if (!entry.is_regular_file()) continue;
            search_in_file(entry.path().string(), regex_pattern, count_only, true);
        }
    } else if (!target.empty()) {
        search_in_file(target, regex_pattern, count_only, false);
    } else {
        // Read from standard input
        std::string line;
        int line_number = 1;
        int match_count = 0;
        while (std::getline(std::cin, line)) {
                            
            if (std::regex_search(line, regex_pattern)) {
                match_count++;
                if (!count_only) {
                    std::string highlighted = highlight_match(line, regex_pattern);
                    std::cout << line_number << ": " << highlighted << std::endl;
                }
            }
            line_number++;
        }
        if (count_only)
            std::cout << match_count << std::endl;
    }

    return 0;
}
