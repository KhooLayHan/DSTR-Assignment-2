#pragma once

#include <cassert>
#include <iostream>
#include <utility>

namespace TCMS
{
    class Assert {
    public:
        // Compile-time assertion using static_assert
        template <bool Condition>
        static constexpr void compiletimeAssert(const char* message = "Compile-time Assertion Failed") {
            static_assert(Condition, "Compile-time Assertion Failed");
        }

        // Run-time assertion using assert
        template <typename Message>
        static void runtimeAssert(bool condition, Message&& message) {
            if (!condition) {
                std::cerr << "Runtime Assertion Failed: " << std::forward<Message>(message) << "\n";
                assert(condition);
            }
        } 
    };
} // namespace TCMS
