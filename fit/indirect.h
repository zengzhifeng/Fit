/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    indirect.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef FIT_GUARD_FUNCTION_INDIRECT_H
#define FIT_GUARD_FUNCTION_INDIRECT_H

/// indirect
/// ========
/// 
/// Description
/// -----------
/// 
/// The `indirect` function adaptor dereferences the object before calling it.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     constexpr indirect_adaptor<F> indirect(F f);
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
///     FunctionObject
///     MoveConstructible
///     Dereferenceable
/// 
/// Example
/// -------
/// 
///     struct sum
///     {
///         template<class T>
///         T sum(T x, T y)
///         {
///             return x+y;
///         }
///     };
/// 
///     int r = indirect(std::make_unique<sum>())(3,2);
///     assert(r, 5);
/// 

#include <fit/detail/delegate.h>
#include <fit/returns.h>
#include <fit/always.h>

namespace fit {

template<class F>
struct indirect_adaptor : F
{
    FIT_INHERIT_CONSTRUCTOR(indirect_adaptor, F);

    template<class... Ts>
    constexpr const F& base_function(Ts&&... xs) const
    {
        return always_ref(*this)(xs...);
    }

    template<class... Ts>
    constexpr auto operator()(Ts&&... xs) const FIT_RETURNS
    (
        (*this->base_function(xs...))(std::forward<Ts>(xs)...)
    );
};

template<class F>
constexpr indirect_adaptor<F> indirect(F f)
{
    return indirect_adaptor<F>(std::move(f));
}


}

#endif