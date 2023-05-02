//*****************************************************************************
// Copyright (c) 2023, Intel Corporation
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// - Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// - Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
// THE POSSIBILITY OF SUCH DAMAGE.
//*****************************************************************************

#pragma once

#include <type_traits>

namespace dpnp
{
namespace backend
{
namespace ext
{
namespace lapack
{
namespace types
{
// TODO: to remove, will be provided by dpctl tensor headers
template <typename Ty1, typename ArgTy1, typename Ty2 = Ty1, typename ArgTy2 = ArgTy1>
struct TypePairEntry : std::bool_constant<std::conjunction_v<std::is_same<Ty1, ArgTy1>, std::is_same<Ty2, ArgTy2>>>
{
    static constexpr bool is_defined = true;
};


// TODO: to remove, will be provided by dpctl tensor headers
struct NotFoundEntry : std::true_type
{
    static constexpr bool is_defined = false;
};

/**
 * @brief A factory to define pairs of supported types for which
 * MKL LAPACK library provides support in oneapi::mkl::lapack::heevd<T, RealT> function.
 *
 * @tparam T Type of array containing input matrix A and an output array with eigenvectors.
 * @tparam RealT Type of output array containing eigenvalues of A.
 */
template <typename T, typename RealT>
struct HeevdTypePairSupportFactory
{
    static constexpr bool is_defined = std::disjunction<TypePairEntry<T, std::complex<double>, RealT, double>,
                                                        TypePairEntry<T, std::complex<float>, RealT, float>,
                                                        // fall-through
                                                        NotFoundEntry>::is_defined;
};

/**
 * @brief A factory to define pairs of supported types for which
 * MKL LAPACK library provides support in oneapi::mkl::lapack::syevd<T> function.
 *
 * @tparam T Type of array containing input matrix A and an output arrays with eigenvectors and eigenvectors.
 */
template <typename T>
struct SyevdTypePairSupportFactory
{
    static constexpr bool is_defined = std::disjunction<TypePairEntry<T, double>,
                                                        TypePairEntry<T, float>,
                                                        // fall-through
                                                        NotFoundEntry>::is_defined;
};
}
}
}
}
}