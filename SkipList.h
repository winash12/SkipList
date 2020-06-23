#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <immintrin.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <memory>
#include <vector>

using std::unique_ptr;
using std::shared_ptr;
using std::vector;

#define MAX_SKIP 2
// initial size of the highest fast lane with number
// of keys that fit into one cache line
// The total size of cache line is 64 bytes or 512 bits
// We are using 64 bit integers hence 8 keys per cache line
#define TOP_LANE_BLOCK 8
// number of keys that can be stored in one SIMD register
#define SIMD_SEGMENTS 4
// data list node
struct _CSSL_DataNode
{
	uint64_t key;
	shared_ptr<_CSSL_DataNode> next;
};


// result of a range query
struct _CSSL_RangeSearchResult
{
	shared_ptr<_CSSL_DataNode> start;
	shared_ptr<_CSSL_DataNode> end;
	uint32_t        count;
};

struct _CSSL_ProxyNode
{
	uint64_t keys[MAX_SKIP];
	shared_ptr<_CSSL_DataNode> pointers[MAX_SKIP];
	bool updated;
};

class SkipList
{
 private:
	// proxy node
	
	struct _CSSL_SkipList
	{
		uint8_t                            max_level;
		uint8_t                            skip;
		uint32_t                           num_elements;
		uint32_t                           flane_size;
		uint64_t*                          items_per_level;
		uint64_t*                          flane_items;
		uint64_t*                          starts_of_flanes;
		uint64_t*                          flanes;
		//_CSSL_ProxyNode** flane_pointers;
		vector<shared_ptr<_CSSL_ProxyNode>> flane_pointers;
		shared_ptr<_CSSL_DataNode> head;
		shared_ptr<_CSSL_DataNode> tail;
	};
	shared_ptr<_CSSL_SkipList> slist;

 public:
	void printFastLanes();
	void createSkipList(uint8_t maxLevel,uint8_t skip);
	void insertElement(uint64_t key);
	_CSSL_DataNode *searchStartKey(uint64_t startKey);
	uint64_t searchElement(uint64_t key);
	_CSSL_RangeSearchResult searchRange(uint64_t startKey, uint64_t endKey);
 private:
	uint64_t   insertItemIntoFastLane(int8_t level,
						shared_ptr<_CSSL_DataNode> newNode);

	void      buildFastLanes();

	void     calculateFastLaneSizes();
	void     allocateFastLanes();
	void      resizeFastLanes();
	void findAndInsertIntoProxyNode(shared_ptr<_CSSL_DataNode> node);
	shared_ptr<_CSSL_DataNode> newNode(uint64_t key);
	shared_ptr<_CSSL_ProxyNode> newProxyNode(shared_ptr<_CSSL_DataNode> node);
};
