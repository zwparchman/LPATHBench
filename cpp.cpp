#include <ctime>
#include <vector>
#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <unordered_map>

using namespace std;
using namespace std::chrono;

#ifndef __clang__
#ifdef __GNUC__  
#if __GNUC__ < 5
#warning "some versions of g++ under 5.0 will make this program crash"
#warning "the December 21 2014 works as does clang."
#warning "additionally use of an optimizatoin level lower than  -O3 with g++ 5.0 may crash this program"
#endif
#endif
#endif

struct route{
  int dest, cost;
};

struct node {
  vector<route> neighbours;
};

vector<node> readPlaces(){
  ifstream text("agraph");
  int numNodes; text >> numNodes;
  vector<node> nodes(numNodes);
  int node, neighbour, cost;
  while (text >> node >> neighbour >> cost){
    nodes[node].neighbours.push_back(route{neighbour, cost});
  }
  return nodes;
}


template <int T>
struct getLongestPath_class{

  int nocache(const vector<node> &nodes, const int nodeID, bitset<T> visited){
    visited[nodeID] = true;
    int max=0;
    for(const route &neighbour: nodes[nodeID].neighbours){
      if (visited[neighbour.dest] == false){
        const int dist = neighbour.cost + nocache(nodes, neighbour.dest, visited);
        if (dist > max){
          max = dist;
        }
      }
    }
    return max;
  }

  unordered_map<  bitset<sizeof(const int) + T  > , const int> cmap;
  int cache (const vector<node> &nodes, const int nodeID, bitset<T> visited){

    long int set = visited.to_ulong();
    set = set << sizeof( const int );
    set += nodeID;
    const bitset<T + sizeof( const int ) > key ( set );

    {
      auto where = cmap.find( key );
      if( where != cmap.end() ){
        return where->second;
      }
    }

    visited[nodeID] = true;
    int max=0;
    for(const route &neighbour: nodes[nodeID].neighbours){
      if (visited[neighbour.dest] == false){
        const int dist = neighbour.cost + cache(nodes, neighbour.dest, visited);
        if (dist > max){
          max = dist;
        }
      }
    }
    cmap.emplace( key , max );
    return max;
  }
};  


int getLongestPath(const vector<node> &nodes) {
  size_t count = nodes.size();

  if (count <= 16) {
    getLongestPath_class<16> c;
    return c.cache(nodes, 0, bitset<16>());
  }  else if ( count <= 32 ){
    getLongestPath_class<32> c;
    return c.cache(nodes, 0, bitset<32>());
  } else if (count <= 256) {
    getLongestPath_class<256> c;
    return c.cache(nodes, 0, bitset<256>());
  } else if (count <= 4096) {
    getLongestPath_class<4096> c;
    return c.nocache(nodes, 0, bitset<4096>());
  } else if (count <= 65536) {
    getLongestPath_class<65536> c;
    return c.nocache(nodes, 0, bitset<65536>());
  } else if (count <= 1048576) {
    getLongestPath_class<1048576> c;
    return c.nocache(nodes, 0, bitset<1048576>());
  } else if (count <= 16777216) {
    getLongestPath_class<16777216> c;
    return c.nocache(nodes, 0, bitset<16777216>());
  } else {
    return -1;
  }
}

int main(int , char** ){
  auto nodes = readPlaces();
  auto start = high_resolution_clock::now();
  int len = getLongestPath(nodes);
  auto end = high_resolution_clock::now();
  auto duration = (int)(0.001 * duration_cast<microseconds>(end - start).count());
  cout << len << " LANGUAGE C++ " << duration << std::endl;
}
