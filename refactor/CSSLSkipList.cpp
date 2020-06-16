#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <immintrin.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <iostream>
#include <stdalign.h>
#include <stdexcept>
#include <memory>
#include <functional>
#include <numeric>
#include "CSSLSkipList.h"

using namespace std;

void CSSLSkipList::createSkipList(int maxLevel, int skip) {


  this->maxLevel = maxLevel;
  this->skip  = skip;
  this->numberOfElements     = 0;
  std::vector<uint64_t> itemsPerLevel(maxLevel);
  std::vector<uint64_t> startOfFastLane(maxLevel);
  std::vector<uint64_t> fastLaneItems;
  std::vector<uint64_t> fastLanes;

}




void CSSLSkipList::insertElement(uint64_t key)
{
  addElementToSkipList(key);
  
  for (int level = 0;level < maxLevel;level++)
    {
      insertItemIntoFastLane(level,key);
    }
}

void CSSLSkipList::insertItemIntoFastLane(int level,uint64_t key)
{
  cout << "The value of level is " <<level << endl;
  //int index1 = startOfFastLane.at(level);
  //cout << "The value of index1 is " <<index1 << endl;
  //int index2 = fastLaneItems[level];
  //cout << "The value of index2 is " <<index2 << endl;


  //int index3 = itemsPerLevel[level];
  //itr2 = std::find(fastLaneItems.begin(),fastLaneItems.end(),level);
  //itr3 = std::find(itemsPerLevel.begin(),itemsPerLevel.end(),level);
  //int index1 = std::distance(startOfFastLane.begin(),itr);
  //int index2 = std::distance(fastLaneItems.begin(),itr);
  //uint64_t curPos = index1 + index2;
  //cout << "The value of curPos is " <<curPos << endl;
  //int index3 = std::distance(itemsPerLevel.begin(),itr);
  ///uint64_t levelLimit = curPos + index3;
  //if (curPos > levelLimit)
  //  curPos = levelLimit;

  //while(key > fastLanes.at(curPos) && curPos < levelLimit)
  //  curPos++;

  //fastLanes.insert(fastLanes.begin()+curPos,key);

}

void CSSLSkipList::addElementToSkipList(uint64_t key)
{
  (*skipList).push_back(key);
}
