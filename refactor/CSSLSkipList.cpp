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


CSSLSkipList::CSSLSkipList(int maxLevel,int skip,int initialFastLaneSize)
{
   this->maxLevel = maxLevel;
   this->skip  = skip;
   this->initialFastLaneSize = initialFastLaneSize;
   for (int i = 0; i < maxLevel; ++i )
     {
       (*fastLaneItems).push_back(0);
     }
}


void CSSLSkipList::calculateFastLaneSize()

{

  cout <<"The value of maxLevel is" << maxLevel << endl;
  (*itemsPerLevel).at(maxLevel)=initialFastLaneSize;
  (*itemsPerLevel).push_back(initialFastLaneSize);
  (*startOfFastLane).at(maxLevel)=0;
  int current = initialFastLaneSize;
  // calculate level sizes level by level
  int value;
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
  for ( int i = 0; i < fastLaneSize; ++i )
    {
      (*fastLanes).push_back(INT_MAX);
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
  int index2 = (*fastLaneItems).at(level);
  cout << "The value of index2 is " <<index2 << endl;


  int index3 = (*itemsPerLevel).at(level);

  int curPos = index1 + index2;
  cout << "The value of curPos is " <<curPos << endl;

  int levelLimit = curPos + index3;
  if (curPos > levelLimit)
    curPos = levelLimit;

  while(key > (*fastLanes).at(curPos) && curPos < levelLimit)
    curPos++;

  (*fastLanes).insert((*fastLanes).begin()+curPos,key);

}

void CSSLSkipList::addElementToSkipList(uint64_t key)
{
  (*skipList).push_back(key);
}
