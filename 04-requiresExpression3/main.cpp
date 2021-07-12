// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <string>

struct A
{
    using Int = int;
};

namespace MySpace {
    using Int = int;
}

template<typename T>
concept TypeCheck = requires(T t)
{
    typename MySpace::Int;
    typename T::Int;
};

struct B
{
};

static_assert(TypeCheck<A>);
static_assert(not TypeCheck<B>);

int main() {}