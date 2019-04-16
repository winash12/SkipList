/*
 * Copyright 2017 Stefan Sprenger <sprengsz@informatik.hu-berlin.de>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <inttypes.h>
#include <sys/time.h>
#include <stdint.h>
#include "skiplist.h"


int main() {

  
  _CSSL_SkipList* slist = createSkipList(9, 5);

  _CSSL_RangeSearchResult result;
  _CSSL_DataNode* node;
  int key;
  
  for (uint64_t i = 0; i < 100000; i += 1000)
    {
      printf("Index  = %d\n", i);
      insertElement(slist, i);
    }

  uint64_t searchKey = 510;
  uint64_t skey = searchElement(slist,searchKey);

  result = searchRange(slist, 500, 2500);


  printf("Result = %d\n", result.count);
  node = result.start;
  printf("First = %d\n", result.start->key);
  //while (node != result.end)
  //  {
  //    node = node->next;
  //    printf("Key = %d\n", node->key);
  //  }
  //printf("Last = %d\n", result.end->key);

  exit(0);
  return 0;
}
