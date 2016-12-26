#include <cstring>
#include <stdexcept>
#include "MyVector.h"

using namespace std;

typedef typename MyVector<class T>::Iterator Iterator;
typedef typename MyVector<class T>::ReverseIterator ReverseIterator;


template<class T>
MyVector<T>::MyVector(unsigned int capacity,const T& val)
{
    _capacity = capacity;
    _vector = new T[capacity];
    for(int i = 0; i < capacity; i++)
        _vector[i] = val;
    _size = _capacity;
}

template<class T>
MyVector<T>::MyVector(Iterator first, Iterator last)
{
    Iterator it = first;
    _size = 0;
    _vector = new T[(*last-*first)/sizeof(T)];
    while(it != last)
    {
        _vector[_size] = *first;
        _size++;
        it++;
    }
}

template<class T>
MyVector<T>::MyVector(const MyVector& copy) : _size(copy._size), _capacity(copy._capacity)
{
    for(int i = 0; i < copy._size; i++)
        _vector[i] = copy._vector[i];
}

template<class T>
MyVector<T>::MyVector(MyVector&& x) : _vector(NULL), _capacity(0), _size(0)
{
    _capacity = x._capacity;
    _size = x._size;
    _vector = x._vector;
    x._capacity = 0;
    x._size = 0;
    x._vector = NULL;
}

template<class T>
MyVector<T>::~MyVector()
{
    if(_vector != NULL)
        delete[] _vector;
}

template<class T>
MyVector<T>& MyVector<T>::operator=(const MyVector& right)
{
    if(&right == this)
        return *this;
    for(int i = 0; i < right._size; i++)
        _vector[i] = right._vector[i];
    _size = right._size;
    _capacity = right._capacity;
    return *this;
}

template<class T>
MyVector<T>& MyVector<T>::operator=(MyVector&& x)
{
    if(this != &x)
    {
        cout<<"in move =";
        delete[] _vector;

        _capacity = x._capacity;
        _size = x._size;
        _vector = x._vector;
        x._capacity = 0;
        x._size = 0;
        x._vector = NULL;
    }

    return *this;
}



////////////////////////////////////
//Iterators
////////////////////////////////////
template<class T>
typename MyVector<T>::Iterator MyVector<T>::begin()
{
    return Iterator(_vector);
}

template<class T>
const typename MyVector<T>::Iterator MyVector<T>::begin() const
{
    return Iterator(_vector);
}

template<class T>
typename MyVector<T>::Iterator MyVector<T>::end()
{
    return Iterator(_vector + _size);
}

template<class T>
const typename MyVector<T>::Iterator MyVector<T>::end() const
{
    return Iterator(_vector + _size);
}

template<class T>
typename MyVector<T>::ReverseIterator MyVector<T>::rbegin()
{
    return ReverseIterator(_vector + _size - 1);
}

template<class T> 
const typename MyVector<T>::ReverseIterator MyVector<T>::rbegin() const
{
    return ReverseIterator(_vector + _size - 1);
}

template<class T>
typename MyVector<T>::ReverseIterator MyVector<T>::rend()
{
    return ReverseIterator(_vector - 1);
}

template<class T>
const typename MyVector<T>::ReverseIterator MyVector<T>::rend() const
{
    return ReverseIterator(_vector - 1);
}

template<class T>
typename MyVector<T>::ConstIterator MyVector<T>::cbegin() const
{
    return ConstIterator(_vector);
}

template<class T>
typename MyVector<T>::ConstIterator MyVector<T>::cend() const
{
    return ConstIterator(_vector + _size);
}

template<class T> 
typename MyVector<T>::ConstReverseIterator MyVector<T>::crbegin() const
{
    return ConstReverseIterator(_vector + _size);
}

template<class T>
typename MyVector<T>::ConstReverseIterator MyVector<T>::crend() const
{
    return ConstReverseIterator(_vector);
}

////////////////////////////////////
//Capacity
////////////////////////////////////

template<class T>
unsigned int MyVector<T>::size() const
{
    return _size;
}

template<class T>
unsigned int MyVector<T>::max_size() const
{
    return int(-1)/sizeof(T);
}

template<class T>
void MyVector<T>::resize(unsigned int nSize)
{
    resize(nSize, (const T&)0);
}

