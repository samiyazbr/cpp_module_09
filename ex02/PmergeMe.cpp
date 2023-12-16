#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}
template <typename T>
void PmergeMe::display(const T& container)
{
    typename T::const_iterator it;
    for (it = container.begin(); it != container.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

PmergeMe::PmergeMe(int ac, char **av){

    std::deque<int> Deque;
    std::list<int> List;

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
    mergeInsertSortDeque(Deque);
    clock_t end_q = clock();
	// clock_t is a type that holds clock ticks.
	// CLOCKS_PER_SEC is a constant that holds the number of clock ticks per second.
    double time_q = static_cast<double>(end_q - start_q) / CLOCKS_PER_SEC * 1000;
	// The result of the subtraction is the number of clock ticks it took to sort the deque.
	// We divide that by CLOCKS_PER_SEC to get the number of seconds it took to sort the deque.

    clock_t start_lst = clock();
    mergeInsertSortList(List);
    clock_t end_lst = clock();
    double time_lst = static_cast<double>(end_lst - start_lst) / CLOCKS_PER_SEC * 1000;

    std::cout << "After: ";
    display(Deque);
    std::cout << "Time to process a range of " << Deque.size() << " elements with std::deque container: " << time_q << " us" << std::endl;
    std::cout << "Time to process a range of " << List.size() << " elements with std::list container: " << time_lst << " us" << std::endl;
    // if (Deque == std::deque<int>(List.begin(), List.end()))
    //     std::cout << "The sorted sequences are equal." << std::endl;
    // else
    //     std::cout << "The sorted sequences are not equal." << std::endl;
}

	// Insertion sort algorithm
		// Loop through the deque starting from the second element (index 1)
		// Move backward in the deque and shift elements to the right
        // until finding the correct position for the current element
		// Insert the current element into the correct position

void PmergeMe::mergeInsertSortDeque(std::deque<int>& arr)
{
    std::deque<int>::iterator it1, it2;
	// we can access random value in deque by using operators like +, -, +=, -=, [], etc.
    for (it1 = arr.begin() + 1; it1 != arr.end(); ++it1)
    {
		// Store the current element in a temporary variable
        int temp = *it1;

		// Initialize the second iterator to the current position
        it2 = it1;

    	//std::prev to get an iterator pointing to the preceding element
        while (it2 != arr.begin() && *(std::prev(it2)) > temp)
        {
            *it2 = *(std::prev(it2)); // shift elements to the right
            std::advance(it2, -1); // move iterator backward
        }
        *it2 = temp;
    }
}

void PmergeMe::mergeInsertSortList(std::list<int>& arr)
{
    std::list<int>::iterator it1, it2;
	// we cant access random value in list by using operators like +, -, +=, -=, [], etc., instead we should traverse the list usingg ++, --, etc.
    for (it1 = ++arr.begin(); it1 != arr.end(); ++it1)
    {
        int temp = *it1;
        it2 = it1;
        while (it2 != arr.begin() && *(std::prev(it2)) > temp)
        {
            *it2 = *(std::prev(it2));
            std::advance(it2, -1);
        }
        *it2 = temp;
    }
}

