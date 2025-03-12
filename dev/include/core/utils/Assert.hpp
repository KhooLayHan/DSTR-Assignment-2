#pragma once

#include <cassert>
#include <iostream>
#include <utility>

namespace TCMS
{
    class Assert {
    public:
        // Compile-time assertion using static_assert
        template <bool Condition, typename Message>
        static constexpr void compiletimeAssert(Message&& message) {
            static_assert(Condition, "Compile-time Assertion Failed");

            // This if-block condition should never be executed, ...
            if (!Condition) {
                std::cerr << "Static Assertion Failed: " << std::forward<Message>(message) << "\n";
            }
        }

        // Run-time assertion using assert
        template <typename Message>
        static void runtimeAssert(bool condition, Message&& message) {
            if (!condition)
                std::cerr << "Runtime Assertion Failed: " << std::forward<Message>(message) << "\n";
            
            assert(condition);
        } 
    };
} // namespace TCMS
