#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <immintrin.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <memory>
#include <vector>
#include <array>

#include "CSSLRangeSearchResult.h"
#include "CSSLProxyNode.h"

using std::unique_ptr;
using std::shared_ptr;

#define MAX_SKIP 2
// initial size of the highest fast lane with number
// of keys that fit into one cache line
// The total size of cache line is 64 bytes or 512 bits
// We are using 64 bit integers hence 8 keys per cache line
#define TOP_LANE_BLOCK 8
// number of keys that can be stored in one SIMD register
#define SIMD_SEGMENTS 4
// data list node


class CSSLSkipList
{
 private:
  uint8_t maxLevel;
  int skip;
  uint64_t fastLaneSize;
  std::vector<uint64_t> skipList;
  std::vector<uint64_t> itemsPerLevel;
  std::vector<uint64_t> startOfFastLane;
  std::vector<uint64_t> fastLaneItems;
  std::vector<uint64_t> fastLanePointers;
  std::vector<uint64_t>::iterator itr;
  std::vector<uint64_t>::iterator itr2;
  std::vector<uint64_t>::iterator itr3;
  std::vector<uint64_t> fastLanes;    
  std::vector<uint64_t> fastLaneProxyNodes;
  uint8_t numberOfElements;

  void      buildFastLanes();
  void calculateFastLaneSize();
  void allocateFastLanes();
  void findAndInsertIntoProxyNode(shared_ptr<CSSLDataNode> node);  
  shared_ptr<CSSLProxyNode> newProxyNode(shared_ptr<CSSLDataNode> node);
  void   insertItemIntoFastLane(int8_t level,
				uint64_t key);  
 public:
  void createSkipList(uint8_t maxLevel,int skip);
  void insertElement(uint64_t key);
  CSSLDataNode searchStartKey(uint64_t startKey);
  uint64_t searchElement(uint64_t key);
  CSSLRangeSearchResult searchRange(uint64_t startKey, uint64_t endKey);

  void addElementToSkipList(uint64_t key);



};
