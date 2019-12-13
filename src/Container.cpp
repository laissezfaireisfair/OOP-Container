#include "../include/Container.hpp"

namespace Bicycle{
  template <class T> using sPtr<T> = std::shared_ptr<T>;
  template <class T> using wPtr<T> = std::weak_ptr<T>;
  template <class T> using uPtr<T> = std::unique_ptr<T>;
  using usInt = std::uint64_t;

  template <class T> Container::Container() {
    length = 0;
    body = sPtr<T[]>(new T[0], std::default_delete<T[]>());
  }
  template <class T> Container::Container(Container const & other) {
    length = other.length;
    body = sPtr<T[]>(new T[length], std::default_delete<T[]>());
    for (usInt i = 0; i < length; ++i)
      body[i] = other.body[i];
  }
  template <class T> Container::Container(T const value, usInt const size) {
    length = amount;
    body = sPtr<T[]>(new T[length], std::default_delete<T[]>());
    for (usInt i = 0; i < length; ++i)
      body[i] = value;
  }
  template <class T> T Container::get_back() const;
  template <class T> T Container::get_front() const;
  template <class T> T Container::operator[](usInt const i);
  template <class T> usInt Container::get_length() const;
  template <class T> bool Container::is_empty() const;
  template <class T> void Container::push_back(T const elem);
  template <class T> void Container::push_front(T const elem);
  template <class T> void Container::pop_back(T const elem);
  template <class T> void Container::pop_front(T const elem);
  template <class T> void Container::clean();
}
