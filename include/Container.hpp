#pragma once
#include <memory>
#include <cstdint>
#include <stdexcept>

namespace Bicycle{
  template <class T> using sPtr = std::shared_ptr<T>;
  using usInt = std::uint64_t;

  template <class T> class Container {
  public:
    Container() {
      length = 0;
      capacity = length + 1;
      body = sPtr<T[]>(new T[capacity], std::default_delete<T[]>());
    }

    Container(unsigned int const capacityReq) {
      length = 0;
      capacity = capacityReq;
      body = sPtr<T[]>(new T[capacity], std::default_delete<T[]>());
    }

    Container(Container const & other) {
      length = other.length;
      capacity = length + 1;
      body = sPtr<T[]>(new T[capacity], std::default_delete<T[]>());
      for (usInt i = 0; i < length; ++i)
        body[i] = other.body[i];
    }

    Container(T const & value, unsigned int const lengthReq) {
      length = lengthReq;
      capacity = length + 1;
      body = sPtr<T[]>(new T[capacity], std::default_delete<T[]>());
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

    T &operator[](unsigned int const i) const {
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
      sPtr<T[]> newBody = sPtr<T[]>(new T[capacity], std::default_delete<T[]>());
      for (usInt i = 0; i < length; ++i)
        newBody[i] = body[i];
      newBody[length] = elem;
      length++;
      body = newBody;
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

    void resize(unsigned int lengthReq) {
      if (length < lengthReq)
        for (;length < lengthReq; push_back(T()));
      else
        for (;length > lengthReq; pop_back());
    }

    void reserve(unsigned int capacityReq) {
      if (capacityReq < capacity)
        return;
      sPtr<T[]> newBody = sPtr<T[]>(new T[capacityReq], std::default_delete<T[]>());
      for (usInt i = 0; i < length; ++i, newBody[i] = body[i]);
      body = newBody;
    }

    void shrink_to_fit() {
      sPtr<T[]> newBody = sPtr<T[]>(new T[length], std::default_delete<T[]>());
      for (usInt i = 0; i < length; ++i, newBody[i] = body[i]);
      body = newBody;
    }

  private:
    usInt length;
    usInt capacity;
    std::shared_ptr<T[]> body;
  };
}
