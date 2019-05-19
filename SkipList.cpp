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
#include "SkipList.h"

using namespace std;

void SkipList::createSkipList(uint8_t maxLevel, uint8_t skip) {

  slist = std::make_shared<_CSSL_SkipList>(_CSSL_SkipList{});
  slist->max_level        = maxLevel;
  cout << slist->max_level  <<endl;
  slist->num_elements     = 0;
  slist->head = newNode(0);
  slist->tail             = slist->head;
  slist->skip             = skip > 1 ? skip : 2;
  slist->items_per_level  = (uint64_t*)malloc(sizeof(uint64_t) * maxLevel);
  slist->items_per_level  = (uint64_t*)malloc(sizeof(uint64_t)*maxLevel);
  //Array
  slist->starts_of_flanes = (uint64_t*)malloc(sizeof(uint64_t)*maxLevel);
  //Array
  slist->flane_items      =(uint64_t*)malloc(sizeof(uint64_t)*maxLevel);
    /*slist->items_per_level  = aligned_alloc(32,sizeof(uint64_t) * maxLevel);
  slist->starts_of_flanes = aligned_alloc(32,sizeof(uint64_t) * maxLevel);
  slist->flane_items      = aligned_alloc(32,sizeof(uint64_t) * maxLevel);*/

  
  for (uint8_t level = 0; level < maxLevel; ++level)
    {
      slist->flane_items[level] = 0;
    }

  calculateFastLaneSizes();
  allocateFastLanes();

  srand(0);

  //return slist;
}


void SkipList::calculateFastLaneSizes()
{
  uint64_t flane_size = TOP_LANE_BLOCK;

  cout << "The value of flane_size is " << flane_size << endl;
  
  slist->items_per_level[slist->max_level - 1]  = flane_size;
  slist->starts_of_flanes[slist->max_level - 1] = 0;
  

  int current = flane_size;
  // calculate level sizes level by level
  for (int8_t level = slist->max_level - 2; level >= 0; level--)
    {
      current = current * slist->skip;
      slist->items_per_level[level] = current;
      cout << slist->items_per_level[level] << endl;
      slist->starts_of_flanes[level] = slist->starts_of_flanes[level + 1 ] +
	slist->items_per_level[level + 1];
      flane_size += slist->items_per_level[level];
    }


  cout << "The value of flane_size is " << flane_size << endl;


  slist->flanes = (uint64_t*)malloc(sizeof(uint64_t) * flane_size);
  //slist->flanes = aligned_alloc(32,sizeof(uint64_t) * flane_size);
  //slist->flane_pointers = (_CSSL_ProxyNode**)malloc(sizeof(_CSSL_ProxyNode*) * slist->items_per_level[0]);
  //slist->flane_pointers(new _CSSL_ProxyNode[slist->items_per_level[0]]);
  slist->flane_pointers.reserve(slist->items_per_level[0]);
  cout << "The value of slist-->items_per_level[0]" << slist->items_per_level[0] << endl;
  //slist->flane_pointers = aligned_alloc(32,sizeof(_CSSL_ProxyNode*) * slist->items_per_level[0]);
  // initialize arrays with placeholder values
  slist->flane_size = flane_size;

}

void SkipList::allocateFastLanes()
{

  for (uint32_t i = 0; i < slist->flane_size; i++)
    slist->flanes[i] = LONG_MAX;
  for (uint32_t i = 0; i < slist->items_per_level[0]; i++)
    slist->flane_pointers[i] = nullptr; 
}

void SkipList::insertElement(uint64_t key)
{
  shared_ptr<_CSSL_DataNode> new_node = newNode(key);
  bool nodeInserted = true;
  bool flaneInserted = false;

  // add new node at the end of the data list
  slist->tail->next =  new_node;
  slist->tail = new_node;
  
  // add key to fast lanes
  for (uint8_t level = 0; level < slist->max_level; level++)
    {
      if (slist->num_elements % (uint64_t) pow(slist->skip, (level + 1)) == 0 &&
	  nodeInserted)
	{
	  nodeInserted = insertItemIntoFastLane(level, new_node);
 	}
      else
	break;
      flaneInserted = true;
    
    }



  if (!flaneInserted)
    {
      findAndInsertIntoProxyNode(new_node);
    }
  
  slist->num_elements++;

  //resize fast lanes if more space is needed
  if (slist->num_elements %
      (TOP_LANE_BLOCK*((uint64_t) pow(slist->skip, slist->max_level))) == 0)
    {
      resizeFastLanes();
    }
}


