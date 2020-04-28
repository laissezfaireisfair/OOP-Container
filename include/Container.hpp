#pragma once
#include <memory>
#include <cstdint>
#include <stdexcept>

namespace Bicycle{
  using usInt = std::uint64_t;

  template <class T> class Container {
  public:
    Container() {
      alloc_body(0);
      length = 0;
    }

    Container(unsigned int const newCapacity) {
      alloc_body(newCapacity);
      length = 0;
    }

    Container(Container const & other) {
      alloc_body(other.capacity);
      for (length = 0; length < other.length; ++length)
        body[length] = other.body[length];
    }

    Container(T const & value, unsigned int const newLength) {
      alloc_body(newLength);
      for (length = 0; length < newLength; ++length)
        body[length] = value;
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
      T & elem = body[i];
      return elem;
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
      if (capacity == 0) {
        usInt const newCapacity = 1;
        alloc_body(newCapacity);
      } else {
        usInt const newCapacity = capacity * 2;
        move_body(length, newCapacity);
      }
      body[length] = elem;
      ++length;
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

    void resize(unsigned int const newLength) {
      if (newLength <= length) {
        while (length > newLength) {
           body[length - 1].~T();
           --length;
        }
        return;
      }
      if (newLength > capacity) {
        usInt newCapacity = newLength;
        move_body(newLength, newCapacity);
        return;
      }
      while (length < newLength) {
         body[length] = T();
         ++length;
      }
    }

    void reserve(unsigned int const newCapacity) {
      if (newCapacity <= capacity)
        return;
      move_body(length, newCapacity);
    }

    void shrink_to_fit() {
      if (capacity == length)
	      return;
      usInt const newCapacity = length;
      move_body(length, newCapacity);
    }

    Container<T> & operator= (Container<T> const & other) {
      deinitialise();
      alloc_body(other.capacity);
      while (length < other.length) {
        body[length] = other.body[length];
        ++length;
      }
      return *this;
    }

  private:
    void alloc_body(usInt newCapacity) {
      capacity = newCapacity;
      if (capacity == 0) {
        memPool = nullptr;
        body = nullptr;
      } else {
      memPool = new char[sizeof(T) * capacity];
      body = reinterpret_cast<T*>(memPool);
      }
    }

    void move_body(usInt newLength, usInt newCapacity) {
      if (newLength > newCapacity)
        throw std::invalid_argument("move_body(): length > capacity.");
      char *newMemPool = new char[sizeof(T) * newCapacity];
      T *newBody = reinterpret_cast<T*>(newMemPool);
      for (usInt i = 0; i < newLength; ++i) {
        if (i < length)
          newBody[i] = body[i];
        else
          newBody[i] = T();
      }
      deinitialise();
      memPool = newMemPool;
      capacity = newCapacity;
      body = newBody;
      length = newLength;
    }

    void deinitialise() {
      clean();
      delete []memPool;
      memPool = nullptr;
      body = nullptr;
      capacity = 0;
    }
    usInt length;
    usInt capacity;
    char *memPool;
    T *body;
  };
}
