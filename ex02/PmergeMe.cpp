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

void PmergeMe::mergeInsertSortDeque(std::deque<int>& arr) {
    if (arr.size() <= 100) {
        insertionSort(arr);
    } else {
        std::deque<int>::iterator mid = arr.begin() + arr.size() / 2;
        std::deque<int> left(arr.begin(), mid);
        std::deque<int> right(mid, arr.end());

        mergeInsertSortDeque(left);
        mergeInsertSortDeque(right);

        merge(left.begin(), left.end(), right.end());
    }
}

void PmergeMe::merge(std::deque<int>::iterator left, std::deque<int>::iterator mid, std::deque<int>::iterator right) {
    std::deque<int> merged;
    std::deque<int>::iterator it1 = left;
    std::deque<int>::iterator it2 = mid;

    while (it1 != mid && it2 != right) {
        if (*it1 <= *it2) {
            merged.push_back(*it1);
            ++it1;
        } else {
            merged.push_back(*it2);
            ++it2;
        }
    }

    std::copy(it1, mid, std::back_inserter(merged));
    std::copy(it2, right, std::back_inserter(merged));
    std::copy(merged.begin(), merged.end(), left);
}

void PmergeMe::insertionSort(std::deque<int>& arr) {
    for (std::deque<int>::iterator it1 = arr.begin() + 1; it1 != arr.end(); ++it1) {
        int temp = *it1;
        std::deque<int>::iterator it2 = it1;

        while (it2 != arr.begin() && *(std::prev(it2)) > temp) {
            *it2 = *(std::prev(it2));
            std::advance(it2, -1);
        }

        *it2 = temp;
    }
}

void PmergeMe::mergeInsertSortList(std::list<int>& arr) {

    if (arr.size() <= 100) {
        insertionSort(arr);
    } else {
        std::list<int>::iterator mid = std::next(arr.begin(), arr.size() / 2);
        std::list<int> left(arr.begin(), mid);
        std::list<int> right(mid, arr.end());

        mergeInsertSortList(left);
        mergeInsertSortList(right);

        merge(arr, left.begin(), left.end(), right.end());
    }
}

void PmergeMe::merge(std::list<int>& arr, std::list<int>::iterator left, std::list<int>::iterator mid, std::list<int>::iterator right) {
    std::list<int> merged;
    std::list<int>::iterator it1 = left;
    std::list<int>::iterator it2 = mid;

    while (it1 != mid && it2 != right) {
        if (*it1 <= *it2) {
            merged.push_back(*it1);
            ++it1;
        } else {
            merged.push_back(*it2);
            ++it2;
        }
    }

    merged.splice(merged.end(), arr, it1, mid);
    merged.splice(merged.end(), arr, it2, right);

    // Using splice to efficiently move the sorted range back into the original list
    arr.splice(left, merged);
}

void PmergeMe::insertionSort(std::list<int>& arr) {
    for (std::list<int>::iterator it1 = std::next(arr.begin()); it1 != arr.end(); ++it1) {
        int temp = *it1;
        std::list<int>::iterator it2 = it1;

        while (it2 != arr.begin() && *(std::prev(it2)) > temp) {
            std::advance(it2, -1);
        }
        // Using splice to efficiently insert the element to its correct position
        arr.splice(it2, arr, it1);
    }
}