uint64_t SkipList::insertItemIntoFastLane(int8_t level,
					  shared_ptr<_CSSL_DataNode> newNode)
{
  uint64_t curPos = slist->starts_of_flanes[level] + slist->flane_items[level];
  //cout << "The value of curPos is " << curPos << endl;
  uint64_t levelLimit = curPos + slist->items_per_level[level];

  //cout << "The value of levelLimit is " << levelLimit << endl;

  if (curPos > levelLimit)
    curPos = levelLimit;

  while (newNode->key > slist->flanes[curPos] && curPos < levelLimit)
    curPos++;
  
  if (slist->flanes[curPos] == LONG_MAX)
    {
      slist->flanes[curPos] = newNode->key;
      if (level == 0)
	slist->flane_pointers[curPos - slist->starts_of_flanes[0]] =
	  newProxyNode(newNode);
      slist->flane_items[level]++;

      //cout << "The value of slist->flane_items[level] " << slist->flane_items[level] << endl;

    }
  else {
    return LONG_MAX;
  }
  //cout << "The value of curPos is " << curPos << endl;
  return curPos;
}

shared_ptr<_CSSL_ProxyNode> SkipList::newProxyNode(shared_ptr<_CSSL_DataNode> node) {

  // proxy(new _CSSL_ProxyNode());
   shared_ptr<_CSSL_ProxyNode> proxy = std::make_shared<_CSSL_ProxyNode>(_CSSL_ProxyNode{});
  //_CSSL_ProxyNode* proxy = aligned_alloc(32,sizeof(*proxy));
  proxy->keys[0] = node->key;
  proxy->updated = false;

  for (uint8_t i = 1; i < slist->skip; i++)
    {
      proxy->keys[i] = LONG_MAX;
      proxy->pointers[0] = node;
    }
  return proxy;
}


void SkipList::findAndInsertIntoProxyNode(shared_ptr<_CSSL_DataNode> node) {

  //cout << "The value of flane_items[0] in insert into ProxyNode" << slist->flane_items[0] << endl;
  shared_ptr<_CSSL_ProxyNode> proxy = (shared_ptr<_CSSL_ProxyNode>)slist->flane_pointers[slist->flane_items[0] - 1];

  for (uint8_t i = 1; i < slist->skip; i++)
    {
      if (proxy->keys[i] == LONG_MAX)
	{
	  proxy->keys[i] = node->key;
	  proxy->pointers[i] = node;
	  return;
	}
    }
}



/*void SkipList::printFastLanes()
{
  for (int i = 0;i < slist->flane_size;i++)
    {
      if (slist->flanes[i] != LONG_MAX)
	{
	  //cout << "The value of flane entry is " << slist->flanes[i]  << endl;
	}
    }

  _CSSL_DataNode* node;
  node = slist->head;
  while (node != slist->tail)
    {
      node = (_CSSL_DataNode*)node->next;
      cout << "THe value of key is " << node->key << endl;
    }
    }*/



