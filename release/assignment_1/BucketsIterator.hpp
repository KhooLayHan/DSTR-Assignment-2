#pragma once

#include "./Buckets.hpp"

namespace PerformanceEvaluation
{
    template <typename Key, typename Value>
    class BucketsIterator {
        using Iterator = BucketsIterator<Key, Value>;

        explicit BucketsIterator(BucketNode<Key, Value>* node) : m_Current(node) {}

        std::pair<Key, Value>& operator*() { return { m_Current->m_Key, m_Current->m_Value }; }

        Iterator& operator++() { 
            if (m_Current) m_Current = m_Current->m_Next; 
            return *this; 
        }

        Iterator operator++(int) { 
            Iterator temp = *this; 
            ++(*this); 
            return temp; 
        }

        Iterator& operator--() { 
            if (m_Current) m_Current = m_Current->m_Previous; 
            return *this; 
        }

        Iterator operator--(int) { 
            Iterator temp = *this; 
            --(*this); 
            return temp; 
        }

        bool operator==(const Iterator& other) const { return m_Current == other.m_Current; }
        bool operator!=(const Iterator& other) const { return m_Current != other.m_Current; }
    private:
        BucketNode<Key, Value>* m_Current;
    };  
} // namespace PerformanceEvaluation
