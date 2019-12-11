#pragma once
#include <memory>
#include <cstdint>

namespace Bicycle{
  using wPtr<T> = std::weak_ptr<T>;
  using sPtr<T> = std::shared_ptr<T>;

  template <class T> class Elem;

  template <class T> class Container {
  public:
    T get_back() const;
    T get_front() const;
    T operator[](std::uint64_t const i);
    std::uint64_t get_length() const;
    bool is_empty() const;
    void push_back(T const elem);
    void push_front(T const elem);
    void pop_back(T const elem);
    void pop_front(T const elem);
    void clean();
  private:
    std::uint64_t length;
    sPtr<Elem<T> > begin;
    sPtr<Elem<T> > end;
  };
}
