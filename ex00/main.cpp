#include <map>
#include <iostream>
#include "BitcoinExchange.hpp"

int main(int ac, char** av){
	if (ac != 2){
		std::cerr<<"Error: could not open file.\n";
		return (1);
	}
	try{
		BitcoinExchange	be;
		be.exchange(av[1]);
	}catch(std::runtime_error& e){
		std::cerr<<e.what();
	}
}