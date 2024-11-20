# ifndef __PMERGEME_H__
# define __PMERGEME_H__

# include <string>

class PmergeMe{
	public:
		PmergeMe();
		~PmergeMe();

	private:
		PmergeMe(const PmergeMe& rhs);
		PmergeMe&	operator=(const PmergeMe& rhs);
};

# endif