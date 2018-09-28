/**
 * Copyright (c) 2017-2018 Mingxin Wang. All rights reserved.
 */

#ifndef SRC_MAIN_P1144_TRIVIALLY_RELOCATABLE_H_
#define SRC_MAIN_P1144_TRIVIALLY_RELOCATABLE_H_

#include <type_traits>

namespace std {

template <class T>
struct is_trivially_relocatable : bool_constant<
  is_trivially_move_constructible_v<T> &&
  is_trivially_destructible_v<T>
> {};
template <class T>
inline constexpr bool is_trivially_relocatable_v =
    is_trivially_relocatable<T>::value;

}  // namespace std

#endif  // SRC_MAIN_P1144_TRIVIALLY_RELOCATABLE_H_
