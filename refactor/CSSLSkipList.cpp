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
  std::vector<uint64_t> itemsPerLevel(maxLevel);
  std::vector<uint64_t> startOfFastLane(maxLevel);
  std::vector<uint64_t> fastLaneItems;
  std::vector<uint64_t> fastLanes;

  for (uint8_t level = 0; level < maxLevel; level++)
    {
      fastLaneItems.push_back(0);
    }

  calculateFastLaneSize();
  
  allocateFastLanes();
}


void CSSLSkipList::allocateFastLanes()
{
    for (int i = 0; i < fastLaneSize; i++)
      {
	fastLanes.push_back(LONG_MAX);
      }
}

void CSSLSkipList::calculateFastLaneSize()
{
  fastLaneSize = TOP_LANE_BLOCK;

  cout << "The value of fastLaneSize is " <<fastLaneSize << endl;

  cout <<"The value of maxLevel is" << maxLevel << endl;
  itemsPerLevel.at(maxLevel)=fastLaneSize;
  itemsPerLevel.push_back(fastLaneSize);
  //startOfFastLane.at(maxLevel-1)=0;
  int current = fastLaneSize;
  // calculate level sizes level by level
  uint64_t value;
  for (int level = this->maxLevel - 2; level >= 0; level--)
    {
      current *= skip;
      cout << "The value of current is " <<current << endl;
      //itemsPerLevel.at(level) = current;
      //value = startOfFastLane.at(level+1) +itemsPerLevel.at(level+1);
      //cout << "The value of value is " << value << endl;
      //startOfFastLane.at(level)=value;
      //fastLaneSize += itemsPerLevel.at(level);
    }
  exit(0);
  cout << "The start of fast lane is " <<itemsPerLevel.at(1) << endl;
  cout << "The start of fastLaneSize is " <<fastLaneSize << endl;
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
  int index1 = startOfFastLane.at(level);
  cout << "The value of index1 is " <<index1 << endl;
  exit(0);
  int index2 = fastLaneItems[level];
  cout << "The value of index2 is " <<index2 << endl;
  exit(0);

  int index3 = itemsPerLevel[level];
  //itr2 = std::find(fastLaneItems.begin(),fastLaneItems.end(),level);
  //itr3 = std::find(itemsPerLevel.begin(),itemsPerLevel.end(),level);
  //int index1 = std::distance(startOfFastLane.begin(),itr);
  //int index2 = std::distance(fastLaneItems.begin(),itr);
  uint64_t curPos = index1 + index2;
  cout << "The value of curPos is " <<curPos << endl;
  exit(0);
  //int index3 = std::distance(itemsPerLevel.begin(),itr);
  uint64_t levelLimit = curPos + index3;
  if (curPos > levelLimit)
    curPos = levelLimit;

  while(key > fastLanes.at(curPos) && curPos < levelLimit)
    curPos++;

  fastLanes.insert(fastLanes.begin()+curPos,key);

}

void CSSLSkipList::addElementToSkipList(uint64_t key)
{
  skipList.push_back(key);
}
