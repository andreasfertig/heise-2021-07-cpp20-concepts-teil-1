// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#include <vector>

template<typename T>
concept iterator = requires(T t)
{
    t.begin();  // SR
    t.end();    // SR
};

struct A
{
};

static_assert(iterator<std::vector<int>>);
static_assert(not iterator<A>);
int main() {}
