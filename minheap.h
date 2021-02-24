#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

struct element
{
  int label;
  float d;
};

class Heap

{
private:
  //allows us to find index of label in O(1) time, increases speed
  unordered_map<int, int> label_map;
  //vector, so we have dynamic space
  vector<element> arr;

  int parent(int i)
  {
    return (i - 1) / 2;
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
    element tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
    label_map[arr[i].label] = i;
    label_map[arr[j].label] = j;
  };

  //min_heapify as referred to in section video
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
  void insert(element i)
  {
    //insert as in section
    if (label_map.find(i.label) == label_map.end())
    {
      arr.push_back(i);
      label_map[i.label] = heap_size() - 1;
      int n = arr.size() - 1;
      while (n > 0 && (arr[n].d < arr[parent(n)].d))
      {
        swap(parent(n), n);
        n = parent(n);
      }
    }
    //else we need to update
    else
    {
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
  //build_heap, won't use it in our prims
  void build_heap(vector<int> A){};
  int heap_size()
  {
    return arr.size();
  }
};
