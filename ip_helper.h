#pragma once

#include <type_traits>
#include <vector>
#include <list>
#include "tuple_helper.h"


template<class T, class Enable = void>
class IP 
{
    static constexpr void print(T && value) 
    {
        std::cout << "Base type" << "\n";
    }
};

template <class T>
struct IP<T, typename std::enable_if<std::is_integral<T>::value>::type> 
{
    static constexpr void print(T && value) 
    {
        using unsigned_t = typename std::make_unsigned<T>::type;
        const std::size_t bytes = sizeof(T);
        for(std::size_t i=0; i<bytes; ++i)
        {
            unsigned offset = ((bytes - 1) - i) * 8;
            std::cout << (i != 0 ? "." : "") << ((value & (static_cast<unsigned_t>(0xFF) << offset)) >> offset);
        }
        std::cout << std::endl;
    }
};


template <class T>
struct IP<T, typename std::enable_if<is_tuple<T>::value>::type> 
{
    static constexpr void print(T && value) 
    {
        print_tuple(value);
        std::cout << std::endl;
    }
};

template <class T>
struct IP<T, typename std::enable_if<
    std::is_same<std::vector<typename T::value_type>,T>::value>::type> 
{
    static constexpr void print(T && value) 
    {
        for(auto it = value.cbegin(); it!=value.cend(); ++it)
        {
            std::cout << ( it!=value.cbegin() ? "." : "") << *it;
        }
        std::cout << std::endl;
    }
};

template <class T>
struct IP<T, typename std::enable_if<
    std::is_same<std::list<typename T::value_type>, T>::value>::type> 
{
    static constexpr void print(T && value) 
    {
        for(auto it = value.cbegin(); it!=value.cend(); ++it)
        {
            std::cout << ( it!=value.cbegin() ? "." : "") << *it;
        }
        std::cout << std::endl;
    }
};

template <class T>
struct IP<T, typename std::enable_if<
    std::is_same<std::string, T>::value>::type> 
{
    static constexpr void print(T && value) 
    {
        std::cout << value << std::endl;
    }
};