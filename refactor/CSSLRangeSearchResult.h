#include "CSSLDataNode.h"

class CSSLRangeSearchResult
{
 private:
  CSSLDataNode startNode;
  CSSLDataNode endNode;
  int count =0;
 public:
  CSSLDataNode getStart();
  CSSLDataNode getEnd();
  int getCount();
};
