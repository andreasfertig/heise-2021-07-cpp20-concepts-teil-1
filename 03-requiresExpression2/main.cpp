// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

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

struct Valid final
{
    void begin() noexcept;
    void end() noexcept;
};

struct MissingFinal
{
    void begin();
    void end();
};

struct Empty
{
};

struct MissingNoexcept final
{
    void begin();
    void end();
};

struct DiffReturnType final
{
    void begin() noexcept;
    int  end() noexcept;
};

static_assert(iterator<Valid>);
static_assert(not iterator<MissingFinal>);
static_assert(not iterator<Empty>);
static_assert(not iterator<MissingNoexcept>);
static_assert(not iterator<DiffReturnType>);

int main() {}