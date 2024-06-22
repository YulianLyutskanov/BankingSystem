#pragma once
#include <algorithm>
#include <stdexcept>

static constexpr size_t INITIAL_CAPACITY = 4;

template <class T> class MyVector
{
  private:
    T *collection = nullptr;
    size_t count = 0;
    size_t capacity = INITIAL_CAPACITY;

    void resize(unsigned newAllocatedDataSize);

    void copyFrom(const MyVector &other);
    void free();
    void moveFrom(MyVector &&other);

  public:
    MyVector();
    explicit MyVector(size_t capacity);
    MyVector(const MyVector &other);
    MyVector(MyVector &&other) noexcept;
    MyVector &operator=(const MyVector &other);
    MyVector &operator=(MyVector &&other) noexcept;

    ~MyVector() noexcept;

    void push_back(const T &toPush);
    void push_back(T &&toPush);
    void pop_back() noexcept;
    size_t insert(size_t at, const T &toInsert);
    size_t insert(size_t at, T &&toInsert);
    size_t erase(size_t at);
    void clear() noexcept;
    bool empty() const noexcept;
    size_t size() const noexcept;
    size_t getCapacity() const noexcept;

    const T &operator[](size_t index) const;
    T &operator[](size_t index);
};

static unsigned roundToPowerOfTwo(unsigned v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

static unsigned dataToAllocByCount(unsigned length)
{
    return std::max(roundToPowerOfTwo(length + 1), 4u);
}

template <class T> MyVector<T>::MyVector() : MyVector(INITIAL_CAPACITY)
{
}

template <typename T> MyVector<T>::MyVector(size_t capacity) : capacity(capacity)
{
    collection = new T[capacity];
}

template <class T> MyVector<T>::MyVector(const MyVector<T> &other)
{
    copyFrom(other);
}

template <class T> MyVector<T>::MyVector(MyVector<T> &&other) noexcept
{
    moveFrom(std::move(other));
}

template <class T> void MyVector<T>::copyFrom(const MyVector<T> &other)
{
    capacity = other.capacity;
    count = other.count;
    collection = new T[capacity];

    for (size_t i = 0; i < other.count; i++)
        collection[i] = other.collection[i];
}

template <class T> void MyVector<T>::free()
{
    delete[] collection;
    collection = nullptr;
    count = 0;
    capacity = 0;
}

template <class T> void MyVector<T>::moveFrom(MyVector<T> &&other)
{
    collection = other.collection;
    other.collection = nullptr;

    count = other.count;
    other.count = 0;

    capacity = other.capacity;
    other.capacity = 0;
}

template <class T> MyVector<T> &MyVector<T>::operator=(const MyVector<T> &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

template <class T> MyVector<T> &MyVector<T>::operator=(MyVector<T> &&other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

template <class T> MyVector<T>::~MyVector() noexcept
{
    free();
}

template <class T> void MyVector<T>::resize(unsigned newAllocatedDataSize)
{
    capacity = newAllocatedDataSize;

    T *newCollection = new T[capacity];

    for (size_t i = 0; i < count; i++)
        newCollection[i] = std::move(collection[i]);

    delete[] collection;
    collection = newCollection;
}

template <class T> void MyVector<T>::push_back(const T &toPush)
{
    if (count == capacity)
        resize(dataToAllocByCount(count + 1));

    collection[count++] = toPush;
}

template <class T> void MyVector<T>::push_back(T &&toPush)
{
    if (count == capacity)
        resize(dataToAllocByCount(count + 1));

    collection[count++] = std::move(toPush);
}

template <class T> void MyVector<T>::pop_back() noexcept
{
    if (empty())
        throw std::exception("Vector is empty");

    count--;
}

template <class T> size_t MyVector<T>::insert(size_t at, const T &toInsert)
{
    if (at > count)
        throw std::out_of_range("too large index");

    if (capacity <= count)
    {
        resize(roundToPowerOfTwo(at + 1));
    }

    for (int i = count; i > at; i--) // shift elements ahead
    {
        collection[i] = std::move(collection[i - 1]);
    }
    collection[at] = toInsert;
    count++;
    return at;
}

template <class T> size_t MyVector<T>::insert(size_t at, T &&toInsert)
{
    if (at > count)
        throw std::out_of_range("too large index");

    if (capacity <= count)
    {
        resize(roundToPowerOfTwo(at + 1));
    }

    for (int i = count; i > at; i--) // shift elements ahead
    {
        collection[i] = std::move(collection[i - 1]);
    }

    collection[at] = std::move(toInsert);
    count++;
    return at;
}

template <class T> size_t MyVector<T>::erase(size_t at)
{
    if (at >= count)
        throw std::out_of_range("too large index");

    for (size_t i = at; i < count - 1; i++) // shift back
    {
        collection[i] = collection[i + 1];
    }
    count--;
    return at;
}

template <class T> void MyVector<T>::clear() noexcept
{
    count = 0;
}

template <class T> bool MyVector<T>::empty() const noexcept
{
    return count == 0;
}

template <class T> size_t MyVector<T>::size() const noexcept
{
    return count;
}

template <class T> size_t MyVector<T>::getCapacity() const noexcept
{
    return capacity;
}

template <class T> const T &MyVector<T>::operator[](size_t index) const
{
    return collection[index];
}

template <class T> T &MyVector<T>::operator[](size_t index)
{
    return collection[index];
}
