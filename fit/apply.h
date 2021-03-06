/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    apply.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef FIT_GUARD_APPLY_H
#define FIT_GUARD_APPLY_H

/// apply
/// =====
/// 
/// Description
/// -----------
/// 
/// The `apply` function calls the function given to it with its arguments.
/// 
/// Synopsis
/// --------
/// 
///     template<class F, class... Ts>
///     constexpr auto apply(F&& f, Ts&&... xs);
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
///     FunctionObject
/// 
/// Example
/// -------
/// 
///     struct sum_f
///     {
///         template<class T, class U>
///         T operator()(T x, U y) const
///         {
///             return x+y;
///         }
///     };
///     assert(fit::apply(sum_f(), 1, 2) == 3);
/// 

#include <fit/detail/result_of.h>
#include <fit/detail/forward.h>
#include <fit/detail/static_const_var.h>

namespace fit {

namespace detail {

struct apply_f
{
    template<class F, class... Ts>
    constexpr FIT_SFINAE_RESULT(F, id_<Ts>...) operator()(F&& f, Ts&&... xs) const FIT_SFINAE_RETURNS
    (
        f(fit::forward<Ts>(xs)...)
    );
};

}

FIT_DECLARE_STATIC_VAR(apply, detail::apply_f);

}

#endif
