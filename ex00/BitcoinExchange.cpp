#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	int i = 0;
	this->readFlag = 1;
	std::ifstream file("./data.csv");
	if (!file.is_open())
	{
		std::cout << "Error: File not found" << std::endl;
		this->readFlag = 0;
		return ;
	}
	std::string line;
	while(std::getline(file, line))
	{
		if (i == 0)
		{
			i = 1;
			continue ;
		}
		size_t pos = line.find(',');
		if (pos == std::string::npos)
		{
			std::cerr << "Error : Invalid Paramter" << std::endl;
			continue;
		}
		std::string date = line.substr(0, pos);
        double value;
        try {
            value = std::stod(line.substr(pos + 1));
        } catch (std::exception &error) {
			(void)error;
            std::cerr << "Error: could not parse value" << std::endl;
            continue;
        }
		this->setData(date, value);
	}
	file.close();
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &rhs)
{
	this->_data = rhs._data;
	return (*this);
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &copy)
{
	*this = copy;
}

void BitcoinExchange::setData(std::string date, double value)
{
	this->_data.insert(std::make_pair(date, value));
}

std::map<std::string, double> BitcoinExchange::getData()
{
	return (this->_data);
}

std::vector<std::string> BitcoinExchange::splitline(std::string str, char seperator)
{
	std::vector<std::string> substrings;
	std::string substring = "";
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] != seperator)
		{
			substring += str[i];
		}
		else
		{
			substrings.push_back(substring);
			while (str[i] == seperator)
				i++;
			i--;
			substring = "";
		}
	}
	substrings.push_back(substring);
	return substrings;
}

// Whitespace characters to remove (space, tab, newline, carriage return)
const char* WHITESPACE = " \t\n\r";

// Trim whitespace characters from the beginning of a string
static std::string& trim_start(std::string& s)
{
    s.erase(0, s.find_first_not_of(WHITESPACE));
    return s;
}

// Trim whitespace characters from the end of a string
static std::string& trim_end(std::string& s)
{
    s.erase(s.find_last_not_of(WHITESPACE) + 1);
    return s;
}

// Trim whitespace characters from both ends of a string
static std::string& trim(std::string& s)
{
    return trim_start(trim_end(s));
}

int BitcoinExchange::parse_date(std::string date)
{
	std::vector<std::string> date_vector;
	date_vector = this->splitline(date, '-');
	if (date_vector.size() != 3)
		return (1);
	if (date_vector[0].length() != 4 || date_vector[1].length() != 2 || date_vector[2].length() != 2)
		return (1);
	try
	{
		int year = std::stoi(date_vector[0]);
		int month = std::stoi(date_vector[1]);
		int day = std::stoi(date_vector[2]);
		if (year < 2009 || year > 2022)
			return (1);
		if (month < 1 || month > 12)
			return (1);
		if (year % 4 == 0 && month == 2 && day > 29)
			return (1);
		if (year % 4 != 0 && month == 2 && day > 28)
			return (1);
		if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			if (day < 1 || day > 30)
				return (1);
		}
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		{
			if (day < 1 || day > 31)
				return (1);
		}
		return (0);
	}
	catch (const std::exception &e)
	{
		(void)e;
		return (1);
	}
}

void BitcoinExchange::readInputfile(std::string inputfilePath)
{
	std::ifstream file2(inputfilePath);
	if (!file2.is_open())
	{
		this->readFlag = -1;
		return;
	}
	std::string line;
	std::vector<std::string> vectorLine;
	while(std::getline(file2, line))
	{
		vectorLine = this->splitline(line, '|');
		if (vectorLine[1].length() == 0 || vectorLine.size() < 2)
		{
			std::cout << "Error: bad input => " << vectorLine[0] << std::endl;
			continue;
		}
		std::map<std::string, double>::iterator it = this->_data.upper_bound(trim(vectorLine[0]));
		if (parse_date(trim(vectorLine[0])) == 1)
		{
			std::cout << "Error: bad input => " << vectorLine[0] << std::endl;
			continue;
		}
		if (it != this->_data.end()) {
	        std::pair<std::string, double> p = *(--it);
			try
			{
				if (std::stod(vectorLine[1]) > 1000)
				{
					std::cout << "Error: too large a number." << std::endl;
				}
				else if (std::stod(vectorLine[1]) < 0)
				{
					std::cout << "Error: not a positive number." << std::endl;
				}
				else
		        	std::cout << vectorLine[0] << " => " << vectorLine[1] << " = " << std::stod(vectorLine[1]) * p.second << std::endl;

			}catch (const std::exception &e)
			{
				(void)e;
				std::cout << "Error : Input Not A Number" << std::endl;
				continue;
			}
		}

	}
	file2.close();
}
