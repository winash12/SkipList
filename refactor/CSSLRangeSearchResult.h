#include "CSSLDataNode.h"

class CSSLRangeSearchResult
{
 private:
  CSSLDataNode startNode;
  CSSLDataNode endNode;
  int count;
 public:
  CSSLDataNode getStart();
  CSSLDataNode getEnd();
  int getCount();
};
