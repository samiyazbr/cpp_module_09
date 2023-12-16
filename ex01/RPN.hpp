#include <iostream>
#include <stack>

class RPN
{
private:
	std::stack<double> _numbers;
public:
	RPN();
	RPN(std::stack<double> number);
	RPN(const RPN &copy);
	~RPN();
	RPN &operator=(const RPN &rhs);
	void calculate(std::string operation);		
};
