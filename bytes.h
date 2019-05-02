//
// Created by Emre Şimşirli on 2019-04-01.
//

#ifndef UNTITLED_BYTES_H
#define UNTITLED_BYTES_H

/**
 * parses the bytes of a given arithmetic value
 *
 * @tparam T an arithmetic type
 */
template<typename T>
union bytes {
    static_assert(std::is_arithmetic_v<T>, "only built-in types are supported");

    constexpr bytes() = default;
    constexpr explicit bytes(T t) : value(t) {}

    constexpr operator T() const { return value; }
    constexpr unsigned char& operator[](unsigned long i) { return bytes_[i]; }
    constexpr const unsigned char& operator[](unsigned long i) const { return bytes_[i]; }

    constexpr size_t size() const { return sizeof(T); }

private:
    T value;
    unsigned char bytes_[sizeof(T)];
};

#endif //UNTITLED_BYTES_H
