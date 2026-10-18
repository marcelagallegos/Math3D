// Copyright (c) Marcela Gallegos
// SPDX-License-Identifier: MIT

#ifndef MATH3D_VEC_HPP
#define MATH3D_VEC_HPP

#include <cassert>
#include <concepts>
#include <cstdint>
#include <math3d/detail/concepts.hpp>
#include <math3d/detail/vec_storage.hpp>
#include <type_traits>

namespace math3d {

template <math3d::detail::scalar T, int N, bool Aligned = false>
    requires(N >= 2 && N <= 4)
struct vec : public detail::vec_storage<T, N, Aligned> {

    using value_type = T;

    constexpr vec() noexcept = default;

    explicit constexpr vec(T s) noexcept {
        for (int i = 0; i < N; ++i) {
            this->data_[i] = s;
        }
    }

    template <typename... Args>
        requires(sizeof...(Args) == N && (std::convertible_to<Args, T> && ...))
    constexpr vec(Args... args) noexcept : detail::vec_storage<T, N, Aligned>{{static_cast<T>(args)...}} {}

    [[nodiscard]] static constexpr int size() noexcept { return N; }

    [[nodiscard]] constexpr T* data() noexcept { return this->data_; }
    [[nodiscard]] constexpr const T* data() const noexcept { return this->data_; }

    [[nodiscard]] constexpr T& operator[](int i) noexcept {
        assert(i >= 0 && i < N && "vec index out of bounds");
        return this->data_[i];
    }

    [[nodiscard]] constexpr const T& operator[](int i) const noexcept {
        assert(i >= 0 && i < N && "vec index out of bounds");
        return this->data_[i];
    }

    [[nodiscard]] constexpr vec operator-() const noexcept
        requires std::is_signed_v<T>
    {
        vec result;
        for (int i = 0; i < N; ++i) {
            result.data_[i] = -this->data_[i];
        }
        return result;
    }

    constexpr vec& operator+=(const vec& v) noexcept {
        for (int i = 0; i < N; ++i) {
            this->data_[i] += v.data_[i];
        }
        return *this;
    }

    constexpr vec& operator-=(const vec& v) noexcept {
        for (int i = 0; i < N; ++i) {
            this->data_[i] -= v.data_[i];
        }
        return *this;
    }

    constexpr vec& operator*=(T s) noexcept {
        for (int i = 0; i < N; ++i) {
            this->data_[i] *= s;
        }
        return *this;
    }

    constexpr vec& operator/=(T s) noexcept {
        assert(s != T{0} && "division by zero in vec operator/=");
        for (int i = 0; i < N; ++i) {
            this->data_[i] /= s;
        }
        return *this;
    }

    [[nodiscard]] friend constexpr vec operator+(vec lhs, const vec& rhs) noexcept { return lhs += rhs; }
    [[nodiscard]] friend constexpr vec operator-(vec lhs, const vec& rhs) noexcept { return lhs -= rhs; }
    [[nodiscard]] friend constexpr vec operator*(vec v, T s) noexcept { return v *= s; }
    [[nodiscard]] friend constexpr vec operator*(T s, vec v) noexcept { return v *= s; }
    [[nodiscard]] friend constexpr vec operator/(vec v, T s) noexcept { return v /= s; }

    [[nodiscard]] friend constexpr bool operator==(const vec& a, const vec& b) noexcept {
        bool is_equal = true;
        for (int i = 0; i < N; ++i) {
            is_equal &= (a.data_[i] == b.data_[i]);
        }
        return is_equal;
    }
};

template <typename T, bool Aligned = false> using vec2 = vec<T, 2, Aligned>;
template <typename T, bool Aligned = false> using vec3 = vec<T, 3, Aligned>;
template <typename T, bool Aligned = false> using vec4 = vec<T, 4, Aligned>;

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

#endif // MATH3D_VEC_HPP
