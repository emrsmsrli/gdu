
#ifndef UNTITLED_RANGE_H
#define UNTITLED_RANGE_H

/**
 * represents a range for enhanced for loop usage
 * instead of using
 * \code for(int i = 0; i &lt; 5; ++i) \endcode
 * it can be used
 * \code for(const auto& i : range(0, 5)) \endcode
 *
 * @tparam T an integral type of range
 * @warning checking the relation between high and
 * low \code hi &lt; lo etc... \endcode is the responsibility of the programmer
 *
 * @example
 * \code
 * for(const auto& i : range(0, 6)) {}
 * for(const auto& c : range('A', 'Z', true)) {}
 * \endcode
 */
template<typename T>
class range {
    static_assert(std::is_integral_v<T>, "only integral types are supported");
    
    T lo;
    T hi;

public:
    class range_iter {
        T current;

    public:
        constexpr explicit range_iter(T current) : current(current) {}
        constexpr const T& operator*() const { return current; }

        constexpr bool operator==(const range_iter& other) { return current == other.current; }
        constexpr bool operator!=(const range_iter& other) { return current != other.current; }
        constexpr range_iter& operator++() { current++; return *this; }
    };

    constexpr explicit range(T hi, bool inclusive = false) : range(0, hi, inclusive) {}
    constexpr range(T lo, T hi, bool inclusive = false) : lo(lo), hi(inclusive ? hi + 1 : hi) {}

    constexpr range_iter begin() { return range_iter(low()); }
    constexpr range_iter end() { return range_iter(high()); }

    /**
     * checks whether value is in range [lo, hi) --- [lo, hi] if inclusive == true
     * @param value value to check
     * @return true if is in range, false otherwise
     */
    constexpr bool contains(T value) { return low() <= value && value < high(); }

    constexpr T low() { return lo; }
    constexpr T high() { return hi; }
};

#endif //UNTITLED_RANGE_H
