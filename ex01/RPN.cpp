# include <iostream>
# include <stdexcept>
# include <string>
# include <fstream>
# include <sstream>
# include <stack>
# include <math.h>
# include "RPN.hpp"

RPN::RPN(const std::string& input){
	std::istringstream		iss(input);
	std::string				token;
	const std::string		opTab[4] = {"+", "-", "/", "*"};
	int						pos;

	while (getline(iss, token, ' ')){
		if (token == "")
			continue ;
		for (pos = 0 ; pos < 4; pos++){
			if (token == opTab[pos])
				break ;
		}
		if (pos == 4 && abs(strtod(token.c_str(), 0)) < 10){ 
			_st.push(strtod(token.c_str(), 0));
			continue ;
		}
		switch(pos){
			case (0):
				_add();
				continue ;
			case (1):
				_subtract();
				continue ;
			case (2):
				_divide();
				continue ;
			case (3):
				_multiply();
				continue ;
		}
		throw std::runtime_error("Error\n");
	}
	if (_st.empty() || _st.size() > 2)
		throw std::runtime_error("Error\n");
	std::cout << _st.top() << "\n";
}

RPN::~RPN(){}

void	RPN::_add(){
	double lhs;
	double rhs;

	_getVal(&lhs, &rhs);
	_st.push(lhs + rhs);
}
void	RPN::_subtract(){
	double lhs;
	double rhs;

	_getVal(&lhs, &rhs);
	_st.push(lhs - rhs);
}
void	RPN::_divide(){
	double lhs;
	double rhs;

	_getVal(&lhs, &rhs);
	if (rhs == 0)
		throw std::runtime_error("Error: division by zero\n");
	_st.push(lhs / rhs);
}
void	RPN::_multiply(){
	double lhs;
	double rhs;

	_getVal(&lhs, &rhs);
	_st.push(lhs * rhs);
}

void	RPN::_getVal(double *lhs, double *rhs){
	if (_st.size() < 2)
		throw std::runtime_error("Error\n");

	*rhs = _st.top();
	_st.pop();
	*lhs = _st.top();
	_st.pop();
}