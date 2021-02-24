#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>
#include <chrono>
#include "min_heap.h"
using namespace std;

float random_edge()
{
  return ((float)rand() / (RAND_MAX));
};

float distance(float coord1[], float coord2[], int dim)
{
  float square_dist = 0;
  for (int i = 0; i < dim; i++)
  {
    square_dist += (coord1[i] - coord2[i]) * (coord1[i] - coord2[i]);
  }
  return sqrt(square_dist);
};

// for "0" we don't need to store vertices, just generate edges
float prims0(int v)
{
  float min_dist = 0;
  float dist[v];
  bool S[v];
  Heap H;
  for (int i = 0; i < v; i++)
  {
    dist[i] = 5;
    S[i] = false;
  }
  dist[0] = 0;
  element s = {1, 0};
  H.insert(s);
  while (H.heap_size())
  {
    element p = H.extract_min();
    S[p.label - 1] = 1;
    for (int j = 1; j < v + 1; j++)
    {
      if (S[j - 1])
      {
        continue;
      }
      else
      {
        float x = random_edge();
        if (dist[j - 1] > x)
        {
          dist[j - 1] = x;
          element w = {j, x};
          H.insert(w);
        }
      }
    }
  }
  for (int i = 0; i < v; i++)
  {
    min_dist += dist[i];
  }
  return min_dist;
}

float primsnot0(int v, int dim)
{
  int S[v];
  float mindist = 0;
  float dist[v];
  float coordinates[v][dim];
  Heap H;
  for (int i = 0; i < v; i++)
  {
    S[i] = 0;
    dist[i] = 5;
    for (int j = 0; j < dim; j++)
    {
      coordinates[i][j] = random_edge();
    }
  }
  dist[0] = 0;
  element s = {1, 0};
  H.insert(s);
  while (H.heap_size())
  {
    element p = H.extract_min();
    S[p.label - 1] = 1;
    for (int j = 1; j < v + 1; j++)
    {
      if (S[j - 1])
      {
        continue;
      }
      else
      {
        float x = distance(coordinates[p.label], coordinates[j], dim);
        if (dist[j - 1] > x)
        {
          dist[j - 1] = x;
          element w = {j, x};
          H.insert(w);
        }
      }
    }
  }
  for (int i = 0; i < v; i++)
  {
    mindist += dist[i];
  }
  return mindist;
}

int main(int argc, char *argv[])
{
  srand(time(NULL));
  int flag = atoi(argv[1]);
  int numpoints = atoi(argv[2]);
  int numtrials = atoi(argv[3]);
  int dimension = atoi(argv[4]);
  float sum = 0;

  if (dimension == 1)
  {
    cout << "not possible";
    return 1;
  }

  for (int i = 0; i < numtrials; i++)
  {
    if (dimension == 0)
    {
      float p = prims0(numpoints);
      sum += p;
      cout << p << endl;
    }
    else
    {
      float p = primsnot0(numpoints, dimension);
      sum += p;
      cout << p << endl;
    }
  }

  cout << "| num_of_points: " << numpoints << " | dimensions: " << dimension << " | trials: " << numtrials << " | average " << sum / numtrials << " |" << endl;
}