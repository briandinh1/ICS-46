// BSTSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// A BSTSet is an implementation of a Set that is a binary search tree,
// albeit one that makes no attempt to remain balanced.  (You explicitly
// should not do any balancing here; do that in AVLSet instead, if you
// choose to work on that one.)
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your binary search tree using your own dynamically-allocated
// nodes, with pointers connecting them.

#ifndef BSTSET_HPP
#define BSTSET_HPP

#include "Set.hpp"


template <typename T>
class BSTSet : public Set<T>
{
public:
  // Initializes a BSTSet to be empty.
  BSTSet();
  
  // Cleans up the BSTSet so that it leaks no memory.
  virtual ~BSTSet();
  
  // Initializes a new BSTSet to be a copy of an existing one.
  BSTSet(const BSTSet& s);
  
  // Assigns an existing BSTSet into another.
  BSTSet& operator=(const BSTSet& s);


  // isImplemented() should be modified to return true if you've
  // decided to implement a BSTSet, false otherwise.
  virtual bool isImplemented() const;
  
  
  // add() adds an element to the set.  If the element is already in the set,
  // this function has no effect.  This function runs in O(n) time when there
  // are n elements in the binary search tree, and is sometimes as fast as
  // O(log n) (when the tree is relatively balanced).
  virtual void add(const T& element);
  
  
  // contains() returns true if the given element is already in the set,
  // false otherwise.  This function runs in O(n) time when there
  // are n elements in the binary search tree, and is sometimes as fast as
  // O(log n) (when the tree is relatively balanced).
  virtual bool contains(const T& element) const;
  
  
  // size() returns the number of elements in the set.
  virtual unsigned int size() const;
  
  
private:
  struct Node
  {
    Node() : left(nullptr), right(nullptr) {}
    Node (T newKey, Node* newLeft = nullptr, Node* newRight = nullptr)
      : key(newKey), left(newLeft), right(newRight) {}
    T key;
    Node* left;
    Node* right;
  };

  Node* root;
  int treeSize;
  
  void destroyAll(Node* node);
  Node* copyAll(Node* node);
  Node* addNode(Node* node, const T& element);
  bool containsNode(Node* node, const T& element) const;
};


template <typename T>
BSTSet<T>::BSTSet()
  : root(nullptr), treeSize(0)
{
}


template <typename T>
BSTSet<T>::~BSTSet()
{
  destroyAll(root);
}


template <typename T>
BSTSet<T>::BSTSet(const BSTSet& s)
  : root(nullptr), treeSize(s.treeSize)
{
  root = copyAll(s.root);
}


template <typename T>
BSTSet<T>& BSTSet<T>::operator=(const BSTSet& s)
{
  if (this != &s)
    {
      destroyAll(root);
      root = copyAll(s.root);
      treeSize = s.treeSize;
    }
  
  return *this;
}


template <typename T>
bool BSTSet<T>::isImplemented() const
{
  return true;
}


template <typename T>
void BSTSet<T>::add(const T& element)
{
  root = addNode(root, element);
}
      
template <typename T>
bool BSTSet<T>::contains(const T& element) const
{
   return containsNode(root, element);
}

template <typename T>
unsigned int BSTSet<T>::size() const
{
    return treeSize;
}



// ==================================================================
// added helper functions

template <typename T>
void BSTSet<T>::destroyAll(Node* node)
{
  if (node)
    {
      destroyAll(node->left);
      destroyAll(node->right);
      delete node;
      node = nullptr;
    }
}

template <typename T>
typename BSTSet<T>::Node* BSTSet<T>::copyAll(Node* node)
{
  if (node == nullptr) return node;

  return new Node(node->key, copyAll(node->left), copyAll(node->right));
}

template<typename T>
typename BSTSet<T>::Node* BSTSet<T>::addNode(Node* node, const T& element)
{
  if (node == nullptr)
    {
      ++treeSize;
      return new Node(element);
    }
    
  if (element < node->key) node->left = addNode(node->left, element);
  if (element > node->key) node->right = addNode(node->right, element);
  
  return node;
}

template <typename T>
bool BSTSet<T>::containsNode(Node* node, const T& element) const
{
   if (node == nullptr) return false;
   if (element == node->key) return true;
   if (element < node->key) return containsNode(node->left, element);
   if (element > node->key) return containsNode(node->right, element);
}

 
#endif // BSTSET_HPP

