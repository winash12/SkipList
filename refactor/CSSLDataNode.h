#include <stdint.h>

class CSSLDataNode
{
 private:
  uint64_t key;
 public:
  void setKey(uint64_t key);
  uint64_t getKey();
};
