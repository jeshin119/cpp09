# ifndef __PMERGEME_H__
# define __PMERGEME_H__

# include <string>
# include <vector>
# include <deque>
# include <sys/time.h>

class PmergeMe{
	public:
		PmergeMe(std::vector<int>& v);
		PmergeMe(std::deque<int>& d);
		~PmergeMe();

		void	prtSpecification();
	private:
		PmergeMe();
		PmergeMe(const PmergeMe& rhs);

		void	_mergeInsertionSort(std::vector<int>* mc, std::vector<int>* sc, int* linkArr);
		void	_binaryInsert(const int& val, std::vector<int>& mc);
		void	_getJacobsthalNumbers(std::vector<int>& jacobNums, const int size);
		// void	_divide(std::vector<int>* mc, std::vector<int>* sc);

		// void	_mergeInsertion(std::deque<int>& mc, std::deque<int>& sc);

		PmergeMe&	operator=(const PmergeMe& rhs);

		long long			_cnt;
		long long			_range;
		struct timeval		_startTime;
		struct timeval		_endTime;
		double				_duration;
		std::string			_type;
};

# endif