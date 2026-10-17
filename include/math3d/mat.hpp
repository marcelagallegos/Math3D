// Copyright (c) Marcela Gallegos
// SPDX-License-Identifier: MIT

#ifndef MATH3D_MAT_HPP
#define MATH3D_MAT_HPP

#include "detail/concepts.hpp"
#include "geometric.hpp"
#include "vec.hpp"
#include <cassert>

namespace math3d {

template <math3d::detail::scalar T, int N, int M, bool Aligned = false>
    requires(N >= 2 && N <= 4 && M >= 2 && M <= 4)
struct mat {
    using value_type = T;
    using col_type = vec<T, M, Aligned>;
    using row_type = vec<T, N, Aligned>;

    constexpr mat() noexcept = default;

    explicit constexpr mat(T s) noexcept {
        for (int col = 0; col < N; ++col) {
            for (int row = 0; row < M; ++row) {
                cols_[col].data_[row] = (col == row ? s : T{0});
            }
        }
    }

    [[nodiscard]] constexpr T* data() noexcept { return cols_[0].data(); }
    [[nodiscard]] constexpr const T* data() const noexcept { return cols_[0].data(); }

    [[nodiscard]] constexpr col_type& operator[](int col) noexcept {
        assert(col >= 0 && col < N && "mat index out of bounds");
        return cols_[col];
    }

    [[nodiscard]] constexpr const col_type& operator[](int col) const noexcept {
        assert(col >= 0 && col < N && "mat index out of bounds");
        return cols_[col];
    }

    constexpr mat& operator*=(T s) noexcept {
        for (int col = 0; col < N; ++col) {
            cols_[col] *= s;
        }
        return *this;
    }

    [[nodiscard]] friend constexpr mat operator*(mat m, T s) noexcept { return m *= s; }
    [[nodiscard]] friend constexpr mat operator*(T s, mat m) noexcept { return m *= s; }

    [[nodiscard]] friend constexpr col_type operator*(const mat& m, const row_type& v) noexcept {
        col_type result = m.cols_[0] * v.data_[0];
        for (int col = 1; col < N; ++col) {
            result += m.cols_[col] * v.data_[col];
        }
        return result;
    }

    [[nodiscard]] friend constexpr row_type operator*(const col_type& v, const mat& m) noexcept {
        row_type result;
        for (int col = 0; col < N; ++col) {
            result.data_[col] = dot(m.cols_[col], v);
        }
        return result;
    }

    friend constexpr col_type& operator*=(col_type& v, const mat& m) noexcept
        requires(N == M)
    {
        return v = v * m;
    }

    constexpr mat& operator*=(const mat<T, N, N, Aligned>& m) noexcept { return *this = *this * m; }

    // clang-format off
    template <int P>
        requires(P >= 2 && P <= 4)
    [[nodiscard]] friend constexpr mat<T, P, M, Aligned> operator*(const mat& lhs, const mat<T, P, N, Aligned>& rhs) noexcept {
        mat<T, P, M, Aligned> result;
        for (int col = 0; col < P; ++col) {
            result.cols_[col] = lhs * rhs.cols_[col];
        }
        return result;
    }
    // clang-format on

    col_type cols_[N];
};

template <typename T, bool Aligned = false> using mat2 = mat<T, 2, 2, Aligned>;
template <typename T, bool Aligned = false> using mat3 = mat<T, 3, 3, Aligned>;
template <typename T, bool Aligned = false> using mat4 = mat<T, 4, 4, Aligned>;

using mat2f = mat2<float>;
using mat3f = mat3<float>;
using mat4f = mat4<float>;

using mat2d = mat2<double>;
using mat3d = mat3<double>;
using mat4d = mat4<double>;

using mat2i = mat2<int32_t>;
using mat3i = mat3<int32_t>;
using mat4i = mat4<int32_t>;

} // namespace math3d

#endif // MATH3D_MAT_HPP
