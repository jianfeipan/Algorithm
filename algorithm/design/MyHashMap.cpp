

#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <vector>

using namespace std;

/*
own hash map
*/
template<class K, class V>
class HashNode
{
public:
   HashNode(const K & key, const V & value):key(key), value(value)
   {
   }

   HashNode(const K & key) :key(key), value()
   {
   }
   K key;
   V value;
};


template<class K, class V>
class MyHashMap
{
public:
   MyHashMap() :_capacity(100), _size(), _hash(), _data(_capacity) {}

   bool has(const K & key)
   {
      size_t index = _hash(key) % _capacity;
      auto it = find_if(_data[index].begin(), _data[index].end(), [&key](const auto & node) {
         return node.key == key;
      });

      return it != _data[index].end();
   }

   void erase(const K& key)
   {
      size_t index = _hash(key) % _capacity;
      auto it = find_if(_data[index].begin(), _data[index].end(), [&key](const auto & node) {
         return node.key == key;
      });

      if (it != _data[index].end())
      {
         _data[index].erase(it);
         --_size;
      }
   }

   V& operator[](const K & key)
   {
      size_t index = _hash(key) % _capacity;
      
      auto it = find_if(_data[index].begin(), _data[index].end(), [&key](const auto & node) {
         return node.key == key;
      });

      if(it == _data[index].end())
         it = _data[index].insert(_data[index].begin(), HashNode<K, V>(key));

      return it->value;
   }

   const V& operator[](const K & key) const
   {
      return this->operator[](key);
   }
private:
   size_t _capacity;
   size_t _size;//how to dynamicly expend the capacity
   hash<K> _hash;
   vector<list<HashNode<K, V>>> _data;
};

int main(int argc, char *argv[])
{

   MyHashMap<string, int> nums;
   nums["a"] = 1; cout << nums["a"] << endl;
   nums["a"] = 2; cout << nums["a"] << endl;
   nums["b"] = 6; cout << nums["b"] << endl;
   nums["v"] = 4; cout << nums["v"] << endl;




   return 0;
}
