#ifndef CSSLSKIPLISTDICTIONARY_H
#define CSSLSKIPLISTDICTIONARY_H

#include <stdint.h>
#include <vector>

class CSSLSkipListDictionary
{
 private:
    std::vector<uint64_t> itemsPerLevel;
    std::vector<uint64_t> startOfFastLane;
 public:
    void calculateFastLaneSize();
};

#endif /* CSSLSKIPLISTDICTIONARY_H  */
