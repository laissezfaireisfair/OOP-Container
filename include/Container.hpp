#pragma once
#include <memory>
#include <cstdint>
#include <stdexcept>

namespace Bicycle{
  template <class T> using sPtr = std::shared_ptr<T>;
  template <class T> using wPtr = std::weak_ptr<T>;
  template <class T> using uPtr = std::unique_ptr<T>;
  using usInt = std::uint64_t;

  template <class T> class Container {
  public:
    Container() {
      length = 0;
      body = sPtr<T[]>(new T[length], std::default_delete<T[]>());
    }
    Container(Container const & other) {
      length = other.length;
      body = sPtr<T[]>(new T[length], std::default_delete<T[]>());
      for (usInt i = 0; i < length; ++i)
        body[i] = other.body[i];
    }
    Container(T const & value, std::uint64_t const size) {
      length = size;
      body = sPtr<T[]>(new T[length], std::default_delete<T[]>());
      for (usInt i = 0; i < length; ++i)
        body[i] = value;
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
    T &operator[](std::uint64_t const i) const {
      if (i >= length)
        throw std::out_of_range("Container size is less than adress");
      T & ref = body[i];
      return ref;
    }
    std::uint64_t get_length() const {
      return length;
    }
    bool is_empty() const {
      return length == 0;
    }
    void push_back(T const & elem) {
      sPtr<T[]> newBody = sPtr<T[]>(new T[length+1], std::default_delete<T[]>());
      for (unsigned int i = 0; i < length; ++i)
        newBody[i] = body[i];
      newBody[length] = elem;
      body = newBody;
      length++;
    }
    void pop_back() {
      if (length == 0)
        throw std::length_error("Zero length container dont have back elem");
      sPtr<T[]> newBody = sPtr<T[]>(new T[length-1], std::default_delete<T[]>());
      for (unsigned int i = 0; i < length - 1; ++i)
        newBody[i] = body[i];
      body = newBody;
      length--;
    }
    void clean() {
      length = 0;
      body = sPtr<T[]>(new T[length], std::default_delete<T[]>());
    }
  private:
    std::uint64_t length;
    std::shared_ptr<T[]> body;
  };
}
