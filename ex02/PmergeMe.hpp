# ifndef __PMERGEME_H__
# define __PMERGEME_H__

# include <string>
# include <vector>
# include <deque>
# include <sys/time.h>
# include <utility>

typedef std::pair<int,int> pair;

class PmergeMe{
	public:
		PmergeMe(std::vector<int>& v);
		PmergeMe(std::deque<int>& d);
		~PmergeMe();

		void	prtSpecification();
		int		getCnt();
	private:
		PmergeMe();
		PmergeMe(const PmergeMe& rhs);

		void	_mergeInsertionSort(std::vector<int>* pmc, std::vector<int>* psc, std::vector<pair>* ppc);
		void	_mergeInsertionSort(std::deque<int>* pmc, std::deque<int>* psc, std::deque<pair>* ppc);

		void	_binaryInsert(const int& val, int end, std::vector<int>& mc);
		void	_binaryInsert(const int& val, int end, std::deque<int>& mc);

		void	_getJacobsthalNumbers(std::vector<int>& jacobNums, const int size);
		void	_getJacobsthalNumbers(std::deque<int>& jacobNums, const int size);

		PmergeMe&	operator=(const PmergeMe& rhs);

		long long			_cnt;
		long long			_range;
		double				_duration;
		std::string			_type;
};

# endif