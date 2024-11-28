# include <iostream>
# include <vector>
# include <deque>
# include <exception>
# include "PmergeMe.hpp"

//설계 : 입력받음-> 검증 음수안됨, float안됨, 문자안됨, 공백기준으로 나눠서 양수만 받음, 0도 안됨, positive integer라고했으니 int 범위 내에있어야함->

void	getInput(int ac, char **av, std::vector<int>& v, std::deque<int>& d){
	int				num;
	char*			endPtr;

	if (ac < 2)
		throw(std::runtime_error("Error: argc\n"));
	for (int i = 1; i != ac ; i++){
		num = strtol(av[i], &endPtr, 10);
		if (*endPtr != 0 || endPtr == av[i])
			throw(std::runtime_error("Error: argv\n"));
		if (num <= 0 || num > 2147483647)
			throw(std::runtime_error("Error: argv\n"));
		v.push_back(num);
		d.push_back(num);
	}
};

int main(int ac, char** av){
	std::vector<int>	ov; // originVector
	std::deque<int>		od; // originDeque
	
	try{
		getInput(ac, av, ov, od);
	}catch(std::exception& e){
		std::cerr << e.what();
		return (1);
	}

	//Before
	std::cout << "Berfore: ";
	for (std::deque<int>::iterator i = od.begin(); i != od.end(); i++)
		std::cout << *i << " " ;
	std::cout <<"\n";

	//merge sort
	PmergeMe pmmV(ov);
	PmergeMe pmmD(od);

	//After
	std::cout << "After:   ";
	for (std::deque<int>::iterator i = od.begin(); i != od.end(); i++)
		std::cout << *i << " " ;
	std::cout <<"\n";

	//prt spec
	pmmV.prtSpecification();
	pmmD.prtSpecification();

	//prove
	try{
		for(std::vector<int>::iterator it = ov.begin() ; it < ov.end() - 1 ; it ++){
			if (*it > *(it + 1))
				throw(std::runtime_error("Error: Vector not sorted\n"));
		}
		for(std::deque<int>::iterator it = od.begin() ; it < od.end() - 1 ; it ++){
			if (*it > *(it + 1))
				throw(std::runtime_error("Error: Deque not sorted\n"));
		}
	}catch(std::exception& e){
		std::cerr<<e.what();
	}
}