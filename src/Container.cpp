#include "../include/Container.hpp"
#include <stdexcept>

namespace Bicycle{
  template <class T> using sPtr = std::shared_ptr<T>;
  template <class T> using wPtr = std::weak_ptr<T>;
  template <class T> using uPtr = std::unique_ptr<T>;
  using usInt = std::uint64_t;

  template <class T> Container<T>::Container() {
    length = 0;
    body = sPtr<T[]>(new T[length], std::default_delete<T[]>());
  }

  template <class T> Container<T>::Container(Container const & other) {
    length = other.length;
    body = sPtr<T[]>(new T[length], std::default_delete<T[]>());
    for (usInt i = 0; i < length; ++i)
      body[i] = other.body[i];
  }

  template <class T> Container<T>::Container(T const & value, usInt const size) {
    length = size;
    body = sPtr<T[]>(new T[length], std::default_delete<T[]>());
    for (usInt i = 0; i < length; ++i)
      body[i] = value;
  }

  template <class T> T &Container<T>::get_back() const {
    if (length == 0)
      throw std::length_error("Zero length container dont have back elem");
    return body[length - 1];
  }

  template <class T> T &Container<T>::get_front() const {
    if (length == 0)
      throw std::length_error("Zero length container dont have front elem");
    return body[0];
  }

  template <class T> T &Container<T>::operator[](usInt const i) const {
    if (i >= length)
      throw std::out_of_range("Container size is less than adress");
    T & ref = body[i];
    return ref;
  }

  template <class T> usInt Container<T>::get_length() const {
    return length;
  }

  template <class T> bool Container<T>::is_empty() const {
    return length == 0;
  }

  template <class T> void Container<T>::push_back(T const  &elem) {
    sPtr<T[]> newBody = sPtr<T[]>(new T[length+1], std::default_delete<T[]>());
    for (unsigned int i = 0; i < length; ++i)
      newBody[i] = body[i];
    newBody[length] = elem;
    body = newBody;
    length++;
  }

  template <class T> void Container<T>::pop_back() {
    if (length == 0)
      throw std::length_error("Zero length container dont have back elem");
    sPtr<T[]> newBody = sPtr<T[]>(new T[length-1], std::default_delete<T[]>());
    for (unsigned int i = 0; i < length - 1; ++i)
      newBody[i] = body[i];
    body = newBody;
    length--;
  }

  template <class T> void Container<T>::clean() {
    length = 0;
    body = sPtr<T[]>(new T[length], std::default_delete<T[]>());
  }
}
