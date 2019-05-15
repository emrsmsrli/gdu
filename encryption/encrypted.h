
#ifndef UNTITLED_ENCRYPTED_H
#define UNTITLED_ENCRYPTED_H

#include <string>
#include "encryptor.h"

template<typename T>
T encrypt(const encryptor<T>& encryptor, T data) { return encryptor.encrypt(data); }
template<typename T>
T decrypt(const encryptor<T>& encryptor, T data) { return encryptor.decrypt(data); }

template<typename T>
class encrypted
{
    static_assert(std::is_arithmetic_v<T>, "only built-in types are supported");

public:
    encrypted() : encrypted(0) {}
    encrypted(T data) { set(data); }
    encrypted(const encrypted<T>& other) { set(other); }
    encrypted(encrypted<T>&& other) noexcept = default;

    void set(T data) { data_ = encrypt(encryptor_, data); }
    T get() const { return decrypt(encryptor_, data_); }
    T get_encrypted() const { return data_; }

    operator T() const { return get(); }

    encrypted<T>& operator=(T data) { set(data); return *this; }
    encrypted<T>& operator=(const encrypted<T>& other) { set(other); return *this; }
    encrypted<T>& operator=(encrypted<T>&& other) noexcept = default;

    encrypted<T> operator+(T other) const { return get() + other; }
    encrypted<T> operator-(T other) const { return get() - other; }
    encrypted<T> operator*(T other) const { return get() * other; }
    encrypted<T> operator/(T other) const { return other == 0 ? 0 : get() / other; }

    encrypted<T>& operator+=(T other) { set(get() + other); return *this; }
    encrypted<T>& operator-=(T other) { set(get() - other); return *this; }
    encrypted<T>& operator*=(T other) { set(get() * other); return *this; }
    encrypted<T>& operator/=(T other) { set(other == 0 ? 0 : get() / other); return *this; }

    encrypted<T>& operator++()
    {
        check_integral();
        *this += 1;
        return *this;
    }

    encrypted<T> operator++(int) const
    {
        check_integral();
        auto temp = *this;
        *this += 1;
        return temp;
    }

    encrypted<T>& operator--()
    {
        check_integral();
        *this -= 1;
        return *this;
    }

    encrypted<T> operator--(int) const
    {
        check_integral();
        auto temp = *this;
        *this -= 1;
        return temp;
    }

private:
    encryptor<T> encryptor_;
    T data_;

    void check_integral() const { static_assert(std::is_integral_v<T>, "floating points are not supported"); }
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, const encrypted<T>& e) { return stream << e.get(); }
template<typename T>
bool operator==(const encrypted<T>& e1, const encrypted<T>& e2) { return e1.get() == e2.get(); }
template<typename T>
bool operator!=(const encrypted<T>& e1, const encrypted<T>& e2) { return !(e1 == e2); }

/********************************************************/

template<>
class encrypted<std::string>
{
public:
    encrypted() : encrypted("") {}
    encrypted(const std::string& data) { set(data); }
    encrypted(const char* data) { set(data); }
    encrypted(const encrypted<std::string>& other) { set(other); }
    encrypted(encrypted<std::string>&& other) noexcept = default;

    void set(const std::string& data) { data_ = encrypt(encryptor_, data); }
    std::string get() const { return decrypt(encryptor_, data_); }
    const std::string& get_encrypted() const { return data_; }

    operator std::string() const { return get(); }

    encrypted<std::string>& operator=(const std::string& data) { set(data); return *this; }
    encrypted<std::string>& operator=(const char* data) { set(data); return *this; }
    encrypted<std::string>& operator=(const encrypted<std::string>& other) { set(other); return *this; }
    encrypted<std::string>& operator=(encrypted<std::string>&& other) noexcept = default;

    encrypted<std::string> operator+(const std::string& data) { return get() + data; }
    encrypted<std::string> operator+(const char* data) { return get() + data; }

    encrypted<std::string>& operator+=(const std::string& data) { set(get() + data); return *this; }
    encrypted<std::string>& operator+=(const char* data) { set(get() + data); return *this; }

private:
    encryptor<std::string> encryptor_;
    std::string data_;
};

#endif //UNTITLED_ENCRYPTED_H
