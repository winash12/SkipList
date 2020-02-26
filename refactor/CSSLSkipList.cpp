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

void CSSLSkipList::createSkipList(uint8_t max_level, int skip) {


  this->maxLevel = max_level;
  this->skip  = skip;
  this->numberOfElements     = 0;

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
	fastLaneProxyNodes.push_back(LONG_MAX);
      }
}

void CSSLSkipList::calculateFastLaneSize()
{
  fastLaneSize = TOP_LANE_BLOCK;
  std::vector<uint64_t> fastLanes;    
  itemsPerLevel.insert(itemsPerLevel.end(),fastLaneSize);
  startOfFastLane.insert(startOfFastLane.end(),0);

  int current = fastLaneSize;
  // calculate level sizes level by level
  uint64_t value;
  for (int8_t level = this->maxLevel - 2; level >= 0; level--)
    {
      current *= skip;
      itemsPerLevel.insert(itemsPerLevel.end()+level,current);
      value = startOfFastLane.at(level+1) +itemsPerLevel.at(level+1);
      startOfFastLane.insert(startOfFastLane.end()+level,value);
      fastLaneSize += itemsPerLevel.at(level);
    }


}

void CSSLSkipList::insertElement(uint64_t key)
{
  addElementToSkipList(key);
  for (uint8_t level = 0;level < maxLevel;level++)
    {
    }
}

void CSSLSkipList::addElementToSkipList(uint64_t key)
{
  skipList.push_back(key);
}
