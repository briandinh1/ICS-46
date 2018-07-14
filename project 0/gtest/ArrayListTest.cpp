#include "ArrayList.hpp"
#include "OutOfBoundsException.hpp"
#include <gtest/gtest.h>


TEST(ArrayListTest, sizeIsZeroWhenConstructed)
{
  ArrayList<double> a;
  EXPECT_EQ(0, a.size());
}

TEST(ArrayListTest, exceptionThrownWhenRequestingAnIndexLargerThanSizeOrLessThanZero)
{
  ArrayList<float> a;
  EXPECT_THROW(a.at(98765), OutOfBoundsException);
  EXPECT_THROW(a.at(-1), OutOfBoundsException);
}


TEST(ArrayListTest, exceptionNotThrownWhenRequestingAnIndexSmallerThanSizeButLargerThanZero)
{
  ArrayList<char> a;
  for (int i = 0; i < a.capacity(); ++i) a.add(a.at(i));
  EXPECT_NO_THROW(a.at(0));
}

TEST(ArrayListTest, capacityIsIncreasedWhenAddingToAFullArray)
{
  ArrayList<int> a;
  for (int i = 0; i < a.capacity(); ++i) a.add(a.at(i));
  int newCap = a.capacity()*2+1;
  a.add(2000);
  EXPECT_EQ(newCap, a.capacity());
}

TEST(ArrayListTest, copyConstructorCopiesItemsPerfectly)
{
  ArrayList<int> a;
  for (int i = 0; i < a.capacity(); ++i) a.add(a.at(i));
  ArrayList<int> b(a);
  for (int i = 0; i < b.capacity(); ++i)
    EXPECT_EQ (a.at(i), b.at(i));
}
