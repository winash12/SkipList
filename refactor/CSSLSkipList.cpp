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

void CSSLSkipList::createSkipList(uint8_t max_level, uint8_t skip) {


  this->maxLevel = max_level;
  this->skip  = skip;
  std::vector<uint64_t> itemsPerLevel(maxLevel);
  numberOfElements     = 0;
  std::vector<uint64_t> startOfFastLane(maxLevel);
  std::vector<uint64_t> fastLaneItems(maxLevel);

  
  /*for (uint8_t level = 0; level < maxLevel; ++level)
    {
      slist->flane_items[level] = 0;
    }
  */
  //calculateFastLaneSizes();
  //allocateFastLanes();

}


void CSSLSkipList::insertElement(uint64_t key)
{
  addElementToSkipList(key);
}

void CSSLSkipList::addElementToSkipList(uint64_t key)
{
  skipList.push_back(key);
}
