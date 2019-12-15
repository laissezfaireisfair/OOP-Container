#include "../include/Container.hpp"
#include <stdexcept>

namespace Bicycle{
  template <class T> using sPtr<T> = std::shared_ptr<T>;
  template <class T> using wPtr<T> = std::weak_ptr<T>;
  template <class T> using uPtr<T> = std::unique_ptr<T>;
  using usInt = std::uint64_t;

  template <class T> Container::Container() {
    length = 0;
    body = sPtr<T[]>(new T[length], std::default_delete<T[]>());
  }
  template <class T> Container::Container(Container const & other) {
    length = other.length;
    body = sPtr<T[]>(new T[length], std::default_delete<T[]>());
    for (usInt i = 0; i < length; ++i)
      body[i] = other.body[i];
  }
  template <class T> Container::Container(T const value, usInt const size) {
    length = size;
    body = sPtr<T[]>(new T[length], std::default_delete<T[]>());
    for (usInt i = 0; i < length; ++i)
      body[i] = value;
  }
  template <class T> T Container::get_back() const {
    if (length == 0)
      throw std::length_error("Zero length container dont have back elem");
    return body[length - 1];
  }
  template <class T> T Container::get_front() const {
    if (length == 0)
      throw std::length_error("Zero length container dont have front elem");
    return body[0];
  }
  template <class T> T Container::operator[](usInt const i) {
    if (i >= length)
      throw std::out_of_range("Container size is less than adress");
    return body[0];
  }
  template <class T> usInt Container::get_length() const {
    return length;
  }
  template <class T> bool Container::is_empty() const {
    return length == 0;
  }
  template <class T> void Container::push_back(T const elem);
  template <class T> void Container::push_front(T const elem);
  template <class T> void Container::pop_back(T const elem) {
    if (length == 0)
      throw std::length_error("Zero length container dont have back elem");
    sPtr<T[]> newBody = sPtr<T[]>(new T[length-1], std::default_delete<T[]>());
    for (unsigned int i = 0; i < length - 1; ++i)
      newBody[i] = body[i];
    body = newBody;
  }
  template <class T> void Container::pop_front(T const elem) {
    if (length == 0)
      throw std::length_error("Zero length container dont have front elem");
      sPtr<T[]> newBody = sPtr<T[]>(new T[length-1], std::default_delete<T[]>());
      for (unsigned int i = 0; i < length - 1; ++i)
        newBody[i] = body[i + 1];
      body = newBody;
  }
  template <class T> void Container::clean() {
    length = 0;
    body = sPtr<T[]>(new T[length], std::default_delete<T[]>());
  }
}
