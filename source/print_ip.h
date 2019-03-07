#pragma once

#include <string>
#include <stdint.h>
#include <vector>
#include <sstream>
#include <algorithm>
#include <tuple>

// Very usefull and clear article about SFINAE:
// http://scrutator.me/post/2016/12/12/sfinae.aspx

// Checking that type is a container, that has type T:
// 1. has an iterator type
// 2. implements begin() functions, that returns iterator
// 3. implements end() functions, that returns iterator
template<typename T,
         typename IteratorType = typename T::iterator,
         typename BeginType = decltype(std::declval<T>().begin()),
         typename EndType = decltype(std::declval<T>().end()),
         typename = typename std::enable_if<std::is_same<IteratorType, BeginType>::value, void>::type,
         typename = typename std::enable_if<std::is_same<IteratorType, EndType>::value, void>::type>
struct IteratableTriats
{
  static constexpr bool value = true;
};

// For containers.
// It would be easier to use such construction as
// typename = typename T::iterator
// in template header, but I was wonder how to implement something like IteratableTriats
// and how to use in with enable_if
template<typename T>
typename std::enable_if<IteratableTriats<T>::value, std::string>::type
print_ip(T const& ip)
{
  std::stringstream ss;
  for (typename T::const_iterator I = ip.begin(); I != ip.end(); ++I)
  {
    if (I != ip.begin())
      ss << ".";
    ss << static_cast<int>(*I);
  }
  return ss.str();
}

// For integral types
template<typename T>
typename std::enable_if<std::is_integral<T>::value, std::string>::type
print_ip(T ip)
{
  constexpr size_t totalBytes = sizeof(ip);
  std::vector<uint8_t> bytes;
  bytes.reserve(totalBytes);
  // Could be constexpr in C++17
  if /*constexpr*/ (totalBytes > 1) {
    for (size_t i = 0; i < totalBytes; ++i) {
      bytes.push_back(ip & 0xFF);
      ip = ip >> 8;
    }
    std::reverse(bytes.begin(), bytes.end());
  } else {
    bytes.push_back(ip);
  }
  return print_ip(bytes);
}

// For std::string
std::string print_ip(std::string const& ip)
{
  return ip;
}

//========================================================================================
// Далее попытка реализовать случай для tuple
//========================================================================================

// Returns first type from types list T...
template<typename... T>
struct GetHead;

template<typename T>
struct GetHead<T> { using type = T; };

template<typename Head, typename... Tail>
struct GetHead<Head, Tail...> { using type = Head; };

// Check that all types in T... are the same
template<typename... T>
struct IsHomogeneous;

template<typename T>
struct IsHomogeneous<T>
{
  constexpr static bool value = true;
};

template<typename T, typename S>
struct IsHomogeneous<T, S>
{
  constexpr static bool value = std::is_same<T, S>::value;
};

template<typename T, typename... Tail>
struct IsHomogeneous<T, Tail...>
{
  using Head = typename GetHead<Tail...>::type;
  constexpr static bool value =
      IsHomogeneous<T, Head>::value && IsHomogeneous<Tail...>::value;
};


// Printer for tuple
template<class Tuple, std::size_t TupleSize>
struct TuplePrinter;

template<class Tuple>
struct TuplePrinter<Tuple, 1> {
  static void print(std::ostream& out, Tuple const& tuple)
  {
    out << std::get<0>(tuple);
  }
};

template<class Tuple, std::size_t TupleSize>
struct TuplePrinter {
  static void print(std::ostream& out, Tuple const& tuple)
  {
    TuplePrinter<Tuple, TupleSize - 1>::print(out, tuple);
    out << "." << std::get<TupleSize - 1>(tuple);
  }
};

// And finally - print_ip specialization for tuple!
template<typename... T>
typename std::enable_if<IsHomogeneous<T...>::value, std::string>::type
print_ip(std::tuple<T...> const& ip)
{
  std::stringstream ss;
  TuplePrinter<std::tuple<T...>, sizeof...(T)>::print(ss, ip);
  return ss.str();
}
