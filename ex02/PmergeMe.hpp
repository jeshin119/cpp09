# ifndef __PMERGEME_H__
# define __PMERGEME_H__

# include <string>
# include <vector>
# include <deque>
# include <sys/time.h>

class PmergeMe{
	public:
		PmergeMe(std::vector<int>& v);
		// PmergeMe(std::deque<int>& d);
		~PmergeMe();

		void	prtSpecification();
		int		getCnt();
	private:
		PmergeMe();
		PmergeMe(const PmergeMe& rhs);

		void	_mergeInsertionSort(std::vector<int>* pmc, std::vector<int>* psc);
		// void	_mergeInsertionSort(std::deque<int>* pmc, std::deque<int>* psc);

		int		_binaryInsert(const int& here, int end, std::vector<int>& mc);
		// int		_binaryInsert(const int& val, int end, std::deque<int>& mc);

		void	_getJacobsthalNumbers(std::vector<int>& jacobNums, const int size);
		// void	_getJacobsthalNumbers(std::deque<int>& jacobNums, const int size);

		PmergeMe&	operator=(const PmergeMe& rhs);

		long long			_cnt;
		long long			_range;
		double				_duration;
		std::string			_type;
		std::vector<int>	_ov; // ov: origin Vector
		std::deque<int>		_od; // od: origin Deque
};

# endif