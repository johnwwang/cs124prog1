#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <unistd.h>
#include <list>
using namespace std;

int flag;
int numpoints;
int numtrials;
int dimension;
float coordinates[4][262144]

    // generate random number between 0 and 1
    float
    randByN()
{
  return (float)rand() / RAND - MAX;
}

// distance formula
float calcRand(int dim, int index1, int index2)
{
  float sum = 0;
  for (int i = 0; i <= dim; i++)
  {
    sum += pow(abs(coordinates[i][index1] - coordinates[i][index2]), 2);
  }
  return sqrt(sum);
}

// creating heap
vector<float> heap;

// create mst and return minimum weight
float prim()
{
  srand(time(0))

  // populate coordinates array with 0s
  // populate coordiate array using randByN() function
  // keep edgeSum count
  // array of distances, visited, and onheap -- to keep track of
  // which vertices are pushed onto the heap

  // return edgeSum
}

// computes average weight
float average()
{
  float sum = 0;
  for (int i = 0; i < numtrials; i++)
  {
    float weight = prim();
    sum += weight;
  }
  return (float)weight / numtrials;
}

int main(int argc, char *argv[])
{
  srand(time(0));
  flag = std::stoi(argv[1]);
  numpoints = std::stoi(argv[2]);
  numtrials = std::stoi(argv[3]);
  dimension = std::stoi(argv[4]);
  printf("%d points, %d trials, dimension %d: %f\n", numpoints, numtrials, dimension, average());
}