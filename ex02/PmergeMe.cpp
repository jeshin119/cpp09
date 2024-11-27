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
	if (v.size() != 1){
		_mergeInsertionSort(&v, 0, 0);
}
	gettimeofday(&endTime, 0);
	_duration = (endTime.tv_sec - startTime.tv_sec) * 1000000 + (endTime.tv_usec - startTime.tv_usec);
}

PmergeMe::~PmergeMe(){}

 //pmc : prev main chain, psc : prev sub chain, ppc : prev pair chain
void	PmergeMe::_mergeInsertionSort(std::vector<int>* pmc, std::vector<int>* psc, std::vector<pair>* ppc){
	//종료조건
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

	//분할
	std::vector<int> mainChain;
	std::vector<int> subChain;
	std::vector<pair> pairChain;
	for (std::vector<int>::iterator it = pmc->begin() ; it < pmc->end() ; it += 2){
		if (it == pmc->end() - 1){
			subChain.push_back(*it);
			pairChain.push_back(pair(0,*it));
			break;
		}
		_cnt++;
		if (*it >= *(it + 1)){
			mainChain.push_back(*it);
			subChain.push_back(*(it + 1));
			pairChain.push_back(pair(*it, *(it + 1)));
		}
		else{
			mainChain.push_back(*(it + 1));
			subChain.push_back(*it);
			pairChain.push_back(pair(*(it + 1), *it));
		}
	}

	//재귀호출
	_mergeInsertionSort(&mainChain, &subChain, &pairChain);

	//이진삽입
	std::vector<int> jacobNums;
	_getJacobsthalNumbers(jacobNums, subChain.size());
	int	mergeCnt = 0;

	//이진삽입 역순으로 진행
	for (size_t i = 0; i != jacobNums.size() ; i++){
		int jacobNumIdx = jacobNums[i] - 1;
		while (jacobNumIdx >= 0 && (i == 0 || jacobNumIdx > jacobNums[i - 1] - 1)){
			_binaryInsert(subChain[jacobNumIdx], mergeCnt + jacobNumIdx, mainChain);
			mergeCnt++;
			jacobNumIdx--;
		}
	}
	//나머지 이진삽입 진행
	size_t jacobNumEndIdx = *(jacobNums.end() - 1) - 1;
	for (size_t i = subChain.size() - 1 ; i > jacobNumEndIdx ; i--){
		if (i + mergeCnt > mainChain.size() - 1){
			_binaryInsert(subChain[i], mainChain.size(), mainChain);
			mergeCnt++;
		}
		else{
			_binaryInsert(subChain[i], mergeCnt + i, mainChain);
			mergeCnt++;
		}
	}

	//갱신
	*pmc = mainChain;
	if (psc){
		for (size_t i = 0 ; i != pmc->size() ; i++){
			for(size_t j = 0 ; j != ppc->size() ; j++){
				if ((*pmc)[i] == (*ppc)[j].first){
					(*psc)[i] = (*ppc)[j].second;
				}
			}
		}
		if ((*ppc)[ppc->size() - 1].first == 0)
			(*psc)[psc->size() - 1] = (*ppc)[ppc->size() - 1].second;
	}

// prt mainchain
	// std::cout<<"mainchain: ";
	// for(unsigned long i=0;i<pmc->size();i++){
	// 	std::cout<<pmc->at(i)<<" ";
	// }
	// std::cout<<"\n";
// prt subchain
	// if (psc){
	// 	std::cout<<"subchain: ";
	// 	for(unsigned long i=0;i<psc->size();i++){
	// 		std::cout<<psc->at(i)<<" ";
	// 	}
	// 	std::cout<<"\n";
	// }
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
	std::cout<<"Time to process a range of "<<_range<<" elements with "<<_type<<" "<< std::fixed<<std::setprecision(5)<<_duration<<" us"<<"cnt: "<< _cnt<<"\n";
}