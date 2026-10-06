// Copyright (c) Marcela Gallegos
// SPDX-License-Identifier: MIT

#ifndef MATH3D_TVEC_HPP
#define MATH3D_TVEC_HPP

#include "detail/concepts.hpp"
#include "detail/vec_storage.hpp"
#include <cassert>
#include <concepts>
#include <cstdint>
#include <type_traits>

namespace math3d {

template <math3d::detail::scalar T, int N, bool Aligned = false>
    requires(N >= 2 && N <= 4)
struct vec : public detail::vec_storage<T, N, Aligned> {

    using value_type = T;
    using arg_type = std::conditional_t<(sizeof(T) * N <= 16), vec, const vec&>;

    constexpr vec() noexcept = default;

    explicit constexpr vec(T s) noexcept {
        for (int i = 0; i < N; ++i) {
            this->data[i] = s;
        }
    }

    template <typename... Args>
        requires(sizeof...(Args) == N && (std::convertible_to<Args, T> && ...))
    constexpr vec(Args... args) noexcept : detail::vec_storage<T, N, Aligned>{{static_cast<T>(args)...}} {}

    [[nodiscard]] static constexpr int size() noexcept { return N; }

    [[nodiscard]] constexpr T& operator[](int i) noexcept {
        assert(i >= 0 && i < N && "vec index out of bounds");
        return this->data[i];
    }

    [[nodiscard]] constexpr const T& operator[](int i) const noexcept {
        assert(i >= 0 && i < N && "vec index out of bounds");
        return this->data[i];
    }

    [[nodiscard]] constexpr vec operator-() const noexcept
        requires std::is_signed_v<T>
    {
        vec result;
        for (int i = 0; i < N; ++i) {
            result.data[i] = -this->data[i];
        }
        return result;
    }

    constexpr vec& operator+=(arg_type v) noexcept {
        for (int i = 0; i < N; ++i) {
            this->data[i] += v.data[i];
        }
        return *this;
    }

    constexpr vec& operator-=(arg_type v) noexcept {
        for (int i = 0; i < N; ++i) {
            this->data[i] -= v.data[i];
        }
        return *this;
    }

    constexpr vec& operator*=(T s) noexcept {
        for (int i = 0; i < N; ++i) {
            this->data[i] *= s;
        }
        return *this;
    }

    constexpr vec& operator/=(T s) noexcept {
        for (int i = 0; i < N; ++i) {
            this->data[i] /= s;
        }
        return *this;
    }

    [[nodiscard]] friend constexpr vec operator+(vec lhs, arg_type rhs) noexcept { return lhs += rhs; }
    [[nodiscard]] friend constexpr vec operator-(vec lhs, arg_type rhs) noexcept { return lhs -= rhs; }
    [[nodiscard]] friend constexpr vec operator*(vec v, T s) noexcept { return v *= s; }
    [[nodiscard]] friend constexpr vec operator*(T s, vec v) noexcept { return v *= s; }
    [[nodiscard]] friend constexpr vec operator/(vec v, T s) noexcept { return v /= s; }

    [[nodiscard]] friend constexpr bool operator==(arg_type a, arg_type b) noexcept {
        bool is_equal = true;
        for (int i = 0; i < N; ++i) {
            is_equal &= (a.data[i] == b.data[i]);
        }
        return is_equal;
    }
};

template <typename T> using vec2 = vec<T, 2>;
template <typename T> using vec3 = vec<T, 3>;
template <typename T> using vec4 = vec<T, 4>;

using vec2f = vec2<float>;
using vec3f = vec3<float>;
using vec4f = vec4<float>;

using vec2d = vec2<double>;
using vec3d = vec3<double>;
using vec4d = vec4<double>;

using vec2i = vec2<int32_t>;
using vec3i = vec3<int32_t>;
using vec4i = vec4<int32_t>;

} // namespace math3d

#endif // MATH3D_TVEC_HPP
