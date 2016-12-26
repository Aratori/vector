#include <gtest/gtest.h>
#include "MyVector.cpp"
#include <iostream>



MyVector<int> nVector(30, 0);
int primeN = 30;
int count = 5;

class VectorTest : public ::testing::Test {
 protected:
  virtual void SetUp()
{
  }

  virtual void TearDown()
{
  }
};

TEST(VectorTest, PrimeTest)
{
    //std::vector<int> primeVector(primeN, count);//primeN == 30
    //std::vector<int>::iterator it = primeVector.begin();
    //std::vector<int> notPrimeVector(primeN, 0);
    MyVector<int> primeVector(primeN, count);
    MyVector<int> notPrimeVector(primeN, 0);
    MyVector<int>::Iterator it = primeVector.begin();
    unsigned int n;

    ASSERT_TRUE(*it == count);//begin()

    for(n = 0; it != primeVector.end(); n++, it++)//end()
        ;

    ASSERT_TRUE(n == primeN);

    //std::vector<int>::reverse_iterator rIt = primeVector.rbegin();
    MyVector<int>::ReverseIterator rIt = primeVector.rbegin();

    ASSERT_TRUE(*rIt == count);//rbegin()

    for(n = 0; rIt != primeVector.rend(); n++, rIt++)//rend()
        ;

    ASSERT_TRUE(n == primeN);

    ASSERT_TRUE(primeVector.size() == primeN);

    primeVector.resize(primeN/2);

    ASSERT_EQ(primeVector.size(), primeN/2);

    primeVector.resize(primeN, count*2);//resize(num,val)

    ASSERT_EQ(primeVector.back(), count*2);//back()
    ASSERT_EQ(primeVector.front(), count);//front()

    primeVector.resize(0);

    ASSERT_TRUE(primeVector.empty());//empty()

    primeVector.reserve(primeN*2);//reserve()

    ASSERT_EQ(primeVector.capacity(), primeN*2);//capacity()

    primeVector.reserve(primeN);
    primeVector.resize(primeN/2, count);

    ASSERT_EQ(primeVector.at(primeN/2-1), count);//at()

    primeVector.assign(primeN/2, count*count);

    for(int i = 0; i < primeN/2; i++)
        ASSERT_EQ(primeVector[i], count*count);

    primeVector.push_back(count);//push_back()
    primeVector.push_back(count);//now size primeN/2 + 2
    primeVector.pop_back();//pop_back()

    ASSERT_EQ(primeVector.size(), primeN/2 + 1);

    primeVector.insert(primeVector.begin(), primeN);

    ASSERT_EQ(primeVector[0], primeN);

    primeVector.erase(primeVector.begin());

    ASSERT_EQ(primeVector[0], count*count);

    primeVector.swap(notPrimeVector);

    for(int i = 0; i < primeVector.size(); i++)
        ASSERT_EQ(primeVector[i], 0);
}

//insert()
TEST(VectorTest,InsertCheck)
{
    nVector.resize(0);
    MyVector<int>::Iterator it = nVector.begin();

    nVector.insert(it,2);
    nVector.insert(it,5);
	it = nVector.begin();
    ASSERT_TRUE(5 == *it);
}

//erase()
TEST(VectorTest,EraseCheck)
{
    //cout<<nVector.size()<<endl;
    MyVector<int>::Iterator it = nVector.begin();

    nVector.erase(it);
    nVector.erase(it);
    ASSERT_TRUE(0 == nVector.size());
}

//begin()
TEST(VectorTest,BeginCheck)
{
    int n = 3;
	nVector.push_back(n);
    n = 8;
	nVector.push_back(n);
    MyVector<int>::Iterator it = nVector.begin();

    ASSERT_EQ(*it,3);
}

//end()
TEST(VectorTest,EndCheck)
{
    MyVector<int>::Iterator it = nVector.end();//out of vector
    it--;                                       //last element of vector

    ASSERT_EQ(*it,8);
}

//size()
TEST(VectorTest,sizeCheck)
{
    ASSERT_EQ(nVector.size(), 2);
}

//resize(size)
TEST(VectorTest,ResizeCheck)
{
	nVector.resize(count);

    ASSERT_TRUE(nVector.size() == count);
}

//resize(size, val)
TEST(VectorTest, ResizeValCheck)
{
    int n = nVector.size();
    nVector.resize(count*count, 5);

    for(int i = n; i < nVector.size(); i++)

    ASSERT_TRUE(nVector[count*count-1] == 5);
}

//capacity()
TEST(VectorTest,CapacityCheck)
{
    ASSERT_TRUE(nVector.capacity() == 30);
}

//empty()
TEST(VectorTest,EmptyCheck)
{
	for(int i = 0; i < count*count; i++)
		nVector.pop_back();

    ASSERT_TRUE(nVector.empty());
}

//reserve()
TEST(VectorTest,ReserveCheck)
{
	nVector.reserve(40);

    ASSERT_TRUE(nVector.capacity() > 30);//30 - start capacity
}

//at()
TEST(VectorTest,AtCheck)
{
	nVector.push_back(count);

    ASSERT_TRUE(nVector.at(nVector.size()-1) == count);
}

//front()
TEST(VectorTest,FrontCheck)
{
	MyVector<int>::Iterator it = nVector.begin();
	nVector.insert(it,34);

    ASSERT_EQ(nVector.front(), 34);
}

//back()
TEST(VectorTest,BackCheck)
{
    nVector.push_back(count);
    ASSERT_TRUE(nVector.back() == count);
}

//assign()
TEST(VectorTest,AssignCheck)
{
	nVector.assign(6, 34);

	for(int i = 0; i < 6; i++)
		ASSERT_EQ(nVector.at(i),34);
}

//swap()
TEST(VectorTest,SwapCheck)
{
	MyVector<int> second(50, 0);
    nVector.reserve(50);
	second.swap(nVector);

	for(int i = 0; i < 6; i++)
		ASSERT_EQ(second.at(i),34);
}