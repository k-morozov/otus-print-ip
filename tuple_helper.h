#pragma once

#include <tuple>

template <class T>
struct is_tuple
{
    static const bool value = false;
};

template <class ... T>
struct is_tuple <std::tuple<T...>>
{
    static const bool value = true;
};

template<class TUPLE_TYPE, size_t... SIZE>
void print_tuple(const TUPLE_TYPE & value, std::index_sequence<SIZE...>)
{
    (..., (std::cout << (SIZE == 0 ? "" : ".") << std::get<SIZE>(value)));
}

template<class... T>
void print_tuple(const std::tuple<T...>& value) 
{
    print_tuple(value, std::make_index_sequence<sizeof...(T)>());
}