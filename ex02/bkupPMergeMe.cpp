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
		_mergeInsertionSort(&v, 0);
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
void	PmergeMe::_mergeInsertionSort(std::vector<int>* pmc, std::vector<int>* psc){
	if (pmc->size() == 1)
		return ;
	if (pmc->size() == 2){
		_cnt++;
		if (pmc->at(0) >= pmc->at(1)){
			std::swap(pmc->at(0), pmc->at(1));
			std::swap(psc->at(0), psc->at(1));
			// swapLog[0] = 1;
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
	// int sl[tmpMainChain.size()]; //sl : swaplog
	// std::fill(sl, sl + tmpMainChain.size(), 0);
	_mergeInsertionSort(&tmpMainChain, &tmpSubChain);
	// for (size_t i = 0 ; i != tmpMainChain.size() ; i++){
	// 	if (!sl[i])
	// 		continue;
	// 	std::swap(tmpSubChain.at(i), tmpSubChain.at(sl[i]));
	// }
	std::vector<int> jacobNums;
	_getJacobsthalNumbers(jacobNums, tmpSubChain.size());
	int	mergeCnt = 0;
	for (size_t i = 0; i != jacobNums.size() ; i++){
		int jacobNumIdx = jacobNums[i] - 1;
		while (jacobNumIdx >= 0 && (i == 0 || jacobNumIdx > jacobNums[i - 1])){
			mergeCnt++;
			int there = _binaryInsert(tmpSubChain[jacobNumIdx], jacobNumIdx, tmpMainChain);
			std::swap(psc->at(there), psc->at(jacobNumIdx));
			jacobNumIdx--;
		}
	}
	size_t jacobNumEndIdx = *(jacobNums.end() - 1) - 1;
	for (size_t i = tmpSubChain.size() - 1 ; i > jacobNumEndIdx ; i--){
		if (i + mergeCnt > tmpMainChain.size() - 1)
			_binaryInsert(tmpSubChain[i], tmpMainChain.size() - 1, tmpMainChain);
		else{
			int there = _binaryInsert(tmpSubChain[i], i + mergeCnt, tmpMainChain);
			std::swap(psc->at(there), psc->at(i));
		}
	}
	*pmc = tmpMainChain;
}
int	PmergeMe::_binaryInsert(const int& val, int end, std::vector<int>& mc){
	// const int val = sc[here];
	int start = 0;
	int mid;

	while (start < end){
		mid = (end - start) / 2 + start;
		_cnt++;
		if (val >= mc[mid])
			start = mid + 1;
		else
			end = mid - 1;
	}
	if (end >= 0 && start >= end){
		mc.insert(mc.begin() + end , val);
		return (end);
	}else{
		mc.insert(mc.begin() + start , val);
		return (start);
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