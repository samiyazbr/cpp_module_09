#include <iostream>
#include <deque>
#include <list>
#include <algorithm>
#include <ctime>
#include <cstdlib> // for std::prev
#include <iterator> // for std::advance



class PmergeMe
{
	private:
		void merge_deque(std::deque<int>::iterator left, std::deque<int>::iterator mid, std::deque<int>::iterator right);
		void merge_list(std::list<int>::iterator left, std::list<int>::iterator mid, std::list<int>::iterator right);
		void insertionSort_deque(std::deque<int>& arr);
		void insertionSort_list(std::list<int>& arr);
	public:
	PmergeMe();
    PmergeMe(int ac, char **av);
	void mergeInsertSortDeque(std::deque<int>& arr);
	void mergeInsertSortList(std::list<int>& arr);
	
	template <typename T>
	void display(const T& container);
};