// Copyright (c) Marcela Gallegos
// SPDX-License-Identifier: MIT

#ifndef MATH3D_GEOMETRIC_HPP
#define MATH3D_GEOMETRIC_HPP

#include "vec.hpp"
#include <cmath>
#include <concepts>

namespace math3d {

template <typename T, int N, bool Aligned>
[[nodiscard]] constexpr T dot(const vec<T, N, Aligned>& a, const vec<T, N, Aligned>& b) noexcept {
    T sum{};
    for (int i = 0; i < N; ++i) {
        sum += a[i] * b[i];
    }
    return sum;
}

// clang-format off
template <typename T, bool Aligned>
[[nodiscard]] constexpr vec<T, 3, Aligned> cross(const vec<T, 3, Aligned>& a, const vec<T, 3, Aligned>& b) noexcept {
    return {
        a[1] * b[2] - b[1] * a[2],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - b[0] * a[1]
    };
}
// clang-format on

template <typename T, int N, bool Aligned>
[[nodiscard]] constexpr T length_sq(const vec<T, N, Aligned>& v) noexcept {
    return dot(v, v);
}

template <std::floating_point T, int N, bool Aligned>
[[nodiscard]] T length(const vec<T, N, Aligned>& v) noexcept {
    return std::sqrt(length_sq(v));
}

template <std::floating_point T, int N, bool Aligned>
[[nodiscard]] vec<T, N, Aligned> normalize(const vec<T, N, Aligned>& v) noexcept {
    return v * (T{1} / length(v));
}

} // namespace math3d

#endif // MATH3D_GEOMETRIC_HPP
