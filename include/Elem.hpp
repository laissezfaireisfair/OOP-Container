#pragma once
#include <memory>

namespace Bicycle{
  using wPtr<T> = std::weak_ptr<T>;
  using sPtr<T> = std::shared_ptr<T>;

  template <class T> class Elem{
  public:
    T get_value() const;
    void set_value(T const value);
    wPtr<Elem<T> > get_ptr_to_next() const;
    wPtr<Elem<T> > get_ptr_to_prev() const;
    void set_ptr_to_next(wPtr<Elem<T> > const ptr);
    void set_ptr_to_prev(wPtr<Elem<T> > const ptr);
  private:
    T value;
    sPtr<Elem<T> > ptrNext;
    sPtr<Elem<T> > ptrPrev;
  };
