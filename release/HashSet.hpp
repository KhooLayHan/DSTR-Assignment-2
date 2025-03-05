#pragma once

#include "./HashMap.hpp"

#include <initializer_list>

namespace PerformanceEvaluation
{
    template <typename K>
    class HashSet {
    private:
        HashMap<K, bool> m_HashMap;
    
    public:
        constexpr explicit HashSet(size_t capacity = 1000) noexcept : m_HashMap(capacity) {}
        
        constexpr HashSet(std::initializer_list<K> initList) noexcept {
            for (const auto& key : initList) {
                Insert(key);
            }
        }

        constexpr void Insert(const K& key) noexcept {
            m_HashMap.Insert(key, true);
        }
        
        constexpr bool Remove(const K& key) noexcept {
            return m_HashMap.Remove(key);
        }
        
        [[nodiscard]] constexpr bool Contains(const K& key) noexcept {
            return m_HashMap.Contains(key);
        }
        
        [[nodiscard]] constexpr size_t Size() const noexcept { return m_HashMap.Size(); }
        [[nodiscard]] constexpr bool Empty() const noexcept { return m_HashMap.Empty(); }
        [[nodiscard]] constexpr size_t BucketCount() const noexcept { return m_HashMap.BucketCount(); }
        
        constexpr void Clear() noexcept { m_HashMap.Clear(); }
    };
} // namespace PerformanceEvaluation
