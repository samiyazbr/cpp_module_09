#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}

PmergeMe::~PmergeMe(){}

PmergeMe::PmergeMe(PmergeMe const &copy)
{
    *this = copy;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &rhs)
{
	(void)rhs;
	return (*this);
}



template <typename T>
void PmergeMe::display(const T& container)
{
    typename T::const_iterator it;
    for (it = container.begin(); it != container.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

PmergeMe::PmergeMe(int ac, char **av){

    // fill the containers with random integers
    srand(time(NULL));
    for (int i = 1; i < ac; ++i)
    {
        int value = atoi(av[i]);
        if (value <= 0)
        {
            std::cerr << "Error: Invalid input value \"" << av[i] << "\". Only positive integers are allowed." << std::endl;
			exit(1);
        }
        Deque.push_back(value);
        List.push_back(value);
    }
    std::cout << "Before: ";
    display(Deque);

    clock_t start_q = clock();
    merge_Insert_Sort_Deque(Deque);
    clock_t end_q = clock();
	// clock_t is a type that holds clock ticks.
	// CLOCKS_PER_SEC is a constant that holds the number of clock ticks per second.
    double time_q = static_cast<double>(end_q - start_q) / CLOCKS_PER_SEC * 1000;
	// The result of the subtraction is the number of clock ticks it took to sort the deque.
	// We divide that by CLOCKS_PER_SEC to get the number of seconds it took to sort the deque.

    clock_t start_lst = clock();
    merge_Insert_Sort_List(List);
    clock_t end_lst = clock();
    double time_lst = static_cast<double>(end_lst - start_lst) / CLOCKS_PER_SEC * 1000;

    std::cout << "After: ";
    display(Deque);
    std::cout << "Time to process a range of " << Deque.size() << " elements with std::deque container: " << time_q << " us" << std::endl;
    std::cout << "Time to process a range of " << List.size() << " elements with std::list container: " << time_lst << " us" << std::endl;
    if (Deque == std::deque<int>(List.begin(), List.end()))
        std::cout << "The sorted sequences are equal." << std::endl;
    else
        std::cout << "The sorted sequences are not equal." << std::endl;
}

 //========================================== PmergeMe::merge_Insert_Sort_Deque ==========================================//
static void insertion_sort_deque(std::deque<int>& arr) {
    for (std::deque<int>::iterator it1 = arr.begin() + 1; it1 != arr.end(); ++it1) {
        int temp = *it1;
        std::deque<int>::iterator it2 = it1;
        while (it2 != arr.begin() && *(prev_it(it2)) > temp) {
            *it2 = *(prev_it(it2));
            std::advance(it2, -1);
        }
        *it2 = temp;
    }
}

static void merge_deque(std::deque<int>& arr, std::deque<int>& left, std::deque<int>& right) {
    std::deque<int>::iterator it_arr = arr.begin();
    std::deque<int>::iterator it_left = left.begin();
    std::deque<int>::iterator it_right = right.begin();

    while (it_left != left.end() && it_right != right.end()) {
        if (*it_left <= *it_right) {
            *it_arr = *it_left;
            ++it_left;
        } else {
            *it_arr = *it_right;
            ++it_right;
        }
        ++it_arr;
    }
	while (it_left != left.end())
	{
		*it_arr = *it_left;
        ++it_left;
		++it_arr;
	}
	while (it_right != right.end())
	{
		*it_arr = *it_right;
        ++it_right;
		++it_arr;

	}
    // Copy the remaining elements of left and right, if any
    //std::copy(it_left, left.end(), it_arr);
    //std::copy(it_right, right.end(), it_arr);
}

void PmergeMe::merge_Insert_Sort_Deque(std::deque<int>& arr) {
    if (arr.size() < 2) {
        return; // Already sorted
    }

    // Use insertion sort for small subarrays
    if (arr.size() <= 5) {
        insertion_sort_deque(arr);
    } else {
        // Divide the array into two halves
        std::deque<int>::iterator middle = arr.begin() + arr.size() / 2;
        
        // Recursively sort each half
        std::deque<int> left(arr.begin(), middle);
        std::deque<int> right(middle, arr.end());
        merge_Insert_Sort_Deque(left);
        merge_Insert_Sort_Deque(right);

        // Merge the sorted halves
        merge_deque(arr, left, right);
    }
}

//========================================== PmergeMe::merge_Insert_Sort_List ==========================================//

static void insertion_sort_list(std::list<int>& lst) {
    for (std::list<int>::iterator it1 = next_it(lst.begin()); it1 != lst.end(); ++it1) {
        int temp = *it1;
        std::list<int>::iterator it2 = it1;
        while (it2 != lst.begin() && *(prev_it(it2)) > temp) {
            *it2 = *(prev_it(it2));
            --it2;
        }
        *it2 = temp;
    }
}

static void merge_list(std::list<int>& lst, std::list<int>& left, std::list<int>& right) {
        std::list<int>::iterator it_lst = lst.begin();
        std::list<int>::iterator it_left = left.begin();
        std::list<int>::iterator it_right = right.begin();
        while (it_left != left.end() && it_right != right.end()) {
            if (*it_left <= *it_right) {
                *it_lst = *it_left;
                ++it_left;
            } else {
                *it_lst = *it_right;
                ++it_right;
            }
            ++it_lst;
        }
		while (it_left != left.end())
		{
			*it_lst = *it_left;
               ++it_left;
			   ++it_lst;
		}
		while (it_right != right.end())
		{
			*it_lst = *it_right;
              ++it_right;
			  ++it_lst;
		}
    }

void PmergeMe::merge_Insert_Sort_List(std::list<int>& lst) {
    if (lst.size() < 2) {
        return; // Already sorted
    }

    // Use insertion sort for small sublists
    if (lst.size() <= 5) {
        insertion_sort_list(lst);
    } else {
        // Divide the list into two halves
        std::list<int>::iterator middle = lst.begin();
        std::advance(middle, lst.size() / 2);
        
        // Recursively sort each half
        std::list<int> left(lst.begin(), middle);
        std::list<int> right(middle, lst.end());
        merge_Insert_Sort_List(left);
        merge_Insert_Sort_List(right);

        // Merge the sorted halves
        merge_list(lst, left, right);
    }
}


