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

using std::vector;
using std::cout;
using std::endl;


CSSLSkipList::CSSLSkipList(int maxLevel,int skip,int fastLaneSize)
{
   this->maxLevel = maxLevel;
   this->skip  = skip;
   this->fastLaneSize = fastLaneSize;
 
}

/*void CSSLSkipList::createSkipList(int maxLevel, int skip) {


  this->maxLevel = maxLevel;
  this->skip  = skip;
  this->numberOfElements     = 0;
  //std::vector<uint64_t> fastLaneItems;
  //std::vector<uint64_t> fastLanes;

  }*/


void CSSLSkipList::calculateFastLaneSize(int fastLaneSize,int maxLevel,int skip)
{

  cout <<"The value of maxLevel is" << maxLevel << endl;
  (*itemsPerLevel).at(maxLevel)=fastLaneSize;
  (*itemsPerLevel).push_back(fastLaneSize);
  (*startOfFastLane).at(maxLevel-1)=0;
  int current = fastLaneSize;
  // calculate level sizes level by level
  uint64_t value;
  for (int level = this->maxLevel - 2; level >= 0; level--)
    {
      current *= skip;
      cout << "The value of current is " <<current << endl;
      (*itemsPerLevel).at(level) = current;
      value = (*startOfFastLane).at(level+1) +(*itemsPerLevel).at(level+1);
      cout << "The value of value is " << value << endl;
      (*startOfFastLane).at(level)=value;
      fastLaneSize += (*itemsPerLevel).at(level);
    }
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
  int index1 = (*startOfFastLane).at(level);
  cout << "The value of index1 is " <<index1 << endl;
  int index2 = fastLaneItems[level];
  cout << "The value of index2 is " <<index2 << endl;


  int index3 = (*itemsPerLevel).at(level);
  //itr2 = std::find(fastLaneItems.begin(),fastLaneItems.end(),level);
  //itr3 = std::find(itemsPerLevel.begin(),itemsPerLevel.end(),level);
  //int index1 = std::distance(startOfFastLane.begin(),itr);
  //int index2 = std::distance(fastLaneItems.begin(),itr);
  int curPos = index1 + index2;
  cout << "The value of curPos is " <<curPos << endl;
  //int index3 = std::distance(itemsPerLevel.begin(),itr);
  int levelLimit = curPos + index3;
  if (curPos > levelLimit)
    curPos = levelLimit;

  //while(key > fastLanes.at(curPos) && curPos < levelLimit)
  //  curPos++;

  //fastLanes.insert(fastLanes.begin()+curPos,key);

}

void CSSLSkipList::addElementToSkipList(uint64_t key)
{
  (*skipList).push_back(key);
}
