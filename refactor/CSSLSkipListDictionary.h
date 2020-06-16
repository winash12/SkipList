#ifndef CSSLSKIPLISTDICTIONARY_H
#define CSSLSKIPLISTDICTIONARY_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include <vector>

using std::cout;
using std::endl;

class CSSLSkipListDictionary
{
 private:
  int fastLaneSize;
  int maxLevel;
  int skip;
  std::vector<uint64_t> itemsPerLevel;
  std::vector<uint64_t> startOfFastLane;
 public:
  void calculateFastLaneSize(int fastLaneSize,int maxLevel,int skip);
};

#endif /* CSSLSKIPLISTDICTIONARY_H  */
