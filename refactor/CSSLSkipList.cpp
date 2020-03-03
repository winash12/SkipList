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

#include <functional>
#include <numeric>
#include "CSSLSkipList.h"

using namespace std;

void CSSLSkipList::createSkipList(int maxLevel, int skip) {


  this->maxLevel = maxLevel;
  this->skip  = skip;
  this->numberOfElements     = 0;
  cout <<"The value of maxLevel is " << this->maxLevel<<endl;
  cout <<"The value of skip is " << this->skip<<endl;
  std::vector<uint64_t> itemsPerLevel(maxLevel);
  std::vector<uint64_t> startOfFastLane(maxLevel);
  std::vector<uint64_t> fastLaneItems(maxLevel);


  for (uint8_t level = 0; level < maxLevel; ++level)
    {
      fastLaneItems.push_back(0);
    }

  calculateFastLaneSize();

  allocateFastLanes();

}


void CSSLSkipList::allocateFastLanes()
{
    for (uint32_t i = 0; i < fastLaneSize; i++)
      {
	fastLanes.push_back(LONG_MAX);
      }
}

void CSSLSkipList::calculateFastLaneSize()
{
  fastLaneSize = TOP_LANE_BLOCK;

  cout << "The value of fastLaneSize is " <<fastLaneSize << endl;

  std::vector<uint64_t> fastLanes;    
  itemsPerLevel.insert(itemsPerLevel.end(),fastLaneSize);
  startOfFastLane.insert(startOfFastLane.end(),0);

  int current = fastLaneSize;
  // calculate level sizes level by level
  uint64_t value;
  for (int level = this->maxLevel - 2; level >= 0; level--)
    {
      current *= skip;
      cout << "The value of current is " <<current << endl;
      itemsPerLevel.push_back(current);
      value = startOfFastLane[level+1] +itemsPerLevel[level+1];
      startOfFastLane.push_back(value);
      fastLaneSize += itemsPerLevel[level];
    }

  exit(0);
}

void CSSLSkipList::insertElement(uint64_t key)
{
  addElementToSkipList(key);
  for (uint8_t level = 0;level < maxLevel;level++)
    {
      insertItemIntoFastLane(level,key);
    }
}

void CSSLSkipList::insertItemIntoFastLane(int8_t level,uint64_t key)
{

  itr = std::find(startOfFastLane.begin(),startOfFastLane.end(),level);
  itr2 = std::find(fastLaneItems.begin(),fastLaneItems.end(),level);
  itr3 = std::find(itemsPerLevel.begin(),itemsPerLevel.end(),level);
  int index1 = std::distance(startOfFastLane.begin(),itr);
  int index2 = std::distance(fastLaneItems.begin(),itr);
  uint64_t curPos = index1 + index2;
  int index3 = std::distance(itemsPerLevel.begin(),itr);
  uint64_t levelLimit = curPos + index3;
  if (curPos > levelLimit)
    curPos = levelLimit;

  while(key > fastLanes.at(curPos) && curPos < levelLimit)
    curPos++;

  fastLanes.insert(fastLanes.begin()+curPos,key);
  (*itr2)++;
}

void CSSLSkipList::addElementToSkipList(uint64_t key)
{
  skipList.push_back(key);
}