// Increase size of existing fast lanes of a given skip list
void SkipList::resizeFastLanes() {
  //cout <<"Resizing fast lanes" << endl;
  uint32_t new_size = slist->items_per_level[slist->max_level - 1] +
                        TOP_LANE_BLOCK;
  uint64_t* level_items = (uint64_t*)malloc(sizeof(uint64_t) * slist->max_level);
  uint64_t* level_starts = (uint64_t*)malloc(sizeof(uint64_t) * slist->max_level);
  //uint64_t* level_items = aligned_alloc(32,sizeof(uint64_t) * slist->max_level);
  //uint64_t* level_starts = aligned_alloc(32,sizeof(uint64_t) * slist->max_level);
  vector<shared_ptr<_CSSL_ProxyNode>> new_fpointers;
  level_items[slist->max_level - 1]  = new_size;
  level_starts[slist->max_level - 1] = 0;

  for (int8_t level = slist->max_level - 2; level >= 0; level--) {
    level_items[level] = level_items[level + 1] * slist->skip;
    level_starts[level] = level_starts[level + 1] + level_items[level + 1];
    new_size += level_items[level];
  }

  uint64_t* new_flanes = (uint64_t*)malloc(sizeof(uint64_t) * new_size);
  new_fpointers.reserve(level_items[0]);
  //uint64_t* new_flanes = aligned_alloc(32,sizeof(uint64_t) * new_size);
  //_CSSL_ProxyNode** new_fpointers = aligned_alloc(32,sizeof(_CSSL_ProxyNode*) * level_items[0]);

  for (uint32_t i = slist->flane_items[slist->max_level - 1]; i < new_size; i++) {
    new_flanes[i] = LONG_MAX;
  }

  // copy from old flane to new flane
  for (int8_t level = slist->max_level - 1; level >= 0; level--)
    {
      memcpy(&new_flanes[level_starts[level]],
	     &slist->flanes[slist->starts_of_flanes[level]],
	     sizeof(uint64_t) * slist->items_per_level[level]);
    }
  //memcpy(&new_fpointers[0],
  //       &slist->flane_pointers[0],
  //       sizeof(_CSSL_ProxyNode*) * slist->items_per_level[0]);
  memcpy(&new_fpointers[0],
	 &slist->flane_pointers[0],
	 slist->flane_pointers.size());

  free(slist->flanes);
  //free(slist->flane_pointers);
  vector<shared_ptr<_CSSL_ProxyNode>>().swap(slist->flane_pointers);
  free(slist->items_per_level);
  free(slist->starts_of_flanes);
  slist->flanes = new_flanes;
  slist->flane_pointers = new_fpointers;
  slist->items_per_level = level_items;
  slist->starts_of_flanes = level_starts;
}
// Single-key lookup on a given skip list
uint64_t SkipList::searchElement(uint64_t key) {
  uint32_t curPos = 0;
  uint32_t first = 0;
  uint32_t last = slist->items_per_level[slist->max_level - 1] -1;
 
  uint32_t middle = 0;
  uint32_t rPos = 0;
  cout << "The value of is " << slist->max_level - 1<<endl;
  cout << "The value of last is " <<last <<endl;
  
  // scan highest fast lane with binary search
  middle = (first + last) / 2;
  while (first < last)
    {

      if (slist->flanes[middle] < key)
	{
	  first = middle + 1;
	}
      else if (slist->flanes[middle] == key)
	{
	  cout << "The search found at " << middle << endl;
	  curPos = middle;
	  break;
	}
      else
	{
	  last = middle;
	}
      middle = (first + last) / 2;
      cout << "The value of middle is " <<middle <<endl;
    }
  cout << "The value of first is " << first <<endl;
  cout << "The value of last is " << last <<endl;
  if (first > last)
    curPos = last;
  cout << "The value of curPos is " <<curPos <<endl;

  int level;
  // traverse over fast lanes
  for (level = slist->max_level - 1; level >= 0; level--)
    {
      rPos = curPos - slist->starts_of_flanes[level];
      //cout << "The value of rPos is " <<slist->starts_of_flanes[level] <<endl;
      while (rPos < slist->items_per_level[level] &&
	     key >= slist->flanes[++curPos])
	{
	  //cout << "The value of rPos is " << rPos<< endl;
	  rPos++;
	}
      if (level == 0) break;
      curPos  = slist->starts_of_flanes[level - 1] + rPos * slist->skip;
    }
  if (key == slist->flanes[--curPos])
    {
      return key;
    }
  cout << "The value of curPos is " <<curPos <<endl;
  cout << "The value of start of flanes[0]" << slist->starts_of_flanes[0] << endl;
  shared_ptr<_CSSL_ProxyNode> proxy = slist->flane_pointers[curPos - slist->starts_of_flanes[0]];
  for (uint8_t i = 1; i < slist->skip; i++) {
    if (proxy->keys[i] == key)
      return key;
  }

    
  return LONG_MAX;
}



