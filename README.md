
## ConstexprMath
A header-only C++ library providing compile-time mathematical operations that work with both individual arithmetic arguments and containers (like arrays and standard containers).
## Features


-  All functions are `constexpr` and can be evaluated at compile time
-  Support for both variadic arguments and container-based inputs
-  Uses C++20 concepts for compile-time type checking
- 
## Installation

Currently available Functions

## Available Methods
- `sum()` - Calculate the sum of values
- `abs()` - Get absolute values
- `min()` - Find the minimum value
- `max()` - Find the maximum value
- `mean()` - Calculate the arithmetic mean
- `variance()` - Calculate the variance
- `dot()` - Calculate the dot product of two containers   

## Requirements

- C++20 compatible compiler
- Standard Library headers: 
```cpp
<type_traits>, <concepts>, <array>, <algorithm>
```



## Basic Examples
```cpp
    // Using variadic arguments
    constexpr auto s = cm::sum(1, 2, 3, 4, 5);  // Returns 15
    constexpr auto m = cm::mean(1.0, 2.0, 3.0); // Returns 2.0
    constexpr auto mx = cm::max(5, 3, 8, 2);    // Returns 8

    // Using containers
    constexpr std::array<int, 5> arr{1, 2, 3, 4, 5};
    constexpr auto arr_sum = cm::sum(arr);       // Returns 15
    constexpr auto arr_mean = cm::mean(arr);     // Returns 3.0

    // Dot product example
    constexpr std::array<int, 3> a{1, 2, 3};
    constexpr std::array<double, 3> b{1.5, 2.5, 3.5};
    constexpr std::array<double, 4> c{1.5, 2.5, 3.5,3.4};

    constexpr auto dot_result = cm::dot<3, 3>(a, b); // Returns 17.0
    constexpr auto dot_result = cm::dot<3, 4>(a, c); // static assertion 
    static_assert(cm::sum(1, 2, 3) == 6, "Compile-time check");
    //use static_assert to verify compile-time evaluation

```
## Type Requirements
- Variadic functions require all arguments to be arithmetic types

- Container functions require containers that:
    - Have begin() and end() methods
    - Contain arithmetic types
    - Are not arithmetic types themselves
## Supported containers
`std::array`, `std::vector`<br>
(generally speaking std::vector is not a constexpr container, so be carful using it if you want constexpr calculations)

## what i learned
* not all containers can be used at compile time
* basics of concepts type traits
* decltype is useful to give your types custom names
* decay_t can be used to remove constness/refererences
* decay_t is just an alias for accessing the member function std::decay::type
* conexpr calculations
* auto decays to int if not specified differently
* usage of static cast and static assert
* basic usage of variadic templates/fold expressions
