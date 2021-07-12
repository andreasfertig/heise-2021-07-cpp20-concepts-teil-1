// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if __has_include(<ranges>)
#include <algorithm>
#include <concepts>
#include <type_traits>

template<typename T>
concept iterator = requires(T t)
{
    t.begin();                    // SR
    t.end();                      // SR
    requires std::is_final_v<T>;  // NR

    {
        t.begin()
    }
    noexcept;  // CR 1

    {
        t.begin()
        } -> std::same_as<decltype(t.end())>;  // CR 2

    {
        t.begin()
    }
    noexcept->std::same_as<decltype(t.end())>;  // CR 3
};

template<typename T>
requires iterator<T>
void Fill(T& t, int value)
{
    std::ranges::for_each(t, [value](auto& e) { e = value; });
}

struct A final
{
    int data[5]{};

    int* begin() noexcept { return data; }
    int* end() noexcept { return data + sizeof(data); }
};

int main()
{
    A a{};

    Fill(a, 4);
}
#else
int main()
{
#pragma message("not supported")
}
#endif