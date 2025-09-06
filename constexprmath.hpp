#include <type_traits>
#include <concepts>
#include <array>
#include <algorithm>

/* TODO : RETHINK: 

template<typename T, size_t N>
T median(T (&)[N], char(*)[N % 2 = 0] = 0) { //even
  std::cout<<"even";
}

template<typename T, size_t N>
T median(T (&array)[N], char(*)[N % 2 == 1] = 0) { //odd 
    // 1. Create a sorted copy of "array"
    constexpr T sorted = std::sort(array);
    return sorted[N/2];
    }
    */

namespace cm{
template<typename Container>
concept ArithmeticContainer = requires(Container c) {
    requires !std::is_arithmetic_v<Container>; // Not an arithmetic type itself
    requires requires { c.begin(); c.end(); }; // Has begin/end 
    requires std::is_arithmetic_v<std::decay_t<decltype(*c.begin())>>; 
    };


template<typename ...T>
requires (std::is_arithmetic<T>::value && ...)
constexpr auto sum(T...args){
    return (args + ...);
};


template<ArithmeticContainer Container>
constexpr auto sum(const Container& container) {
    auto result = std::decay_t<decltype(*container.begin())>{};
    for(const auto element : container)
    {
        result+=element;
    }
    return result;
};

template <ArithmeticContainer Container>
constexpr auto abs(const Container& container) {
    auto result = container;
    for (size_t i = 0; i < container.size(); ++i) { 

        if (result[i] < 0) {
            result[i] = -result[i];
        }
    }
    return result;
};


template<typename T>
requires (std::is_arithmetic_v<T>)
constexpr auto abs(const T& number) {
    return number < 0 ? -number : number;
}

   
template<std::size_t size1, std::size_t size2, 
         ArithmeticContainer Container1, ArithmeticContainer Container2>
         //need two ArithmeticContainer Container`s because otherwise compiler wouldnt know which has size1 and which has size2
    constexpr auto dot(const Container1& container1, const Container2& container2) {
    static_assert(size1 == size2, "please enter valid lengths");

    using ResultingType = decltype(container1[0] * container2[0]);
    //i cant just use auto result = 0 as it would be standardized to int, i want the type of the inputs, container1[0] * container2[0] eg double * int = double ResultingType is double
    //NOTE DOWN : AUTO DECAYS TO INT IF NOT DIFERNT DEFINED
    ResultingType result = 0; 
    for(size_t i = 0 ; i < std::size(container1); i++ ) {
        result += container1[i] * container2[i];
    }
    return result;
}


template<typename ...T>
requires (std::is_arithmetic_v<T> && ...)
constexpr double mean(T...args){
    return (args + ...)/static_cast<double>(sizeof...(T)); //sizeof...(T) gives number of types) as int inside of T...args
}
template<ArithmeticContainer Container>
constexpr auto mean(Container container){
    using ReturnType = double;
    ReturnType sum = 0;
    int number_of_elements = 0;


    for(auto n : container){
        sum+= n;
        number_of_elements++;
    }
    return sum/number_of_elements;
}



template<typename ...T>
requires (std::is_arithmetic_v<T> && ...)
constexpr double variance(T... args) {
    using ResultingType = const double;

    ResultingType mean_result = mean(args...); 

     ResultingType sum_sq = (((static_cast<double>(args) - mean_result) *
                            (static_cast<double>(args) - mean_result)) + ...);

    return sum_sq / sizeof...(T);
}
template<ArithmeticContainer Container>
constexpr auto variance(Container container){
    const double mean_result = mean(container); 
    double sum_sq = 0;
    double number_of_elements = 0;

    for(auto n : container){
        sum_sq+=( (n-mean_result) * (n-mean_result) );
            number_of_elements++;
    }
    return sum_sq / number_of_elements;
    }
    
    
        
template<typename T>
requires (std::is_arithmetic_v<T>)
constexpr T min(T value) {
    return value;
}

template<typename T, typename... Ts>
requires (std::is_arithmetic_v<T>)
constexpr auto min(T first, Ts... args) {
    auto rest_min = min(args...);
    return first < rest_min ? first : rest_min;
}
        
template<typename T>
requires (std::is_arithmetic_v<T>)
constexpr T max(T value) {
    return value;
}

template<typename T, typename... Ts>
requires (std::is_arithmetic_v<T>)
constexpr auto max(T first, Ts... args) {
    auto rest_max = max(args...);
    return first > rest_max ? first : rest_max;
}
template<ArithmeticContainer Container>
constexpr auto max(Container container){
    
    using ReturnType = decltype(container[0]);

    ReturnType current = container[0];
    for(const auto& n : container){
        if(n > current){current = n;}
    }
    return current;
}


template<ArithmeticContainer Container>
constexpr auto min(Container container){
    
    using ReturnType = decltype(container[0]);

    ReturnType current = container[0];
    for(const auto& n : container){
        if(n < current){current = n;}
    }
    return current;

}

    
        
        
        
        
    
    
    
    
    
    
    
    
    
    }





