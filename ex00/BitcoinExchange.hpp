#ifndef __BITCOINTEXCHANGE_H__
#define __BITCOINTEXCHANGE_H__

#include <string>
#include <map>

class BitcoinExchange{
	public:
		BitcoinExchange();
		~BitcoinExchange();

		void	Exchange(char* inFile);
		void	Calculate(std::string date, double val);
	private:
		BitcoinExchange(const BitcoinExchange& rhs);
		BitcoinExchange&	operator=(BitcoinExchange& rhs);
		std::map<std::string, double>	_m;
};

#endif