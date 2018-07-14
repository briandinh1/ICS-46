// HashSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// A HashSet is an implementation of a Set that is a separately-chained
// hash table, implemented as a dynamically-allocated array of linked
// lists.  At any given time, the HashSet has a "size" indicating
// how many elements are stored within it, along with a "capacity"
// indicating the size of the array.
//
// As elements are added to the HashSet and the proportion of the HashSet's
// size to its capacity exceeds 0.8 (i.e., there are more than 80% as many
// elements as there are array cells), the HashSet should be resized so
// that it is twice as large as it was before.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::vector, std::list, or std::array).  Instead, you'll need
// to use a dynamically-allocated array and your own linked list
// implementation; the linked list doesn't have to be its own class,
// though you can do that, if you'd like.

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <functional>
#include "Set.hpp"



template <typename T>
class HashSet : public Set<T>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction 
    typedef std::function<unsigned int(const T&)> HashFunction;

public:
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    virtual ~HashSet();

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8.  In the case
    // where the array is resized, this function runs in linear time (with
    // respect to the number of elements, assuming a good hash function);
    // otherwise, it runs in constant time (again, assuming a good hash
    // function).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
  HashFunction hashFunction;


private:
  struct Node
  {
    Node() : next(nullptr) {}
    Node(T newKey, Node* next = nullptr)
      : key(newKey), next(next) {}
    T key;
    Node* next;
  };
  
  Node** array;
  int capacity;
  int arraySize;

  void resize();
  void destroyAll();
  void copyAll(const HashSet& s);
};


template <typename T>
HashSet<T>::HashSet(HashFunction hashFunction)
  : hashFunction{hashFunction}, array(new Node*[DEFAULT_CAPACITY])
  , capacity(DEFAULT_CAPACITY), arraySize(0)
{
  for (int i = 0; i < capacity; ++i) array[i] = nullptr;
}


template <typename T>
HashSet<T>::~HashSet()
{
  destroyAll();
}


template <typename T>
HashSet<T>::HashSet(const HashSet& s)
  : hashFunction{s.hashFunction}, array(new Node*[s.capacity])
  , capacity(s.capacity), arraySize(s.arraySize)
{
  copyAll(s);
}


template <typename T>
HashSet<T>& HashSet<T>::operator=(const HashSet& s)
{
    if (this != &s)
    {
      destroyAll();
      hashFunction = s.hashFunction;
      capacity = s.capacity;
      arraySize = s.arraySize;
      array = new Node*[s.capacity];
      copyAll(s);
    }
    
    return *this;
}


template <typename T>
bool HashSet<T>::isImplemented() const
{
  return true;
}


template <typename T>
void HashSet<T>::add(const T& element)
{
  if (!contains(element))
    {
      int index = hashFunction(element) % capacity;
      array[index] = new Node(element, array[index]);
      ++arraySize;
      float ratio = (float)arraySize / (float)capacity;
      if (ratio > 0.8) resize();
    }
}


template <typename T>
bool HashSet<T>::contains(const T& element) const
{
  int index = hashFunction(element) % capacity;
  Node* temp = array[index];
  while (temp)
    {
      if (temp->key == element) return true;
      temp = temp->next;
    }

  return false;
}


template <typename T>
unsigned int HashSet<T>::size() const
{
    return arraySize;
}



// ==========================================================
// added helper functions

template <typename T>
void HashSet<T>::resize()
{
  int newCapacity = capacity * 2;

  Node** newArray = new Node*[newCapacity];
  for (int i = 0; i < newCapacity; ++i) newArray[i] = nullptr;

  for (int i = 0; i < capacity; ++i)
    {
      Node* temp = array[i];
      while (temp)
        {
          int index = hashFunction(temp->key) % newCapacity;
          newArray[index] = new Node(temp->key, newArray[index]);
          temp = temp->next;
        }
    }

  destroyAll();
  capacity = newCapacity;
  array = newArray;
}

template <typename T>
void HashSet<T>::destroyAll()
{
  for (int i = 0; i < capacity; ++i)
    {
      Node* temp = array[i];
      while (temp)
        {
          Node* to_delete = temp;
          temp = temp->next;
          delete to_delete;
        }
    }

  delete[] array;
}

template <typename T>
void HashSet<T>::copyAll(const HashSet& s)
{ 
  for (int i = 0; i < capacity; ++i)
    {
      array[i] = nullptr;
      Node* temp = s.array[i];
      while (temp)
        {
          array[i] = new Node(temp->key, array[i]);
          temp = temp->next;
        }
    }
}



#endif // HASHSET_HPP

