// AVLSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your AVL tree using your own dynamically-allocated nodes,
// with pointers connecting them, and with your own balancing algorithms
// used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include "Set.hpp"
#include <algorithm>


template <typename T>
class AVLSet : public Set<T>
{
public:
    // Initializes an AVLSet to be empty.
    AVLSet();

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet();

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
  struct Node
  {
    Node() : left(nullptr), right(nullptr) {}
    Node(T newKey, Node* newLeft = nullptr, Node* newRight = nullptr)
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

  int height(Node* node);
  int balanceFactor(Node* node);
  Node* balancedTree(Node* node);
  Node* rotateLeft(Node* node);
  Node* rotateRight(Node* node);
  Node* rotateLeftRight(Node* node);
  Node* rotateRightLeft(Node* node);
};


template <typename T>
AVLSet<T>::AVLSet()
  : root(nullptr), treeSize(0)
{
}


template <typename T>
AVLSet<T>::~AVLSet()
{
  destroyAll(root);
}


template <typename T>
AVLSet<T>::AVLSet(const AVLSet& s)
  : root(nullptr), treeSize(s.treeSize)
{
  root = copyAll(s.root);
}


template <typename T>
AVLSet<T>& AVLSet<T>::operator=(const AVLSet& s)
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
bool AVLSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void AVLSet<T>::add(const T& element)
{
  root = addNode(root, element);
}

template <typename T>
bool AVLSet<T>::contains(const T& element) const
{
  return containsNode(root, element);
}


template <typename T>
unsigned int AVLSet<T>::size() const
{
    return treeSize;
}



// ==============================================================
// added helper functions

template <typename T>
void AVLSet<T>::destroyAll(Node* node)
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
typename AVLSet<T>::Node* AVLSet<T>::copyAll(Node* node)
{
  if (node == nullptr) return node;
  
  return new Node(node->key, copyAll(node->left), copyAll(node->right));
}

template <typename T>
typename AVLSet<T>::Node* AVLSet<T>::addNode(Node* node, const T& element)
{
  if (node == nullptr)
    {
      ++treeSize;
      return new Node(element);
    }

  if (element < node->key) node->left = addNode(node->left, element);
  if (element > node->key) node->right = addNode(node->right, element);
  
  return balancedTree(node);
}

template <typename T>
bool AVLSet<T>::containsNode(Node* node, const T& element) const
{
  if (node == nullptr) return false;
  if (element == node->key) return true;
  if (element < node->key) return containsNode(node->left, element);
  if (element > node->key) return containsNode(node->right, element);
}

template <typename T>
int AVLSet<T>::height(Node* node)
{
  return (node == nullptr)
    ? -1
    : 1 + std::max(height(node->left), height(node->right));
}

template <typename T>
int AVLSet<T>::balanceFactor(Node* node)
{
  return height(node->right) - height(node->left);
}

template <typename T>
typename AVLSet<T>::Node* AVLSet<T>::balancedTree(Node* node)
{
  int balance = balanceFactor(node);

  // right heavy
  if (balance >= 2)
    {
      int rightBalance = balanceFactor(node->right);
  
      if (rightBalance < 0)
        return rotateRightLeft(node);
      else
        return rotateLeft(node);
    }
  // left heavy
  else if (balance <= -2)
    {
      int leftBalance = balanceFactor(node->left);

      if (leftBalance > 0)
        return rotateLeftRight(node);
      else
        return rotateRight(node);
    }

  // balanced (-1,0,1)
  return node;
}

template <typename T>
typename AVLSet<T>::Node* AVLSet<T>::rotateLeft(Node* node)
{
  Node * temp = node->right;
  node->right = temp->left;
  temp->left = node;
  return temp;
}

template <typename T>
typename AVLSet<T>::Node* AVLSet<T>::rotateRight(Node* node)
{
  Node * temp = node->left;
  node->left = temp->right;
  temp->right = node;
  return temp;
}

template <typename T>
typename AVLSet<T>::Node* AVLSet<T>::rotateLeftRight(Node* node)
{
  node->left = rotateLeft(node->left);
  Node* temp = rotateRight(node);
  return temp;
}

template <typename T>
typename AVLSet<T>::Node* AVLSet<T>::rotateRightLeft(Node* node)
{
  node->right = rotateRight(node->right);
  Node* temp = rotateLeft(node);
  return temp;
} 
      

#endif // AVLSET_HPP

