#pragma once
#include <memory>
#include <cstdint>
#include <stdexcept>

namespace Bicycle{
  using usInt = std::uint64_t;

  template <class T> class Container {
  public:
    Container() {
      length = 0;
      capacity = length + 1;
      memPool = new char[sizeof(T) * capacity];
      if (memPool == nullptr)
        throw std::runtime_error("Memory cannot be allocated.");
      body = reinterpret_cast<T*>(memPool);
    }

    Container(unsigned int const capacityReq) {
      length = 0;
      capacity = capacityReq;
      memPool = new char[sizeof(T) * capacity];
      if (memPool == nullptr)
        throw std::runtime_error("Memory cannot be allocated.");
      body = reinterpret_cast<T*>(memPool);
    }

    Container(Container const & other) {
      length = other.length;
      capacity = length + 1;
      memPool = new char[sizeof(T) * capacity];
      if (memPool == nullptr)
        throw std::runtime_error("Memory cannot be allocated.");
      body = reinterpret_cast<T*>(memPool);
      for (usInt i = 0; i < length; ++i)
        body[i] = other.body[i];
    }

    Container(T const & value, unsigned int const lengthReq) {
      length = lengthReq;
      capacity = length + 1;
      memPool = new char[sizeof(T) * capacity];
      if (memPool == nullptr)
        throw std::runtime_error("Memory cannot be allocated.");
      body = reinterpret_cast<T*>(memPool);
      for (usInt i = 0; i < length; ++i)
        body[i] = value;
    }

    ~Container() {
      deinitialise();
    }

    T &get_back() const {
      if (length == 0)
        throw std::length_error("Zero length container dont have back elem");
      return body[length - 1];
    }

    T &get_front() const {
      if (length == 0)
        throw std::length_error("Zero length container dont have front elem");
      return body[0];
    }

    T &operator[](usInt const i) const {
      if (i >= length)
        throw std::out_of_range("Container size is less than adress");
      T & ref = body[i];
      return ref;
    }

    std::uint64_t get_length() const {
      return length;
    }

    std::uint64_t get_capacity() const {
      return capacity;
    }

    bool is_empty() const {
      return length == 0;
    }

    void push_back(T const & elem) {
      if (capacity > length) {
        body[length] = elem;
        ++length;
        return;
      }
      usInt newCapacity = capacity * 2;
      char *newMemPool = new char[sizeof(T) * newCapacity];
      if (newMemPool == nullptr)
        throw std::runtime_error("Memory cannot be allocated.");
      T *newBody = reinterpret_cast<T*>(newMemPool);
      for (usInt i = 0; i < length; ++i)
        newBody[i] = body[i];
      newBody[length] = elem;
      usInt newBodyLen = length + 1;
      deinitialise();
      body = newBody;
      length = newBodyLen;
      memPool = newMemPool;
      capacity = newCapacity;
    }

    void pop_back() {
      if (length == 0)
        throw std::length_error("Zero length container dont have back elem");
      body[length - 1].~T();
      --length;
    }

    void clean() {
      for (; length > 0; --length)
        body[length - 1].~T();
    }

    void resize(unsigned int const lengthReq) {
      if (length >= lengthReq) {
        for (;length > lengthReq; body[length - 1].~T(), --length) {}
        return;
      }
      reserve(lengthReq); // If capacity is enough it won't do anything
      for (; length < lengthReq; body[length] = T(), ++length) {}
    }

    void reserve(unsigned int const capacityReq) {
      if (capacityReq <= capacity)
        return;
      char *newMemPool = new char[sizeof(T) * capacityReq];
      if (newMemPool == nullptr)
        throw std::runtime_error("Memory cannot be allocated.");
      T *newBody = reinterpret_cast<T*>(newMemPool);
      usInt const newLength = length;
      for (usInt i = 0; i < length; newBody[i] = body[i], ++i) {}
      deinitialise();
      memPool = newMemPool;
      capacity = capacityReq;
      body = newBody;
      length = newLength;
    }

    void shrink_to_fit() {
      char *newMemPool = new char[sizeof(T) * capacity];
      if (memPool == nullptr)
        throw std::runtime_error("Memory cannot be allocated.");
      T *newBody = reinterpret_cast<T*>(newMemPool);
      usInt const newLength = length;
      for (usInt i = 0; i < length; newBody[i] = body[i], ++i) {}
        body = newBody;
      deinitialise();
      memPool = newMemPool;
      capacity = newLength;
      length = newLength;
      body = newBody;
    }

    Container<T> & operator= (Container<T> const & other) {
      deinitialise();
      length = other.length;
      capacity = length + 1;
      memPool = new char[sizeof(T) * capacity];
      if (memPool == nullptr)
        throw std::runtime_error("Memory cannot be allocated.");
      body = reinterpret_cast<T*>(memPool);
      for (usInt i = 0; i < length; ++i)
        body[i] = other.body[i];
      return (*this);
    }

  private:
    void deinitialise() {
      clean();
      delete []memPool;
      capacity = 0;
    }
    usInt length;
    usInt capacity;
    char *memPool;
    T *body;
  };
}
