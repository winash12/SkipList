#pragma once

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
#include <iterator>
#include <vector>
#include <deque>


#define MAX_SKIP 2
// initial size of the highest fast lane with number
// of keys that fit into one cache line
// The total size of cache line is 64 bytes or 512 bits
// We are using 64 bit integers hence 8 keys per cache line
#define TOP_LANE_BLOCK 8
// number of keys that can be stored in one SIMD register
#define SIMD_SEGMENTS 4
// data list node

using std::vector;

class CSSLSkipList {
private:
	int maxLevel;
	int skip;
	int initialFastLaneSize;
	int fastLaneSize;
	std::unique_ptr<std::vector<uint64_t>> skipList = std::make_unique<std::vector<uint64_t>>();
	std::unique_ptr<std::deque<int>> itemsPerLevel = std::make_unique<std::deque<int>>();
	std::unique_ptr<std::deque<int>> startOfFastLane = std::make_unique<std::deque<int>>();

	std::unique_ptr<std::deque<int>> fastLaneItems = std::make_unique<std::deque<int>>();
	std::unique_ptr<std::vector<uint64_t>> fastLanes = std::make_unique<std::vector<uint64_t>>();

	uint32_t numberOfElements = 0;

	void buildFastLanes();
	void calculateFastLaneSize();
	void allocateFastLanes();

	void insertItemIntoFastLane(int level,
															uint64_t key);
	void addElementToSkipList(uint64_t key);

public:
	CSSLSkipList(int maxLevel, int skip, int fastLaneSize);

	void createSkipList(int maxLevel, int skip);

	void insertItemsIntoFastLanes(vector<uint64_t> inputData);
	
	uint64_t searchElement(uint64_t key);

	std::vector<uint64_t> searchRange(uint64_t startKey, uint64_t endKey);
};