template<class T>
void MyVector<T>::resize(unsigned int nSize, const T& val)
{
    if(nSize > _capacity)
        return;

    if(nSize > _size)
    {
        for(int i = _size; i < nSize; i++)
            _vector[i] = val;
    }

    _size = nSize;
}

template<class T>
unsigned int MyVector<T>::capacity() const
{
    return _capacity;
}

template<class T>
bool MyVector<T>::empty() const
{
    if(_size == 0)
        return true;
    else
        return false;
}

template<class T>
void MyVector<T>::reserve(unsigned int nCapacity)
{
    if(nCapacity < _capacity)
        return;
    T* nVector = new T[nCapacity];

    memcpy(nVector, _vector, sizeof(T)*_size);

    _capacity = nCapacity;
    delete[] _vector;
    _vector = nVector;
}

template<class T>
void MyVector<T>::shrink_to_fit()
{
    reserve(_size);
}
////////////////////////////////////////////
//Element access
////////////////////////////////////////////
template<class T>
T& MyVector<T>::operator[](unsigned int index) const
{
    return _vector[index];
}

template<class T>
const T& MyVector<T>::at(unsigned int index) const
{
    if(index >= _size)
        throw out_of_range("invalid index");
    
    return _vector[index];
}

template<class T>
const T& MyVector<T>::front() const
{
    return _vector[0];
}

template<class T>
const T& MyVector<T>::back() const
{
    return _vector[_size-1];
}

template<class T>
T* MyVector<T>::data() const
{
    return _vector;
}

//////////////////////////////////////////////
//Modifiers
//////////////////////////////////////////////
template<class T>
void MyVector<T>::assign(unsigned int n, T val)
{
    delete[] _vector;
    _size=0;
    _vector = new T[_capacity];
    for(_size = 0; _size < n; _size++)
        _vector[_size] = val;
}

template<class T>
void MyVector<T>::assign(const Iterator& it1,const Iterator& it2)
{
    Iterator it = it1;
    delete[] _vector;
    _vector = new T[capacity];
    for(_size = 0; it != it2; it++,_size++)
        _vector[_size] = *it;
}
template<class T>
void MyVector<T>::push_back(T& nObj)
{
    _vector[_size] = nObj;
    _size++;
}

template<class T>
void MyVector<T>::pop_back()
{
    _size--;
}

template<class T>
typename MyVector<T>::Iterator MyVector<T>::insert(Iterator position, const  T& val)
{

    insert(position, 1, val);

    return position;
}

template<class T>
void MyVector<T>::insert(Iterator position, unsigned int n, const T& val)
{
    T* ptr = _vector;
    T nextObj,curObj;
    T nextObjs[n];

    ptr += position.itPtr() - ptr;

    for(int i = 0; i < n; i++)//fill n positions and remember values 
    {
        nextObjs[i] = *ptr;
        *ptr = val;
        ptr++;
    }
    for(int i = 0; i < n; i++)
    {
        *ptr = nextObjs[i];
        ptr++;
    }
    nextObj = *ptr;
    for(int i = ( position.itPtr() - ptr + 1); i < (_size + n); i++,ptr++)//shift to left
    {
        curObj = nextObj;
        nextObj = *ptr;
        *ptr = curObj;
    }

    _size+=n;
}

template<class T>
void MyVector<T>::insert(Iterator position, Iterator first, Iterator last)
{
    T* ptr = _vector;
    Iterator it = first;
    T nextObj,curObj;
    unsigned int n = (last.itPtr() - first.itPtr())/sizeof(T); 
    T nextObjs[n];

    ptr += position.itPtr() - ptr;

    for(int i = 0; it != last; i++)//fill n positions and remember values 
    {
        nextObjs[i] = *ptr;
        *ptr = *it;
        it++;
        ptr++;
    }
    for(int i = 0; i < n; i++)
    {
        *ptr = nextObjs[i];
        ptr++;
    }
    nextObj = *ptr;
    for(int i = ( position.itPtr() - ptr + 1); i < (_size + n); i++,ptr++)//shift to left
    {
        curObj = nextObj;
        nextObj = *ptr;
        *ptr = curObj;
    }

    _size+= n;
}

