# include <iostream>
# include "RPN.hpp"

int main(int ac, char** av){
	if (ac != 2){
		std::cerr<<"Error\n";
		return (1);
	}
	try{
		RPN rpn(av[1]);
	}catch(std::exception& e){
		std::cerr<<e.what();
	}
}