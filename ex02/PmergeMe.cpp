# include <iostream>
# include <vector>
# include <deque>
# include <sys/time.h>
# include <iomanip>
# include <algorithm>
# include "PmergeMe.hpp"

PmergeMe::PmergeMe(std::vector<int>& v) : _cnt(0), _range(v.size()) , _type("std::vector"){
	gettimeofday(&_startTime, 0);
	if (v.size() != 1)
		_mergeInsertionSort(&v, 0, 0);
	gettimeofday(&_endTime, 0);
	_duration = (_endTime.tv_sec - _startTime.tv_sec) * 1000000 + (_endTime.tv_usec - _startTime.tv_usec);
}

PmergeMe::PmergeMe(std::deque<int>& d) : _cnt(0), _range(d.size()) , _type("std::deque"){
	gettimeofday(&_startTime, 0);

	// _mergeInsertion(d, 0);

	gettimeofday(&_endTime, 0);
	_duration = (_endTime.tv_sec - _startTime.tv_sec) * 1000000 + (_endTime.tv_usec - _startTime.tv_usec);

}

PmergeMe::~PmergeMe(){}

//pmc : prev main chain, psc : prev sub chain
void	PmergeMe::_mergeInsertionSort(std::vector<int>* pmc, std::vector<int>* psc, int *swapLog){
	if (pmc->size() == 1)
		return ;
	if (pmc->size() == 2){
		_cnt++;
		if (pmc->at(0) >= pmc->at(1)){
			std::swap(psc->at(0), psc->at(1));
			swapLog[0] = 1;
		}
		return ;
	}
	std::vector<int> tmpMainChain;
	std::vector<int> tmpSubChain;
	for(std::vector<int>::iterator it = pmc->begin() ; it < pmc->end() ; it += 2){
		if (it == pmc->end() - 1){
			tmpSubChain.push_back(*it);
			break;
		}
		_cnt++;
		if (*it >= *(it + 1)){
			tmpMainChain.push_back(*it);
			tmpSubChain.push_back(*(it + 1));
		}else{
			tmpMainChain.push_back(*(it + 1));
			tmpSubChain.push_back(*it);
		}
	}
	int sl[tmpMainChain.size()]; //sl : swaplog
	std::fill(sl, sl + tmpMainChain.size(), 0);
	_mergeInsertionSort(&tmpMainChain, &tmpSubChain, sl);
	for (int i = 0 ; i != tmpMainChain.size() ; i++){
		if (!sl[i])
			continue;
		std::swap(tmpSubChain.at(i), tmpSubChain.at(sl[i]));
	}
	std::vector<int> jacobNums;
	_getJacobsthalNumbers(jacobNums, tmpSubChain.size());

	for (int i = 1; i != jacobNums.size() ; i++){
		int front = jacobNums[i];
		while (front && front > jacobNums[i - 1])
	}
	while (jacobNums.size()){
		int k = jacobNums.front();
		jacobNums.pop
		for (int i = jacobNums.front() ; i !=)
		_binaryInsert(tmpSubChain[jacobNums.front()],tmpMainChain);
	}
}
void	PmergeMe::_binaryInsert(const int& val, int end, std::vector<int>& mc){
	int start = 0;
	int end = mc.size() - 1;
	int mid;

	while (start < end){
		mid = (end - start) / 2 + start;
		_cnt++;
		if (val >= mc[mid])
			start = mid + 1;
		else
			end = mid - 1;
	}
	if (start > end){
		mc.insert(mc.begin() + end , val);
	}else{
		mc.insert(mc.begin() + start , val);
	}
}
void	PmergeMe::_getJacobsthalNumbers(std::vector<int>& jacobNums, const int size){
	int x = 0;
	int y = 1;
	int tmpX;
	while ((2 * x + y) < size){
		tmpX = x;
		x = y;
		y = 2 * tmpX + y;
		jacobNums.push_back(y);
	}
}

void	PmergeMe::prtSpecification(){
	std::cout<<"Time to process a range of "<< _range << " elements with " << _type << " " << std::fixed <<std::setprecision(5) <<_duration << " us\n";
}