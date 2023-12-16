#include "RPN.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./RPN <expression>" << std::endl;
        return 1;
    }

    std::string operation = argv[1];
    RPN calculator;
    calculator.calculate(operation);

    return 0;
}