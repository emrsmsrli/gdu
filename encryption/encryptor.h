//
// Created by Emre Şimşirli on 2019-04-29.
//

#ifndef UNTITLED_ENCRYPTOR_H
#define UNTITLED_ENCRYPTOR_H

#include "../rand.h"
#include "../bytes.h"

template<typename T> class encrypted;

template<typename T, typename Enable = void>
class encryptor
{
    friend class encrypted<T>;

    T encryption_key = random<T>();
    encryptor() = default;

public:
    T encrypt(T data) const { return (data ^ encryption_key) - encryption_key; }
    T decrypt(T data) const { return (data + encryption_key) ^ encryption_key; }
};

template<typename T>
class encryptor<T, std::enable_if_t<is_string_v<T>>>
{
    friend class encrypted<T>;

    unsigned char encryption_key = random<unsigned char>();
    encryptor() = default;

public:
    T encrypt(T data) const
    {
        std::for_each(data.begin(), data.end(), [&](char &c) { return c ^= encryption_key; });
        std::reverse(data.begin(), data.end());
        return data;
    }

    T decrypt(T data) const { return encrypt(data); }
};

template<typename T>
class encryptor<T, std::enable_if_t<std::is_floating_point_v<T>>>
{
    friend class encrypted<T>;

    T encryption_key = random<T>();
    encryptor() = default;

public:
    T encrypt(T data) const
    {
        bytes<T> f(data);
        bytes<T> encrypted;

        const auto size = f.size();
        for(size_t i = 0; i < size; ++i) {
            encrypted[i] = ~f[size - 1 - i];
        }

        return encrypted;
    }

    T decrypt(T data) const { return encrypt(data); }
};

#endif //UNTITLED_ENCRYPTOR_H
