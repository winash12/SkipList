#include "CSSLSkipListDictionary.h"

void CSSLSkipListDictionary::calculateFastLaneSize(int fastLaneSize,int maxLevel,int skip)
{
  fastLaneSize = fastLaneSize;

  cout <<"The value of maxLevel is" << maxLevel << endl;
  itemsPerLevel.at(maxLevel)=fastLaneSize;
  itemsPerLevel.push_back(fastLaneSize);
  //startOfFastLane.at(maxLevel-1)=0;
  int current = fastLaneSize;
  // calculate level sizes level by level
  uint64_t value;
  for (int level = this->maxLevel - 2; level >= 0; level--)
    {
      current *= skip;
      cout << "The value of current is " <<current << endl;
      //itemsPerLevel.at(level) = current;
      //value = startOfFastLane.at(level+1) +itemsPerLevel.at(level+1);
      //cout << "The value of value is " << value << endl;
      //startOfFastLane.at(level)=value;
      //fastLaneSize += itemsPerLevel.at(level);
    }

}
