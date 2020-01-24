#include "CSSLProxyNode.h"

int CSSLProxyNode::getKey(int index)
{
  return keys[index];
}

CSSLDataNode CSSLProxyNode::getValue(int index)
{
  return values[index];
}
