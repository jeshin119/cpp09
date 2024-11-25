# include <iostream>
# include <vector>
# include <deque>
# include <sys/time.h>
# include <iomanip>
# include <algorithm>
# include "PmergeMe.hpp"

PmergeMe::PmergeMe(std::vector<int>& v) : _cnt(0), _range(v.size()) , _type("std::vector"){
	struct timeval		startTime;
	struct timeval		endTime;

	gettimeofday(&startTime, 0);
	if (v.size() != 1)
		_mergeInsertionSort(&v, 0);
	gettimeofday(&endTime, 0);
	_duration = (endTime.tv_sec - startTime.tv_sec) * 1000000 + (endTime.tv_usec - startTime.tv_usec);
}

PmergeMe::PmergeMe(std::deque<int>& d) : _cnt(0), _range(d.size()) , _type("std::deque"){
	struct timeval		startTime;
	struct timeval		endTime;

	gettimeofday(&startTime, 0);

	if (d.size() != 1)
		_mergeInsertionSort(&d, 0);

	gettimeofday(&endTime, 0);
	_duration = (endTime.tv_sec - startTime.tv_sec) * 1000000 + (endTime.tv_usec - startTime.tv_usec);
}

PmergeMe::~PmergeMe(){}

void	PmergeMe::_mergeInsertionSort(std::vector<int>* pmc, std::vector<int>* psc){ //pmc : prev main chain, psc : prev sub chain
	if (pmc->size() == 1)
		return ;
	if (pmc->size() == 2){
		_cnt++;
		if (pmc->at(0) >= pmc->at(1)){
			std::swap(pmc->at(0), pmc->at(1));
			std::swap(psc->at(0), psc->at(1));
		}
		return ;
	}
	std::vector<int> mainChain;
	std::vector<int> subChain;
	std::vector<int> mic; // mainIdxChain
	std::vector<int> sic; // subIdxChain
	for(std::vector<int>::iterator it = pmc->begin() ; it < pmc->end() ; it += 2){
		if (it == pmc->end() - 1){
			subChain.push_back(*it);
			sic.push_back(it - pmc->begin());
			break;
		}
		_cnt++;
		if (*it >= *(it + 1)){
			mainChain.push_back(*it);
			subChain.push_back(*(it + 1));
			mic.push_back(it - pmc->begin());
			sic.push_back((it + 1) - pmc->begin());
		}else{
			mainChain.push_back(*(it + 1));
			subChain.push_back(*it);
			mic.push_back((it + 1) - pmc->begin());
			sic.push_back(it - pmc->begin());
		}
	}

	_mergeInsertionSort(&mainChain, &subChain);

	std::vector<int> jacobNums;
	_getJacobsthalNumbers(jacobNums, subChain.size());
	int	mergeCnt = 0;
	for (size_t i = 0; i != jacobNums.size() ; i++){
		int jacobNumIdx = jacobNums[i] - 1;
		while (jacobNumIdx >= 0 && (i == 0 || jacobNumIdx > jacobNums[i - 1] - 1)){
			int there = _binaryInsert(subChain[jacobNumIdx], mergeCnt + jacobNumIdx, mainChain);
			if (psc)
				mic.insert(mic.begin() + there, sic[jacobNumIdx]);
			mergeCnt++;
			jacobNumIdx--;
		}
	}
	size_t jacobNumEndIdx = *(jacobNums.end() - 1) - 1;
	for (size_t i = subChain.size() - 1 ; i > jacobNumEndIdx ; i--){
		if (i + mergeCnt > mainChain.size() - 1){
			int there = _binaryInsert(subChain[i], mainChain.size(), mainChain);
			mergeCnt++;
			if (psc)
				mic.insert(mic.begin() + there, sic[i]);
		}
		else{
			int there = _binaryInsert(subChain[i], mergeCnt + i, mainChain);
			mergeCnt++;
			if (psc)
				mic.insert(mic.begin() + there, sic[i]);
		}
	}
	std::vector<int> linkChain;
	if (psc){
		size_t i = -1;
		while (++i < mic.size())
			linkChain.push_back(psc->at(mic[i]));
		while (i < psc->size())
			linkChain.push_back(psc->at(i++));
		*psc = linkChain;
	}
	*pmc = mainChain;

// prt mainchain
	std::cout<<"mainchain: ";
	for(unsigned long i=0;i<pmc->size();i++){
		std::cout<<pmc->at(i)<<" ";
	}
	std::cout<<"\n";
// prt psc
	if (psc){
		std::cout<<"subchain: ";
		for(unsigned long i=0;i<psc->size();i++){
			std::cout<<psc->at(i)<<" ";
		}
		std::cout<<"\n";
	}
}

