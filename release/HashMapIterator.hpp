#pragma once

#include "./BucketsIterator.hpp"

namespace PerformanceEvaluation
{
    // Sourced from ChatGPT
    template <typename Key, typename Value>
    class HashMapIterator {
    public:
        using Iterator = HashMapIterator<Key, Value>;

        HashMapIterator(Buckets<Key, Value>** buckets, size_t bucket_count, size_t index = 0)
            : m_Buckets(buckets), m_BucketCount(bucket_count), m_Index(index), m_Current(nullptr) {
            FindNextValidBucket();
        }

        std::pair<Key, Value>& operator*() { return *m_Current; }

        Iterator& operator++() { 
            if (m_Current != m_Buckets[m_Index]->end()) {
                ++m_Current;
            } else {
                ++m_Index;
                FindNextValidBucket();
            }
            return *this;
        }

        bool operator==(const Iterator& other) const { return m_Index == other.m_Index && m_Current == other.m_Current; }
        bool operator!=(const Iterator& other) const { return !(*this == other); }

    private:
        DynamicArray<Buckets<Key, Value>*> m_Buckets;
        size_t m_BucketCount;
        size_t m_Index;
        BucketsIterator<Key, Value> m_Current;

        void FindNextValidBucket() {
            while (m_Index < m_BucketCount && m_Buckets[m_Index]->begin() == m_Buckets[m_Index]->end())
                ++m_Index;

            if (m_Index < m_BucketCount) 
                m_Current = m_Buckets[m_Index]->begin();
        }
    };
} // namespace PerformanceEvaluation
