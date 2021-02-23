#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

struct node
{
  int label;
  float dist;
};

class Heap
{
private:
  int parent(int i);
  int right(int i);
  int left(int i);
  void swap(int a, int b);
  void min_heapify(int i);

public:
  unordered_map<int, int> location;
  vector<node> H;
  Heap();
  void insert(node i);

  Heap::Heap()
  {
  }

  int Heap::parent(int i)
  {
    return (i - 1) / 2;
  }

  int Heap::right(int i)
  {
    return 2 * i + 2;
  }

  int Heap::left(int i)
  {
    return 2 * i + 1;
  }

  void Heap::swap(int i, int j)
  {
    node tmp = H[i];
    H[i] = H[j];
    location[H[i].label] = i;
    H[j] = tmp;
    location[H[j].label] = j;
  }

  void Heap::min_heapify(int i)
  {
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < H.size() && H[l].dist < H[i].dist)
      smallest = l;
    if (r < H.size() && H[r].dist < H[smallest].dist)
      smallest = r;
    if (smallest != i)
    {
      swap(i, smallest);
      min_heapify(smallest);
    }
  }

  void Heap::update(int label, float value)
  {
    int n = location[label];
    if (H[n].dist <= value)
    {
      return;
    }
    H[n].dist = value;
    while (n > 0 && (H[parent(n)].dist > H[n].dist))
    {
      swap(parent(n), n);
      n = parent(n);
    }
  }

  void Heap::insert(node i)
  {
    if (location.find(i.label) != location.end())
    {
      update(i.label, i.dist);
    }
    else
    {

      H.push_back(i);
      location[i.label] = get_size() - 1;
      int n = H.size() - 1;
      while (n > 0 && (H[parent(n)].dist > H[n].dist))
      {
        swap(parent(n), n);
        n = parent(n);
      }