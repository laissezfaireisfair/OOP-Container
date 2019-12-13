#include "../include/Container.hpp"

namespace Bicycle{
  template <class T> T Container::get_back() const;
  template <class T> T Container::get_front() const;
  template <class T> T Container::operator[](std::uint64_t const i);
  template <class T> std::uint64_t Container::get_length() const;
  template <class T> bool Container::is_empty() const;
  template <class T> void Container::push_back(T const elem);
  template <class T> void Container::push_front(T const elem);
  template <class T> void Container::pop_back(T const elem);
  template <class T> void Container::pop_front(T const elem);
  template <class T> void Container::clean();
}
