#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <cctype>

class BitcoinExchange
{
	private:
	std::map<std::string, double> _data;
	int readFlag;

	public:
	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange(BitcoinExchange const &copy);
	BitcoinExchange &operator=(BitcoinExchange const &rhs);

	void setData(std::string date, double value);

	void readInputfile(std::string inputfilePath);

	std::map<std::string, double> getData();
	std::vector<std::string> splitline(std::string str, char seperator);
	int parse_date(std::string date);
};

#endif