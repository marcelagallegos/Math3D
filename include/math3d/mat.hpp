// Copyright (c) Marcela Gallegos
// SPDX-License-Identifier: MIT

#ifndef MATH3D_MAT_HPP
#define MATH3D_MAT_HPP

#include "detail/concepts.hpp"
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

    col_type cols_[N];
};

} // namespace math3d

#endif // MATH3D_MAT_HPP
