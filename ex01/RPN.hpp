# ifndef __RPN_H__
# define __RPN_H__

# include <string>
# include <stack>

class RPN{
	public:
		RPN(const std::string& input);
		~RPN();
	private:
		RPN();
		RPN(const RPN& rhs);
		RPN&	operator=(const RPN& rhs);

		void	_add();
		void	_subtract();
		void	_divide();
		void	_multiply();
		void	_getVal(double *lhs, double *rhs);

		std::stack<double>		_st;
};

# endif