void	PmergeMe::_mergeInsertionSort(std::deque<int>* pmc, std::deque<int>* psc){
	if (pmc->size() == 1)
		return ;
	if (pmc->size() == 2){
		_cnt++;
		if (pmc->at(0) >= pmc->at(1)){
			std::swap(pmc->at(0), pmc->at(1));
			std::swap(psc->at(0), psc->at(1));
		}
		return ;
	}
	std::deque<int> mainChain;
	std::deque<int> subChain;
	std::deque<int> mic; // mainIdxChain
	std::deque<int> sic; // subIdxChain
	for(std::deque<int>::iterator it = pmc->begin() ; it < pmc->end() ; it += 2){
		if (it == pmc->end() - 1){
			subChain.push_back(*it);
			sic.push_back(it - pmc->begin());
			break;
		}
		_cnt++;
		if (*it >= *(it + 1)){
			mainChain.push_back(*it);
			subChain.push_back(*(it + 1));
			mic.push_back(it - pmc->begin());
			sic.push_back((it + 1) - pmc->begin());
		}else{
			mainChain.push_back(*(it + 1));
			subChain.push_back(*it);
			mic.push_back((it + 1) - pmc->begin());
			sic.push_back(it - pmc->begin());
		}
	}

	_mergeInsertionSort(&mainChain, &subChain);

	std::deque<int> jacobNums;
	_getJacobsthalNumbers(jacobNums, subChain.size());
	int	mergeCnt = 0;
	for (size_t i = 0; i != jacobNums.size() ; i++){
		int jacobNumIdx = jacobNums[i] - 1;
		while (jacobNumIdx >= 0 && (i == 0 || jacobNumIdx > jacobNums[i - 1])){
			int there = _binaryInsert(subChain[jacobNumIdx], mergeCnt + jacobNumIdx, mainChain);
			if (psc)
				mic.insert(mic.begin() + there, sic[jacobNumIdx]);
			mergeCnt++;
			jacobNumIdx--;
		}
	}
	size_t jacobNumEndIdx = *(jacobNums.end() - 1) - 1;
	for (size_t i = subChain.size() - 1 ; i > jacobNumEndIdx ; i--){
		if (i + mergeCnt > mainChain.size() - 1){
			int there = _binaryInsert(subChain[i], mainChain.size(), mainChain);
			if (psc)
				mic.insert(mic.begin() + there, sic[i]);
		}
		else{
			int there = _binaryInsert(subChain[i], mergeCnt + i, mainChain);
			if (psc)
				mic.insert(mic.begin() + there, sic[i]);
		}
	}
	std::deque<int> linkChain;
	if (psc){
		size_t i = -1;
		while (++i < mic.size())
			linkChain.push_back(psc->at(mic[i]));
		while (i < psc->size())
			linkChain.push_back(psc->at(i++));
		*psc = linkChain;
	}
	*pmc = mainChain;
}

int	PmergeMe::_binaryInsert(const int& val, int end, std::vector<int>& mc){
	int start = 0;
	int mid;

	while (start < end){
		mid = (end - start) / 2 + start;
		_cnt++;
		if (val >= mc[mid])
			start = mid + 1;
		else
			end = mid;
	}
	mc.insert(mc.begin() + start , val);
	return (start);
}

int		PmergeMe::_binaryInsert(const int& val, int end, std::deque<int>& mc){
	int start = 0;
	int mid;

	while (start < end){
		mid = (end - start) / 2 + start;
		_cnt++;
		if (val >= mc[mid])
			start = mid + 1;
		else
			end = mid;
	}
	mc.insert(mc.begin() + start , val);
	return (start);
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

void	PmergeMe::_getJacobsthalNumbers(std::deque<int>& jacobNums, const int size){
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
	std::cout<<"Time to process a range of "<<_range<<" elements with "<<_type<<" "<< std::fixed<<std::setprecision(5)<<_duration<<" us"<<"cnt: "<< _cnt<<"\n";
}