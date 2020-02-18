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

void CSSLSkipList::createSkipList(uint8_t maxLevel, uint8_t skip) {



  //slist->num_elements     = 0;

  //slist->items_per_level  = (uint64_t*)malloc(sizeof(uint64_t) * maxLevel);
  //slist->items_per_level  = (uint64_t*)malloc(sizeof(uint64_t)*maxLevel);
  //Array
  //slist->starts_of_flanes = (uint64_t*)malloc(sizeof(uint64_t)*maxLevel);
  //Array
  //slist->flane_items      =(uint64_t*)malloc(sizeof(uint64_t)*maxLevel);
    /*slist->items_per_level  = aligned_alloc(32,sizeof(uint64_t) * maxLevel);
  slist->starts_of_flanes = aligned_alloc(32,sizeof(uint64_t) * maxLevel);
  slist->flane_items      = aligned_alloc(32,sizeof(uint64_t) * maxLevel);*/

  
  /*for (uint8_t level = 0; level < maxLevel; ++level)
    {
      slist->flane_items[level] = 0;
    }
  */
  //calculateFastLaneSizes();
  //allocateFastLanes();

}


void CSSLSkipList::addElementToSkipList(uint64_t key)
{
  skipList.push_back(key);
}
