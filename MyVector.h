#ifndef MYVECTOR_H//prevent repeat connection
#define MYVECTOR_H


/**
MyVector
include:
    templates;+
    all basic vector methods+
    makefile+
    iterators;+
    unit tests;
    copy constructor;+
**/

template <class T>
class MyVector
{
public:
    /**
    Iterator for MyVector class
    **/
    class Iterator
    {
    protected:
        T* pointer;
    public:
        Iterator(T* x);
        Iterator(const Iterator& it);
        Iterator operator++(int);
        Iterator& operator++();
        Iterator operator--(int);
        Iterator& operator--();
        bool operator==(const Iterator& right) const;
        bool operator!=(const Iterator& right) const;
        T& operator*();
        T* itPtr() const;
    };

    class ReverseIterator: public MyVector<T>::Iterator
    {
    public:
        ReverseIterator(T* x);
        ReverseIterator(const ReverseIterator& it);
        ReverseIterator operator++(int);
        ReverseIterator& operator++();
        ReverseIterator operator--(int);
        ReverseIterator& operator--();
    };

    class ConstIterator: public MyVector<T>::Iterator
    {
    public:
        ConstIterator(T* x);
        ConstIterator(const ConstIterator& it);
        T& operator*() const;
    };

    class ConstReverseIterator: public MyVector<T>::ReverseIterator
    {
    public:
        ConstReverseIterator(T* x);
        ConstReverseIterator(const ConstReverseIterator& it);
        T& operator*() const;
    };
    
    //main fill constructor
    MyVector(unsigned int capacity, const T& val);
    MyVector(Iterator first, Iterator last);
    //copy constructor
    MyVector(const MyVector& copy);
    MyVector(MyVector&& x);
    ~MyVector();


    T& operator[](unsigned int index) const;
    MyVector<T>& operator=(const MyVector& right);
    MyVector<T>& operator=(MyVector&& x);

    Iterator begin();
    const Iterator begin() const;
    Iterator end();
    const Iterator end() const;

    ReverseIterator rbegin();
    const ReverseIterator rbegin() const;
    ReverseIterator rend();
    const ReverseIterator rend() const;

    ConstIterator cbegin() const;
    ConstIterator cend() const;
    ConstReverseIterator crbegin() const;
    ConstReverseIterator crend() const;


    unsigned int size() const;
    unsigned int max_size() const;
    void resize(unsigned int nSize);
    void resize(unsigned int nSize, const T& val);
    unsigned int capacity() const;
    bool empty() const;
    void reserve(unsigned int nCapacity);
    void shrink_to_fit();

    const T& at(unsigned int index) const;
    const T& front() const;
    const T& back() const;
    T* data() const;

    void assign(unsigned int n, T val);
    void assign(const Iterator& it1,const Iterator& it2);
    void push_back(T& nObj);
    void pop_back();
    Iterator insert(Iterator position,const T& nObj);
    void insert(Iterator position, unsigned int n, const T& val);
    void insert(Iterator position, Iterator first, Iterator last);
    Iterator erase(Iterator position);
    Iterator erase(Iterator first, Iterator last);
    void swap(MyVector& ex);
    void clear();
private:
    T* _vector;
    unsigned int _capacity;
    unsigned int _size;
};


#endif // MYVECTOR_H
