cimport cython
import numpy as np
import sys
cimport numpy as np
import ctypes

cdef extern from "stdint.h":
    ctypedef unsigned long long uint64_t
    ctypedef unsigned char uint8_t
    
cdef extern from "geohash.h":
    ctypedef enum GeoDirection:
        GEOHASH_NORTH = 0,
        GEOHASH_EAST,
        GEOHASH_WEST,
        GEOHASH_SOUTH,
        GEOHASH_SOUTH_WEST,
        GEOHASH_SOUTH_EAST,
        GEOHASH_NORT_WEST,
        GEOHASH_NORT_EAST

    ctypedef struct GeoHashBits:
            uint64_t bits;
            uint8_t step;

    ctypedef struct GeoHashRange:
            double max;
            double min;
    ctypedef struct GeoHashArea:
            GeoHashBits hash;
            GeoHashRange latitude;
            GeoHashRange longitude;

    ctypedef struct GeoHashNeighbors:
            GeoHashBits north;
            GeoHashBits east;
            GeoHashBits west;
            GeoHashBits south;
            GeoHashBits north_east;
            GeoHashBits south_east;
            GeoHashBits north_west;
            GeoHashBits south_west;

    int geohash_encode(GeoHashRange lat_range, GeoHashRange lon_range, double latitude, double longitude, uint8_t step, GeoHashBits* hash);
    int geohash_decode(GeoHashRange lat_range, GeoHashRange lon_range, GeoHashBits hash, GeoHashArea* area);

    int geohash_get_neighbors(GeoHashBits hash, GeoHashNeighbors* neighbors);
    int geohash_get_neighbor(GeoHashBits hash, GeoDirection direction, GeoHashBits* neighbor);

    int geohash_fast_encode(GeoHashRange lat_range, GeoHashRange lon_range, double latitude, double longitude, uint8_t step, GeoHashBits* hash);
    int geohash_fast_decode(GeoHashRange lat_range, GeoHashRange lon_range, GeoHashBits hash, GeoHashArea* area);

    
    GeoHashBits geohash_next_leftbottom(GeoHashBits bits);
    GeoHashBits geohash_next_rightbottom(GeoHashBits bits);
    GeoHashBits geohash_next_lefttop(GeoHashBits bits);
    GeoHashBits geohash_next_righttop(GeoHashBits bits);




class GeoHash:
    

    def encode(self,np.float64_t longitude,np.float64_t latitude,np.uint8_t precision):
        cdef GeoHashBits hash
        cdef GeoHashNeighbors neighbors
        cdef GeoHashRange lat_range, lon_range
        lat_range.max = 90.0
        lat_range.min = -90.0
        lon_range.max = 180.0
        lon_range.min = -180.0
        geohash_encode(lat_range, lon_range, latitude, longitude, precision, &hash);
        return hash.bits

    def fast_encode(self,np.float64_t longitude,np.float64_t latitude,np.uint8_t precision):

        cdef GeoHashBits hash
        cdef GeoHashNeighbors neighbors
        cdef GeoHashRange lat_range, lon_range
        lat_range.max = 90.0
        lat_range.min = -90.0
        lon_range.max = 180.0
        lon_range.min = -180.0

        geohash_fast_encode(lat_range, lon_range, latitude, longitude, precision, &hash);
        return hash
    
    def decode(self,hashBits):
        cdef GeoHashRange lat_range, lon_range
        cdef GeoHashArea area
        lat_range.max = 90.0
        lat_range.min = -90.0
        lon_range.max = 180.0
        lon_range.min = -180.0
        geohash_decode(lat_range,lon_range,hashBits,&area)
        return area.longitude,area.latitude

    def get_neighbors(self,hash):
        cdef GeoHashNeighbors neighbors
        geohash_get_neighbors(hash,&neighbors)
        return neighbors
    
    def calculateGeoHash(self):

        cdef GeoHashBits hash, fast_hash
        cdef GeoHashNeighbors neighbors
        cdef GeoHashRange lat_range, lon_range
        lat_range.max = 90.0
        lat_range.min = -90.0
        lon_range.max = 180.0
        lon_range.min = -180.0
        
        cdef double latitude = 12.34
        cdef double longitude = 56.78
        
        for step in range(33):
            geohash_encode(lat_range, lon_range, latitude, longitude, step, &hash);
            geohash_fast_encode(lat_range, lon_range, latitude, longitude, step, &fast_hash);
            print("normal encode (%d): %llu\n", step, hash.bits);
        
            print("fast encode   (%d): %llu\n", step, fast_hash.bits);
            print("%lld\n", hash.bits);
            geohash_get_neighbors(hash,&neighbors)
            print("%lld\n", neighbors.east.bits);
            print("%lld\n", neighbors.west.bits);
            print("%lld\n", neighbors.south.bits);
            print("%lld\n", neighbors.north.bits);
            print("%lld\n", neighbors.north_west.bits);
            print("%lld\n", neighbors.north_east.bits);
            print("%lld\n", neighbors.south_east.bits);
            print("%lld\n", neighbors.south_west.bits);

            print("\n");

    def defineRangeIndex(self):
        rangeIndex = [
            0.6, # 52
            1, #50
            2.19, # 48
            4.57, # 46
            9.34, # 44
            14.4, # 42
            33.18, # 40
            62.1, # 38
            128.55, # 36
            252.9, # 34
            510.02, # 32
            1015.8, # 30
            2236.5, # 28
            3866.9, # 26
            8749.7, # 24
            15664, # 22
            33163.5, # 20
            72226.3, # 18
            150350, # 16
            306600, # 14
            474640, # 12
            1099600, # 10
            2349600, # 8
            4849600, # 6
            10018863 # 4
            ]
        return rangeIndex

            
