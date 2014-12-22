#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

struct route{
  int dest, cost;
};

struct node {
  vector<route> neighbours;
};

int main( int argc , char * argv [] ){
  int verticies = 20;

  if( argc == 2 ){
    verticies = atoi( argv[1] );
  }



  int maxDist = 1000;

  vector< node  > graph;
  graph.reserve( verticies );

  //generate a fully connected graph with random weights
  for( int i=0; i < verticies ; i ++ ){
    node n;
    for( int j=0; j < verticies ; j ++ ){
      n.neighbours.push_back( { j , rand()%maxDist } );
    }
    graph.push_back( n );
  }

  cout<<graph.size()<<endl;
  for( size_t i=0; i < graph.size() ; i ++ ){
    const auto &n = graph[i];
    for( const auto &r : n.neighbours ){
      cout<<i<<" "<<r.dest<<" "<<r.cost<<endl;
    }
  }

  return 0;
}
