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
  int maxLevel;
  int skip;
  uint64_t fastLaneSize;
  std::vector<uint64_t> skipList;
  std::vector<uint64_t> itemsPerLevel;
  std::vector<uint64_t> startOfFastLane;
  std::vector<uint64_t> fastLaneItems;
  std::vector<uint64_t> fastLanePointers;
  std::vector<uint64_t> fastLanes;    

  uint8_t numberOfElements;

  void      buildFastLanes();
  void calculateFastLaneSize();
  void allocateFastLanes();


  void   insertItemIntoFastLane(int level,
				uint64_t key);  
  void addElementToSkipList(uint64_t key);
  
 public:
  void createSkipList(int maxLevel,int skip);
  void insertElement(uint64_t key);

  uint64_t searchElement(uint64_t key);

  std::vector<uint64_t> searchRange(uint64_t startKey, uint64_t endKey);

};
