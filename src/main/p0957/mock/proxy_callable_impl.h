/**
 * Copyright (c) 2017-2018 Mingxin Wang. All rights reserved.
 */

#ifndef SRC_MAIN_P0957_MOCK_PROXY_CALLABLE_IMPL_H_
#define SRC_MAIN_P0957_MOCK_PROXY_CALLABLE_IMPL_H_

/**
 * template <class T>
 * facade Callable;  // undefined
 *
 * template <class R, class... Args>
 * facade Callable<R(Args...)> {
 *   R operator()(Args...);
 * };
 */

template <class>
struct Callable;

namespace std {

template <class R, class... Args, template <bool, bool> class E>
struct facade_meta_t<Callable<R(Args...)>, E> {
  template <class, class>
  friend class proxy;

 public:
  template <class T>
  constexpr explicit facade_meta_t(in_place_type_t<T>)
      : callable_op_0_(callable_op_0<T>) {}

  facade_meta_t() = default;
  constexpr facade_meta_t(const facade_meta_t&) = default;

 private:
  template <class T>
  static R callable_op_0(E<false, false> erased, Args&&... args) {
    return erased.cast(in_place_type<T>)(forward<Args>(args)...);
  }

  R (*callable_op_0_)(E<false, false>, Args&&...);
};

template <class... Args, template <bool, bool> class E>
struct facade_meta_t<Callable<void(Args...)>, E> {
  template <class, class>
  friend class proxy;

 public:
  template <class T>
  constexpr explicit facade_meta_t(in_place_type_t<T>)
      : callable_op_0_(callable_op_0<T>) {}

  facade_meta_t() = default;
  constexpr facade_meta_t(const facade_meta_t&) = default;

 private:
  template <class T>
  static void callable_op_0(E<false, false> erased, Args&&... args) {
    erased.cast(in_place_type<T>)(forward<Args>(args)...);
  }

  void (*callable_op_0_)(E<false, false>, Args&&...);
};

template <class R, class... Args, class A>
class proxy<Callable<R(Args...)>, A> : public A {
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

  R operator()(Args... args) {
    const A& a = static_cast<const A&>(*this);
    return a.meta().callable_op_0_(a.data(), forward<Args>(args)...);
  }
};

}  // namespace std

#endif  // SRC_MAIN_P0957_MOCK_PROXY_CALLABLE_IMPL_H_
