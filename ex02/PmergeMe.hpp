#include <iostream>
#include <deque>
#include <list>
#include <ctime>
#include <iterator> // for std::advance



class PmergeMe
{
	public:
	PmergeMe();
    PmergeMe(int ac, char **av);
	PmergeMe(PmergeMe const &copy);
	PmergeMe &operator=(PmergeMe const &rhs);
	void merge_Insert_Sort_Deque(std::deque<int>& arr);
	void merge_Insert_Sort_List(std::list<int>& arr);
	
	template <typename T>
	void display(const T& container);

	~PmergeMe();};

template <typename Iterator>
Iterator prev_it(Iterator it) {
        --it;
    return it;
}

template <typename Iterator>
Iterator next_it(Iterator it) {
		++it;
	return it;
}