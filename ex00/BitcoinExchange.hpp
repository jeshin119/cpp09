#ifndef __BITCOINTEXCHANGE_H__
#define __BITCOINTEXCHANGE_H__

#include <string>
#include <map>

class BitcoinExchange{
	public:
		BitcoinExchange();
		~BitcoinExchange();

		void	exchange(const char* inFile);
		void	calculate(const std::string& date, const double& val);
	private:
		BitcoinExchange(const BitcoinExchange& rhs);
		BitcoinExchange&	operator=(BitcoinExchange& rhs);

		bool		_checkIss(std::istringstream& iss);
		bool		_checkDate(const std::string& date);
		bool		_checkVal(const double& val);
		int 		_toDate(const std::string& token);

		std::map<std::string, double>	_m;
};

#endif