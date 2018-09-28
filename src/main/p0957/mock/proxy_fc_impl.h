/**
 * Copyright (c) 2017-2018 Mingxin Wang. All rights reserved.
 */

#ifndef SRC_MAIN_P0957_MOCK_PROXY_FC_IMPL_H_
#define SRC_MAIN_P0957_MOCK_PROXY_FC_IMPL_H_

#include "./proxy_fa_impl.h"
#include "./proxy_fb_impl.h"

/**
 * facade FC : FA, FB {
 *   void fun_c();
 * };
 */

struct FC;

namespace std {

template <template <bool, bool> class E>
struct facade_meta_t<FC, E> : facade_meta_t<FA, E>, facade_meta_t<FB, E> {
  template <class, class>
  friend class proxy;

 public:
  template <class T>
  explicit constexpr facade_meta_t(in_place_type_t<T>)
      : facade_meta_t<FA, E>(in_place_type<T>),
        facade_meta_t<FB, E>(in_place_type<T>), fc_op_0_(fc_op_0<T>) {}

  facade_meta_t() = default;
  constexpr facade_meta_t(const facade_meta_t&) = default;

 private:
  template <class T>
  static void fc_op_0(E<false, false> erased) {
    erased.cast(in_place_type<T>).fun_c();
  }

  void (*fc_op_0_)(E<false, false>);
};

template <class A>
class proxy<FC, A> : public A {
 public:
  proxy() : A() {}

  proxy(null_proxy_t) : A() {}

  proxy(const proxy&) = default;

  template <class _F, class _A>
  proxy(const proxy<_F, _A>& rhs) : A(static_cast<const _A&>(rhs)) {}

  proxy(proxy&&) = default;

  template <class _F, class _A>
  proxy(proxy<_F, _A>&& rhs) : A(static_cast<_A&&>(rhs)) {}

  template <class T, class = enable_if_t<!is_proxy_v<decay_t<T>>>>
  proxy(T&& value) : proxy(in_place_type<decay_t<T>>, forward<T>(value)) {}

  template <class T, class U, class... _Args,
            class = enable_if_t<is_same_v<T, decay_t<T>>>>
  explicit proxy(in_place_type_t<T>, initializer_list<U> il, _Args&&... args)
      : A(in_place_type<T>, il, forward<_Args>(args)...) {}

  template <class T, class... _Args,
            class = enable_if_t<is_same_v<T, decay_t<T>>>>
  explicit proxy(in_place_type_t<T>, _Args&&... args)
      : A(in_place_type<T>, forward<_Args>(args)...) {}

  proxy& operator=(null_proxy_t) {
    A::reset();
    return *this;
  }

  template <class T, class = enable_if_t<!is_proxy_v<decay_t<T>>>>
  proxy& operator=(T&& value) {
    A::reset(forward<T>(value));
    return *this;
  }

  proxy& operator=(const proxy& rhs) = default;

  template <class _F, class _A>
  proxy& operator=(const proxy<_F, _A>& rhs) {
    static_cast<A&>(*this) = static_cast<const _A&>(rhs);
    return *this;
  }

  proxy& operator=(proxy&& rhs) = default;

  template <class _F, class _A>
  proxy& operator=(proxy<_F, _A>&& rhs) {
    static_cast<A&>(*this) = static_cast<_A&&>(rhs);
    return *this;
  }

  void fun_a_0() {
    const A& a = static_cast<const A&>(*this);
    a.meta().fa_op_0_(a.data());
  }

  int fun_a_1(double arg_0) {
    const A& a = static_cast<const A&>(*this);
    return a.meta().fa_op_1_(a.data(), forward<double>(arg_0));
  }

  void fun_b(value_proxy<FA> arg_0) {
    const A& a = static_cast<const A&>(*this);
    a.meta().fb_op_0_(forward<value_proxy<FA>>(arg_0));
  }

  void fun_c() {
    const A& a = static_cast<const A&>(*this);
    a.meta().fc_op_0_(a.data());
  }
};

}  // namespace std

#endif  // SRC_MAIN_P0957_MOCK_PROXY_FC_IMPL_H_
