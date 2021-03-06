/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    variadic.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef FIT_GUARD_FUNCTION_VARIADIC_H
#define FIT_GUARD_FUNCTION_VARIADIC_H

/// variadic
/// ========
/// 
/// Description
/// -----------
/// 
/// The `variadic` function adaptor converts the arguments of the function to a
/// tuple.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     constexpr variadic_adaptor<F> variadic(F f);
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
///     FunctionObject
///     MoveConstructible
/// 

#include <fit/detail/ref_tuple.h>
#include <fit/detail/result_of.h>
#include <fit/always.h>
#include <fit/detail/make.h>
#include <fit/detail/static_const_var.h>

namespace fit {

template<class F>
struct variadic_adaptor : F
{
    typedef variadic_adaptor fit_rewritable1_tag;
    template<class... Ts>
    constexpr variadic_adaptor(Ts && ... x) : F(fit::forward<Ts>(x)...)
    {}

    template<class... Ts>
    constexpr const F& base_function(Ts&&... xs) const
    {
        return always_ref(*this)(xs...);
    }

    FIT_RETURNS_CLASS(variadic_adaptor);

    template<class... Ts>
    constexpr FIT_SFINAE_RESULT(const F&, id_<std::tuple<typename detail::remove_rvalue_reference<Ts>::type...>>) 
    operator()(Ts && ... xs) const FIT_SFINAE_RETURNS
    (
        FIT_MANGLE_CAST(const F&)(FIT_CONST_THIS->base_function(xs...))(detail::make_ref_tuple(fit::forward<Ts>(xs)...))
    );
};

FIT_DECLARE_STATIC_VAR(variadic, detail::make<variadic_adaptor>);

}

#endif
