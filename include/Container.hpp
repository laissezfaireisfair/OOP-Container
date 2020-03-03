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
      body = NULL;
    }

    Container(unsigned int const capacityReq) {
      length = 0;
      capacity = capacityReq;
      memPool = new char[sizeof(T) * capacity];
      if (memPool == nullptr)
        throw std::runtime_error("Memory cannot be allocated.");
      body = NULL;
    }

    Container(Container const & other) {
      length = other.length;
      capacity = length + 1;
      memPool = new char[sizeof(T) * capacity];
      if (memPool == nullptr)
        throw std::runtime_error("Memory cannot be allocated.");
      body = new (memPool) T[length];
      if (body == nullptr)
        throw std::runtime_error("Constructing objects failed.");
      for (usInt i = 0; i < length; ++i)
        body[i] = other.body[i];
    }

    Container(T const & value, unsigned int const lengthReq) {
      length = lengthReq;
      capacity = length + 1;
      memPool = new char[sizeof(T) * capacity];
      if (memPool == nullptr)
        throw std::runtime_error("Memory cannot be allocated.");
      body = new (memPool) T[length];
      if (body == nullptr)
        throw std::runtime_error("Constructing objects failed.");
      for (usInt i = 0; i < length; ++i)
        body[i] = value;
    }

    ~Container() {
      for (usInt i = 0; i < length; ++i)
        body[i].~T();
      delete []memPool;
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
      capacity *= 2;
      char *newMemPool = new char[sizeof(T) * capacity];
      if (newMemPool == nullptr)
        throw std::runtime_error("Memory cannot be allocated.");
      T *newBody = new (newMemPool) T[length];
      if (newBody == nullptr)
        throw std::runtime_error("Constructing objects failed.");
      for (usInt i = 0; i < length; ++i)
        newBody[i] = body[i];
      newBody[length] = elem;
      length++;
      body = newBody;
      delete []memPool;
      memPool = newMemPool;
    }

    void pop_back() {
      if (length == 0)
        throw std::length_error("Zero length container dont have back elem");
      body[length - 1].~T();
      --length;
    }

    void clean() {
      while(!is_empty())
        pop_back();
    }

    void resize(unsigned int const lengthReq) {
      if (length < lengthReq)
        for (;length < lengthReq; push_back(T())) {}
      else
        for (;length > lengthReq; pop_back()) {}
    }

    void reserve(unsigned int const capacityReq) {
      if (capacityReq <= capacity)
        return;
      char *newMemPool = new char[sizeof(T) * capacityReq];
      if (newMemPool == nullptr)
        throw std::runtime_error("Memory cannot be allocated.");
      T *newBody = new (newMemPool) T[length];
      if (newBody == nullptr)
        throw std::runtime_error("Constructing objects failed.");
      for (usInt i = 0; i < length; newBody[i] = body[i], ++i) {}
      body = newBody;
      capacity = capacityReq;
      delete []body;
      body = newBody;
    }

    void shrink_to_fit() {
      char *newMemPool = new char[sizeof(T) * capacity];
      if (memPool == nullptr)
        throw std::runtime_error("Memory cannot be allocated.");
      T *newBody = new (newMemPool) T(length);
      if (newBody == nullptr)
        throw std::runtime_error("Constructing objects failed.");
      for (usInt i = 0; i < length; newBody[i] = body[i], ++i) {}
        body = newBody;
      capacity = length;
      delete []body;
      body = newBody;
    }

  private:
    usInt length;
    usInt capacity;
    char *memPool;
    T *body;
  };
}
