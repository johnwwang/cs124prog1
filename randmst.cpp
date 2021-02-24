#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>
#include <chrono>
#include "minheap.h"
using namespace std;

float random_edge()
{
  return ((float)rand() / (RAND_MAX));
};

float distance(float coord1[], float coord2[], int d)
{
  float square_dist = 0;
  for (int i = 0; i < d; i++)
  {
    square_dist += (coord1[i] - coord2[i]) * (coord1[i] - coord2[i]);
  }
  return sqrt(square_dist);
};

// for "0" we don't need to store vertices, just generate edges
float prims0(int v, int d)
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
  H.insert({1, 0});
  while (H.heap_size())
  {
    S[H.extract_min().label - 1] = true;
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
          H.insert({j, x});
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

float primsnot0(int v, int d)
{
  int S[v];
  float coords[v][d];
  float mindist = 0;
  float dist[v];
  Heap H;
  for (int i = 0; i < v; i++)
  {
    S[i] = 0;
    dist[i] = 5;
    for (int j = 0; j < d; j++)
    {
      coords[i][j] = random_edge();
    }
  }
  dist[0] = 0;
  H.insert({1, 0});
  while (H.heap_size())
  {
    element tmp = H.extract_min();
    S[tmp.label - 1] = 1;
    for (int j = 1; j < v + 1; j++)
    {
      if (S[j - 1])
      {
        continue;
      }
      else
      {
        float x = distance(coords[tmp.label], coords[j], d);
        dist[j - 1] = min(x, dist[j - 1]);
        H.insert({j, x});
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

  if (dimension == 1 || dimension < 0)
  {
    cout << "not possible";
    return 1;
  }

  for (int i = 0; i < numtrials; i++)
  {
    if (dimension == 0)
    {
      auto start = std::chrono::high_resolution_clock::now();
      float p = prims0(numpoints, dimension);
      auto finish = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> elapsed = finish - start;
      sum += p;
      cout << p << endl;
      cout << elapsed.count() << endl;
    }
    else
    {
      auto start = std::chrono::high_resolution_clock::now();
      float p = primsnot0(numpoints, dimension);
      auto finish = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> elapsed = finish - start;
      sum += p;
      cout << p << endl;
      cout << elapsed.count() << endl;
    }
  }

  cout << "| num_of_points: " << numpoints << " | dimensions: " << dimension << " | trials: " << numtrials << " | average " << sum / numtrials << " |" << endl;
}