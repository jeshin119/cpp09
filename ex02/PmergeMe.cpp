# include <iostream>
# include <vector>
# include <deque>
# include <algorithm>
# include "PmergeMe.hpp"
# include <ctime>
# include <cstring>

PmergeMe::PmergeMe(std::vector<int>& v) : _cnt(0), _range(v.size()) , _type("std::vector"){
	std::clock_t start = std::clock();
	if (v.size() != 1)
		_mergeInsertionSort(&v, 0, 0);
    std::clock_t end = std::clock();
    _duration = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;
}

PmergeMe::PmergeMe(std::deque<int>& d) : _cnt(0), _range(d.size()) , _type("std::deque"){
	std::clock_t start = std::clock();
	if (d.size() != 1)
		_mergeInsertionSort(&d, 0, 0);
    std::clock_t end = std::clock();
    _duration = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;
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
			if (psc)
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
		bool visited[ppc->size()];
		std::memset(visited, 0, ppc->size());
		for (size_t i = 0 ; i != pmc->size() ; i++){
			for(size_t j = 0 ; j != ppc->size() ; j++){
				if (!visited[j] && (*pmc)[i] == (*ppc)[j].first){
					(*psc)[i] = (*ppc)[j].second;
					visited[j] = 1;
					break;
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
void	PmergeMe::_mergeInsertionSort(std::deque<int>* pmc, std::deque<int>* psc, std::deque<pair>* ppc){
	if (pmc->size() == 1)
		return ;
	if (pmc->size() == 2){
		_cnt++;
		if (pmc->at(0) >= pmc->at(1)){
			std::swap(pmc->at(0), pmc->at(1));
			if (psc)
				std::swap(psc->at(0), psc->at(1));
		}
		return ;
	}

	std::deque<int> mainChain;
	std::deque<int> subChain;
	std::deque<pair> pairChain;
	for (std::deque<int>::iterator it = pmc->begin() ; it < pmc->end() ; it += 2){
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

	_mergeInsertionSort(&mainChain, &subChain, &pairChain);

	std::deque<int> jacobNums;
	_getJacobsthalNumbers(jacobNums, subChain.size());
	int	mergeCnt = 0;

	for (size_t i = 0; i != jacobNums.size() ; i++){
		int jacobNumIdx = jacobNums[i] - 1;
		while (jacobNumIdx >= 0 && (i == 0 || jacobNumIdx > jacobNums[i - 1] - 1)){
			_binaryInsert(subChain[jacobNumIdx], mergeCnt + jacobNumIdx, mainChain);
			mergeCnt++;
			jacobNumIdx--;
		}
	}

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

	*pmc = mainChain;
	if (psc){
		bool visited[ppc->size()];
		std::memset(visited, 0, ppc->size());
		for (size_t i = 0 ; i != pmc->size() ; i++){
			for(size_t j = 0 ; j != ppc->size() ; j++){
				if (!visited[j] && (*pmc)[i] == (*ppc)[j].first){
					(*psc)[i] = (*ppc)[j].second;
					visited[j] = 1;
					break;
				}
			}
		}
		if ((*ppc)[ppc->size() - 1].first == 0)
			(*psc)[psc->size() - 1] = (*ppc)[ppc->size() - 1].second;
	}
}

void	PmergeMe::_binaryInsert(const int& val, int end, std::vector<int>& mc){
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
}

void	PmergeMe::_binaryInsert(const int& val, int end, std::deque<int>& mc){
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
	std::cout<<"Time to process a range of "<<_range<<" elements with "<<_type<<" "<<_duration<<"ms"<<" cnt: "<< _cnt<<"\n";
}