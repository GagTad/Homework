#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <cctype>

std::string expr;
size_t pos = 0;
std::map<std::string, double> variables;

void skip_whitespace() {
    while (pos < expr.size() && std::isspace(expr[pos])) pos++;
}

double parse_expression(); // Forward declaration to allow usage before definition

double parse_number() {
    skip_whitespace();
    size_t start = pos;
    while (pos < expr.size() && (std::isdigit(expr[pos]) || expr[pos] == '.')) pos++;
    if (start == pos) throw std::runtime_error("Expected a number");
    return std::stod(expr.substr(start, pos - start));
}

std::string parse_identifier() {
    skip_whitespace();
    size_t start = pos;
    while (pos < expr.size() && std::isalpha(expr[pos])) pos++;
    return expr.substr(start, pos - start);
}

double parse_function_call(const std::string& func_name) {
    skip_whitespace();
    if (expr[pos] != '(')
        throw std::runtime_error("Expected opening parenthesis `(` for function");
    pos++; // consume '('
    double arg = parse_expression();
    skip_whitespace();
    if (expr[pos] != ')')
        throw std::runtime_error("Missing closing parenthesis `)` for function");
    pos++; // consume ')'

    if (func_name == "sqrt") return std::sqrt(arg);
    if (func_name == "sin") return std::sin(arg);
    if (func_name == "cos") return std::cos(arg);
    if (func_name == "tan") return std::tan(arg);
    if (func_name == "log") return std::log(arg);
    if (func_name == "exp") return std::exp(arg);
    if (func_name == "abs") return std::abs(arg);

    throw std::runtime_error("Unknown function: " + func_name);
}

double parse_factor() {
    skip_whitespace();
    if (expr[pos] == '(') {
        pos++;
        double val = parse_expression();
        skip_whitespace();
        if (expr[pos] != ')') throw std::runtime_error("Missing `)`");
        pos++;
        return val;
    } else if (std::isalpha(expr[pos])) {
        std::string name = parse_identifier();
        skip_whitespace();
        if (expr[pos] == '(') {
            return parse_function_call(name); // function call
        } else {
            if (variables.find(name) != variables.end()) {
                return variables[name]; // variable
            } else {
                throw std::runtime_error("Unknown variable: " + name);
            }
        }
    } else {
        return parse_number();
    }
}

double parse_term() {
    double val = parse_factor();
    while (true) {
        skip_whitespace();
        if (expr[pos] == '*') {
            pos++;
            val *= parse_factor();
        } else if (expr[pos] == '/') {
            pos++;
            double divisor = parse_factor();
            if (divisor == 0) throw std::runtime_error("Division by zero");
            val /= divisor;
        } else {
            break;
        }
    }
    return val;
}

double parse_expression() {
    double val = parse_term();
    while (true) {
        skip_whitespace();
        if (expr[pos] == '+') {
            pos++;
            val += parse_term();
        } else if (expr[pos] == '-') {
            pos++;
            val -= parse_term();
        } else {
            break;
        }
    }
    return val;
}

double evaluate(const std::string& input) {
    expr = input;
    pos = 0;
    skip_whitespace();

    size_t assign_pos = expr.find('=');
    if (assign_pos != std::string::npos) {
        std::string var_name = expr.substr(0, assign_pos);
        expr = expr.substr(assign_pos + 1);
        pos = 0;
        double val = parse_expression();
        var_name.erase(remove_if(var_name.begin(), var_name.end(), ::isspace), var_name.end());
        variables[var_name] = val;
        return val;
    } else {
        return parse_expression();
    }
}

int main() {
    std::string input;
    std::cout << "Simple Calculator (type `exit` to quit)\n";
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        if (input == "exit") break;
        try {
            double result = evaluate(input);
            std::cout << "= " << result << "\n";
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
    return 0;
}