template<class T>
typename MyVector<T>::Iterator MyVector<T>::erase(Iterator position)
{
    return erase(Iterator(position.itPtr()), Iterator(position.itPtr()+1));
}

template<class T>
typename MyVector<T>::Iterator MyVector<T>::erase(Iterator first, Iterator last)
{
    T* ptr;
    T* nxt;
    unsigned int counter = 0;

    ptr = first.itPtr();
    nxt = last.itPtr();

    while(nxt != end().itPtr())
    {
        *ptr = *nxt;
        *nxt = 0;
        ptr++;
        nxt++;
    }

    if((ptr - last.itPtr()) < 0)
        while(ptr != last.itPtr())
        {
            *ptr = 0;
            counter++;
            ptr++;
        }

    _size -= last.itPtr() - first.itPtr();
    
    return first;
}


template<class T>
void MyVector<T>::swap(MyVector& ex)
{
    MyVector s(ex._size, 0);
    s = ex;
    ex = *this;
    *this = s;
}

template<class T>
void MyVector<T>::clear()
{
    delete[] _vector;
    _size = 0;
    _capacity = 0;
}

/*
    ////////////////////////////
    Iterator
    ////////////////////////////
*/

template<class T>
MyVector<T>::Iterator::Iterator(T* x) :pointer(x){}

template<class T>
MyVector<T>::Iterator::Iterator(const Iterator& it) :pointer(it.pointer){}

template<class T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator++(int)
{
    Iterator nIt(*this);
    operator++();
    return nIt;
}

template<class T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator++()
{
    pointer++;
    return *this;
}

template<class T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator--(int)
{
    Iterator nIt(*this);
    operator--();
    return nIt;
}

template<class T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator--()
{
    pointer--;
    return *this;
}

template<class T>
T& MyVector<T>::Iterator::operator*()
{
    return *pointer;
}

template<class T>
bool MyVector<T>::Iterator::operator==(const Iterator& right) const
{
    return (pointer == right.pointer);
}

template<class T>
bool MyVector<T>::Iterator::operator!=(const Iterator& right) const
{
    return (pointer != right.pointer);
}

template<class T>
T* MyVector<T>::Iterator::itPtr() const
{
    return pointer;
}
///////////////////////////////////////////////
//ReverseIterator
///////////////////////////////////////////////

template<class T>
MyVector<T>::ReverseIterator::ReverseIterator(T* x) : Iterator(x)
{}

template<class T>
MyVector<T>::ReverseIterator::ReverseIterator(const ReverseIterator& it) : Iterator(it)
{}

template<class T>
typename MyVector<T>::ReverseIterator MyVector<T>::ReverseIterator::operator++(int)
{
    ReverseIterator nIt(*this);
    operator++();
    return nIt;
}

template<class T>
typename MyVector<T>::ReverseIterator& MyVector<T>::ReverseIterator::operator++()
{
    Iterator::pointer--;
    return *this;
}

template<class T>
typename MyVector<T>::ReverseIterator MyVector<T>::ReverseIterator::operator--(int)
{
    ReverseIterator nIt(*this);
    operator--();
    return nIt;
}

template<class T>
typename MyVector<T>::ReverseIterator& MyVector<T>::ReverseIterator::operator--()
{
    MyVector<T>::Iterator::pointer++;
    return *this;
}

////////////////////////////////////////////////////
//ConstIterator
////////////////////////////////////////////////////
template<class T>
MyVector<T>::ConstIterator::ConstIterator(T* x) : Iterator(x)
{}

template<class T>
MyVector<T>::ConstIterator::ConstIterator(const ConstIterator& it) : Iterator(it)
{}

template<class T>
T& MyVector<T>::ConstIterator::operator*() const
{
    return *MyVector<T>::Iterator::pointer;
}

////////////////////////////////////////////////////
//ConstReverseIterator
////////////////////////////////////////////////////
template<class T>
MyVector<T>::ConstReverseIterator::ConstReverseIterator(T* x) : Iterator(x)
{}

template<class T>
MyVector<T>::ConstReverseIterator::ConstReverseIterator(const ConstReverseIterator& it) : Iterator(it)
{}


template<class T>
T& MyVector<T>::ConstReverseIterator::operator*() const
{
    return *MyVector<T>::Iterator::ReverseIterator::pointer;
}