_CSSL_RangeSearchResult SkipList::searchRange(uint64_t startKey, uint64_t endKey) {
  __m256d avx_creg, res, avx_sreg;
  _CSSL_RangeSearchResult result;
  int level, bitmask;
  uint32_t rPos = 0;
  uint32_t curPos = 0;

  uint32_t first = 0;
  uint32_t last = slist->items_per_level[slist->max_level - 1] - 1;
  uint32_t middle = 0;
  // scan highest fast lane with binary search
  while (first < last) {
    middle = (first + last) / 2;
    if (slist->flanes[middle] < startKey) {
      first = middle + 1;
    } else if (slist->flanes[middle] == startKey) {
      curPos = middle;
      break;
    } else {
      last = middle;
    }
  }
  if (first > last)
    curPos = last;

  for (level = slist->max_level - 1; level >= 0; level--) {
    rPos = curPos - slist->starts_of_flanes[level];
    while (rPos < slist->items_per_level[level] &&
           startKey >= slist->flanes[++curPos]) {
      rPos++;
    }
    if (level == 0) break;
    curPos  = slist->starts_of_flanes[level - 1] + rPos * slist->skip;
  }
  uint32_t start_of_flane = slist->starts_of_flanes[0];
  while (startKey < slist->flanes[curPos] && curPos > start_of_flane) {
    curPos--;
  }
  result.count = 0;
  
  

  cout << "the start value is " << result.start->key << endl;

  // search for the range's last matching node
  avx_sreg = _mm256_castsi256_pd(_mm256_set1_epi64x(endKey));
  alignas(32) uint64_t v[4]; 
  _mm256_store_pd((double*)v, avx_sreg);
  printf("v2_u64: %lld %lld %lld %lld\n", v[0], v[1],v[2],v[3]);

  
  uint32_t itemsInFlane = slist->items_per_level[0] - SIMD_SEGMENTS;

  rPos = curPos-slist->starts_of_flanes[0];
  cout <<"rPos is  " <<rPos << endl;
			       
			       
  cout <<"Items in Fast Lane" << itemsInFlane << endl;
  cout << "The current value of curPos " << curPos << endl;
  while (rPos < itemsInFlane) {
    avx_creg = _mm256_castsi256_pd(
        _mm256_loadu_si256((__m256i const *) &slist->flanes[curPos]));
    //
    alignas(32) uint64_t v[4]; 
    _mm256_store_pd((double*)v, avx_creg);
    printf("v2_u64: %lld %lld %lld %lld\n", v[0], v[1],v[2],v[3]);
    //
    res      = _mm256_cmp_pd(avx_sreg, avx_creg, 30);
    bitmask  = _mm256_movemask_pd(res);
    int mmask = __builtin_popcount(bitmask);

    if (bitmask < 0x0f)
      {
	break;
      }
    curPos += SIMD_SEGMENTS; rPos += SIMD_SEGMENTS;
    result.count += (SIMD_SEGMENTS *  slist->skip);
  }

  curPos--;
						
  if (rPos > 0)
    {
      rPos--;
    }
  itemsInFlane += SIMD_SEGMENTS;
  
  while (endKey >= slist->flanes[++curPos] && rPos < itemsInFlane) {
    rPos++;
  }
  cout << "The value of rPos is " << rPos <<  endl;
  shared_ptr<_CSSL_ProxyNode> proxy = slist->flane_pointers[curPos - slist->starts_of_flanes[0]];
  if (rPos > 0 && rPos <  slist->items_per_level[0])
    {
      proxy = slist->flane_pointers[rPos];
      result.end = proxy->pointers[slist->skip - 1];
      cout << "The count is " << result.count << endl;
      for (uint8_t i = 1; i < slist->skip; i++)
	{
	  if (endKey < proxy->keys[i]) {
	    result.end = proxy->pointers[i - 1];
	    break;
	  }
	}
      
    }
  exit(0);

  return result;
}

// Creates a new node
shared_ptr<_CSSL_DataNode> SkipList::newNode(uint64_t key)
{
  //shared_ptr<_CSSL_DataNode> node(new _CSSL_DataNode());
  shared_ptr<_CSSL_DataNode> node = std::make_shared<_CSSL_DataNode>(_CSSL_DataNode{});
  //_CSSL_DataNode* node = aligned_alloc(32,sizeof(*node));
  node->key  = key;
  node->next = NULL;

  return node;
}
