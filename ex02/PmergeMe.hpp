#include <iostream>
#include <deque>
#include <list>
#include <algorithm>
#include <ctime>
#include <cstdlib> // for std::prev
#include <iterator> // for std::advance



class PmergeMe
{
	public:
	PmergeMe();
    PmergeMe(int ac, char **av);
	void mergeInsertSortDeque(std::deque<int>& arr);
	void mergeInsertSortList(std::list<int>& arr);
	
	template <typename T>
	void display(const T& container);
};