// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <type_traits>

template<typename T>
concept iterator = requires(T t)
{
    t.begin();                    // SR
    t.end();                      // SR
    requires std::is_final_v<T>;  // NR
};

struct A final
{
    void begin();
    void end();
};

struct B
{
    void begin();
    void end();
};

struct C
{
};

static_assert(iterator<A>);
static_assert(not iterator<B>);
static_assert(not iterator<C>);
int main() {}
