#pragma once
#include <exception>
#include <utility>

template <typename T> class MyStack
{
  private:
    static const short INITIAL_CAPACITY = 4;
    static const short RESIZE_COEF = 2; // the most optimal is between 1.4 and 1.5

    T *data = nullptr;
    size_t size = 0;
    size_t capacity;

    void resize(size_t newCapacity);

    // Not needed functions - created by in class
    void assertIndex(size_t index) const;
    void upsizeIfNeeded();
    void downsizeIfNeeded();

  public:
    MyStack();
    MyStack(size_t capacity);
    MyStack(const MyStack<T> &other);
    MyStack(MyStack<T> &&other);
    MyStack<T> &operator=(const MyStack<T> &other);
    MyStack<T> &operator=(MyStack<T> &&other);
    ~MyStack();

    size_t getSize() const;
    size_t getCapacity() const;

    void pushBack(const T &element);
    void pushBack(T &&element);
    T popBack();
    T &peek();
    const T &peek() const;

    bool empty() const;
    void clear();
    void shrinkToFit();

  private:
    void move(MyStack<T> &&other);
    void copyFrom(const MyStack<T> &other);
    void free();
};

template <typename T> MyStack<T>::MyStack() : MyStack(INITIAL_CAPACITY)
{
}

template <typename T> MyStack<T>::MyStack(size_t capacity) : capacity(capacity)
{
    data = new T[capacity];
}

template <typename T> MyStack<T>::MyStack(const MyStack<T> &other)
{
    copyFrom(other);
}
template <typename T> MyStack<T>::MyStack(MyStack<T> &&other)
{
    move(std::move(other));
}

template <typename T> MyStack<T> &MyStack<T>::operator=(const MyStack<T> &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

template <typename T> MyStack<T> &MyStack<T>::operator=(MyStack<T> &&other)
{
    if (this != &other)
    {
        free();
        move(std::move(other));
    }

    return *this;
}

template <typename T> MyStack<T>::~MyStack()
{
    free();
}

template <typename T> void MyStack<T>::assertIndex(size_t index) const
{
    if (index >= size)
    {
        throw std::exception("Out of range");
    }
}

template <typename T> void MyStack<T>::upsizeIfNeeded()
{
    if (size == capacity)
    {
        resize(capacity * RESIZE_COEF);
    }
}

template <typename T> void MyStack<T>::downsizeIfNeeded()
{
    if (size * RESIZE_COEF * RESIZE_COEF <= capacity)
    {
        resize(capacity / RESIZE_COEF);
    }
}

template <typename T> void MyStack<T>::resize(size_t newCapacity)
{
    capacity = newCapacity;
    T *temp = new T[capacity];

    // Note: the std::MyStack allocates ONLY MORE than the current capacity
    if (size > newCapacity)
    {
        size = newCapacity;
    }

    for (size_t i = 0; i < size; i++)
    {
        temp[i] = std::move(data[i]);
    }

    delete[] data;
    data = temp;
}

template <typename T> size_t MyStack<T>::getSize() const
{
    return size;
}

template <typename T> size_t MyStack<T>::getCapacity() const
{
    return capacity;
}

template <typename T> void MyStack<T>::pushBack(const T &element)
{
    upsizeIfNeeded();
    data[size++] = element;
}

template <typename T> void MyStack<T>::pushBack(T &&element)
{
    upsizeIfNeeded();
    data[size++] = std::move(element);
}

template <typename T> T MyStack<T>::popBack()
{
    if (empty())
    {
        throw std::exception("MyStack is empty");
    }
    // Note: the actual std::MyStack does NOT lower its capacity on this function
    // downsizeIfNeeded();
    // Note: the actual std::MyStack does NOT return on popback
    return data[--size];
}

template <typename T> T &MyStack<T>::peek()
{
    if (empty())
    {
        throw std::exception("MyStack is empty");
    }

    return data[size - 1];
}

template <typename T> const T &MyStack<T>::peek() const
{
    if (empty())
    {
        throw std::exception("MyStack is empty");
    }

    return data[size - 1];
}

template <typename T> bool MyStack<T>::empty() const
{
    return size == 0;
}

template <typename T> void MyStack<T>::clear()
{
    size = 0;
}

template <typename T> void MyStack<T>::shrinkToFit()
{
    resize(size);
}

template <typename T> void MyStack<T>::move(MyStack<T> &&other)
{
    size = other.size;
    capacity = other.capacity;
    data = other.data;
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template <typename T> void MyStack<T>::copyFrom(const MyStack<T> &other)
{
    size = other.size;
    capacity = other.capacity;
    data = new T[capacity];

    for (size_t i = 0; i < other.size; i++)
    {
        data[i] = other.data[i];
    }
}

template <typename T> void MyStack<T>::free()
{
    delete[] data;
    data = nullptr;
    size = capacity = 0;
}
