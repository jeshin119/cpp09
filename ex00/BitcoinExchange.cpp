#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include "BitcoinExchange.hpp"

static bool		checkDate(std::string date){
	std::istringstream	iss(date);
	std::string			token;
	int					year = 0;
	int					mon = 0;
	int					day = 0;
	int					i = 4;

	while (std::getline(iss, token, '-') && i--){
		switch(i){
			case(3):
				year = strtol(token.c_str(), 0, 10);
			case(2):
				mon = strtol(token.c_str(), 0, 10);
			case(1):
				day = strtol(token.c_str(), 0, 10);
		}
	}
	if (year < 2009 || year > 2022 || mon < 1 || mon > 12 || day < 1 || day > 31)
		return (false);
	else if (year == 2009 && mon == 1 && day < 2)
		return (false);
	else if ((year == 2022 && mon > 3) || (year == 2022 && mon == 3 && day > 29))
		return (false);
	else if (mon == 2 && !((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) && day > 29)
		return (false);
	else if ((mon == 4 && day > 30) || (mon == 6 && day > 30) || (mon == 9 && day > 30) || (mon == 11 && day > 30))
		return (false);
	return (true);
}

static bool		checkVal(double val){
	if (val < 0){
		std::cerr<<"Error: not a positive number.\n";
		return false;
	}
	if (val > 1000){
		std::cerr<<"Error: too large a number\n";
		return false;
	}
	return true;
}

BitcoinExchange::BitcoinExchange(){
	std::ifstream		ifs("data.csv");
	std::string			line;
	std::string			date;
	double				val;

	if (!ifs)
		throw(std::runtime_error("Error: could not open file.\n"));
	std::getline(ifs, line);
	if (line != "date,exchange_rate")
		throw(std::runtime_error("Error: invaild data header.\n"));
	while (std::getline(ifs, line)){
		std::istringstream	iss(line);
		if (std::getline(iss, date, ',') && iss >> val)
			_m[date] = val;
		else
			throw(std::runtime_error("Error: invaild data. Failed to parse\n"));
	}
}

BitcoinExchange::~BitcoinExchange(){}

void	BitcoinExchange::Exchange(char* inFile){
	std::ifstream		ifs(inFile);
	std::string			line;
	std::string			date;
	double				val;

	if (!ifs)
		throw(std::runtime_error("Error: could not open input file.\n"));
	std::getline(ifs, line);
	if (line != "date | value")
		throw(std::runtime_error("Error: invaild input file header.\n"));
	while (std::getline(ifs, line)){
		std::istringstream	iss(line);
		if (!std::getline(iss, date, '|') || !(iss >> val)){
			std::cerr<<"Error: bad input => "<< line << "\n";
			continue;
		}
		if (!checkDate(date)){
			std::cerr<<"Error: bad input => "<< line << "\n";
			continue;
		}
		if (!checkVal(val))
			continue;
		Calculate(date, val);
	}
}

void	BitcoinExchange::Calculate(std::string date, double val){
	std::map<std::string,double>::iterator it = _m.upper_bound(date);
	std::cout << date << " => " << val << " = "  << (--it)->second * val << "\n";
}