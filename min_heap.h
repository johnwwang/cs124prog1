#include <vector>
#include <iostream>
#include <math.h>
#include <unordered_map>
using namespace std;

//vertex
struct element
{
  int label;
  float d;
};

class Heap

{
private:
  //time for space
  unordered_map<int, int> label_map;
  vector<element> arr;

  int parent(int i)
  {
    return floor(i / 2);
  };

  int left(int i)
  {
    return 2 * i + 1;
  };

  int right(int i)
  {
    return 2 * i + 2;
  };
  //used in min_heapify
  void swap(int i, int j)
  {
    element temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    label_map[arr[i].label] = i;
    label_map[arr[j].label] = j;
  };

  void min_heapify(int i)
  {
    int l = left(i);
    int r = right(i);
    int n = arr.size();
    int smallest = i;
    if (l < n && arr[i].d > arr[l].d)
      smallest = l;
    if (r < n && arr[smallest].d > arr[r].d)
      smallest = r;
    if (smallest != i)
    {
      swap(i, smallest);
      min_heapify(smallest);
    }
  };

public:
  int heap_size()
  {
    return arr.size();
  }
  void insert(element i)
  {
    if (label_map.find(i.label) == label_map.end())
    {
      //insert
      arr.push_back(i);
      label_map[i.label] = heap_size() - 1;
      int n = arr.size() - 1;
      while (n > 0 && (arr[n].d < arr[parent(n)].d))
      {
        swap(parent(n), n);
        n = parent(n);
      }
    }
    else
    {
      //insert i is already in heap
      int index = label_map[i.label];
      if (arr[index].d > i.d)
      {
        arr[index].d = i.d;
        while (index > 0 && (arr[parent(index)].d > arr[index].d))
        {
          swap(parent(index), index);
          index = parent(index);
        }
      }
    }
  };

  element extract_min()
  {
    //implemented like in section
    if (heap_size() != 0)
    {
      element min = arr[0];
      label_map.erase(min.label);
      swap(0, heap_size() - 1);
      arr.pop_back();
      min_heapify(0);
      return min;
    }
    else
    {
      return {0, 0};
    };
  };
  void build_heap(vector<int> A){};
};
