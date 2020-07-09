#include <iostream>
#include "CSSLSkipList.h"
using namespace std;
class SkipList;
int main(void) {

	int maxLevel;
	int skip;
	int fastLaneSize;
	maxLevel = 9;
	skip = 5;
	fastLaneSize = 8;

	CSSLSkipList skipList(maxLevel, skip, fastLaneSize);
	vector<uint64_t> inputData;
	for (uint64_t i = 0; i < 100000; i += 1000) {
	  //cout << "The value of i is " << i << endl;
	  inputData.push_back(i);
	}
	skipList.insertItemsIntoFastLanes(inputData);
	exit(0);
	//skipList.printFastLanes();class test

	//exit(0);

	//uint64_t key = 500;
	//uint64_t keyT = skipList.searchElement(2500);
	//cout << "The value of key T is " << keyT << endl;
	//_CSSL_RangeSearchResult result = skipList.searchRange(500, 2500);

	//node = result.start;
	//cout <<"The value of start is " << result.start->key << endl; {
	//cout <<"The value of key is " << node->key << endl;
	//node = (shared_ptr<_CSSL_DataNode>)node->next;
	//cout <<"The value of end is " << result.end->key << endl;*/
	return 0;
}
