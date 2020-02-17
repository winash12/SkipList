#include <stdint.h>
#include <vector>

#include "CSSLDataNode.h"

class CSSLProxyNode
{
 private:
  std::vector<int> keys;
  std::vector<CSSLDataNode> values;
 public:
  int getKey(int index);
  CSSLDataNode getValue(int index);
};
