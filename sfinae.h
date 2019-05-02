//
// Created by Emre Şimşirli on 2019-04-08.
//

#ifndef UNTITLED_SFINAE_H
#define UNTITLED_SFINAE_H

#include <type_traits>

template<typename T> struct is_bool       : std::false_type {};
template<>           struct is_bool<bool> : std::true_type {};

template<typename T> constexpr inline const bool is_bool_v = is_bool<T>::value;

template<typename T> struct is_string       : std::false_type {};
template<>           struct is_string<std::string> : std::true_type {};

template<typename T> constexpr inline const bool is_string_v = is_string<T>::value;

#endif //UNTITLED_SFINAE_H
