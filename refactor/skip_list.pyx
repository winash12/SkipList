cimport cython
import numpy as np
import array
import sys
cimport numpy as np
import ctypes
from libc.stdint cimport (int8_t)
from libc.stdlib cimport malloc,free
from cpython.mem cimport PyMem_Malloc,PyMem_Free

cdef extern from "stdint.h":
    ctypedef unsigned int uint32_t
    ctypedef unsigned long long uint64_t
    ctypedef unsigned char uint8_t
    ctypedef bint updated
    
cdef extern from "skiplist.h":
    ctypedef struct _CSSL_DataNode:
            uint64_t key;
            _CSSL_DataNode* next;
    ctypedef struct _CSSL_ProxyNode:
            uint64_t keys[5];
            _CSSL_DataNode* pointers[5];
            bint updated;
    ctypedef struct _CSSL_SkipList:
            uint8_t max_level;
            uint8_t           skip;
            uint32_t          num_elements;
            uint64_t*         items_per_level;
            uint64_t*         flane_items;
            uint64_t*         starts_of_flanes;
            uint64_t*         flanes;
            _CSSL_ProxyNode** flane_pointers;
            _CSSL_DataNode    *head;
            _CSSL_DataNode    *tail;

    ctypedef struct  _CSSL_RangeSearchResult:
            _CSSL_DataNode* start;
            _CSSL_DataNode* end;
            uint32_t        count;


    _CSSL_SkipList*         createSkipList(uint8_t maxLevel, uint8_t skip);
    void                    insertElement(_CSSL_SkipList* slist, uint64_t key);
    uint64_t                insertItemIntoFastLane(_CSSL_SkipList* slist,
                                               int8_t level,
                                               _CSSL_DataNode* newNode);
    uint64_t                searchElement(_CSSL_SkipList* slist, uint64_t key);
    _CSSL_RangeSearchResult searchRange(_CSSL_SkipList* slist, uint64_t startKey, uint64_t endKey);


cdef class Skip_List:

   cdef:
      _CSSL_SkipList* slist
    
   def __cinit__(self):

       self.slist = createSkipList(9, 5)
       if self.slist == NULL:
           raise MemoryError()


   def insertElement(self,np.uint64_t key): 
       insertElement(self.slist,key);

   def searchElement(self,np.uint64_t key):
       cdef np.uint64_t returnKey;
       returnKey = searchElement(self.slist,key)
       return returnKey

   def searchRange(self,np.uint64_t startKey,np.uint64_t endKey):
       cdef _CSSL_RangeSearchResult rangeSearchResult
       cdef _CSSL_DataNode* node
       cdef np.uint64_t sKey,rangeKey
       cdef int count
       rangeSearchResult = searchRange(self.slist, startKey, endKey);
       node = rangeSearchResult.start
       sKey = node.key
       rangeItems = []
       count = 0
       rangeItems.append(sKey)
       while (node != rangeSearchResult.end):
           node = node.next
           rangeItems.append(node.key)
           count += 1
       rangeArray = np.array(rangeItems)
       return rangeArray

   def __dealloc__(self):
      if self.slist != NULL:
          print("freeing skip list")
          free(self.slist)
