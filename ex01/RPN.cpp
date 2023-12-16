#include "RPN.hpp"

RPN::RPN()
{
	return;
}

RPN::~RPN()
{
	return;
}

RPN::RPN(std::stack<double> number)
{
	this->_numbers = number;
}

RPN::RPN(const RPN &copy)
{
	*this = copy;
}

RPN &RPN::operator=(const RPN &rhs)
{
	this->_numbers = rhs._numbers;
	return (*this);
}

// In Reverse Polish Notation (RPN), the operators come after their operands.
// For example, 3 + 4 is written 3 4 + in RPN.
// An advantage of RPN is that it removes the need for parentheses that are required by infix.(3 + 4) * 5 in RPN is 3 4 + 5 * and in infix is (3 + 4) * 5.

void RPN::calculate(std::string input)
{
	for (size_t i = 0; i < input.size(); i++)
	{
		char c = input[i];

		if (c == ' ')
		{
			// skip whitespace
			continue;
		}
		else if (isdigit(c))
		{
			int number = c - '0';
			_numbers.push(number);
		}
		else if (c == '+' && _numbers.size() >= 2)
		{
			double b = _numbers.top();
			_numbers.pop();
			double a = _numbers.top();
			_numbers.pop();
			_numbers.push(a + b);
		}
		else if (c == '-' && _numbers.size() >= 2)
		{
			double b = _numbers.top();
			_numbers.pop();
			double a = _numbers.top();
			_numbers.pop();
			_numbers.push(a - b);
		}
		else if (c == '*' && _numbers.size() >= 2)
		{
			double b = _numbers.top();
			_numbers.pop();
			double a = _numbers.top();
			_numbers.pop();
			_numbers.push(a * b);
		}
		else if (c == '/' && _numbers.size() >= 2)
		{
			double b = _numbers.top();
			_numbers.pop();
			double a = _numbers.top();
			_numbers.pop();
			_numbers.push(a / b);
		}
		else
		{
			// invalid character or insufficient operands
			std::cout << "Invalid input." << std::endl;
			return;
		}
	}

	if (_numbers.size() == 1)
	{
		double result = _numbers.top();
		_numbers.pop();
		std::cout << "Result: " << result << std::endl;
	}
	else
	{
		// insufficient operands
		std::cout << "Invalid input." << std::endl;
	}
}
