void CSSLSkipListDictionary::calculateFastLaneSize()
{
  fastLaneSize = TOP_LANE_BLOCK;

  cout << "The value of fastLaneSize is " <<fastLaneSize << endl;

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
  exit(0);
  cout << "The start of fast lane is " <<itemsPerLevel.at(1) << endl;
  cout << "The start of fastLaneSize is " <<fastLaneSize << endl;
}
