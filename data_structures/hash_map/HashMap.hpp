#pragma once

#include <iostream>
#include <functional>
#include <cassert>
#include "../Vector.hpp" // Include the TCMS::Vector
#include "Buckets.hpp"

namespace TCMS {
    /**
     * @brief A HashMap implementation using separate chaining for collision resolution.
     * @tparam K The key type.
     * @tparam V The value type.
     */
    template <typename K, typename V>
    class HashMap {
    private:
        Vector<Buckets<K, V>> m_Buckets; // Use TCMS::Vector for bucket storage
        std::hash<K> m_HashFunction;     // Hash function for keys
        size_t m_BucketCount;            // Number of buckets
        size_t m_Size;                   // Number of elements in the HashMap

    public:
        /**
         * @brief Constructs a HashMap with a specified initial capacity.
         * @param capacity The initial number of buckets (default is 1000).
         */
        constexpr explicit HashMap(size_t capacity = 1000) noexcept 
            : m_Buckets(capacity), m_BucketCount(capacity), m_Size(0) {}

        /**
         * @brief Inserts a key-value pair into the HashMap.
         * @param key The key to insert.
         * @param value The value to associate with the key.
         */
        constexpr void insert(const K& key, const V& value) noexcept {
            size_t index = m_HashFunction(key) % m_BucketCount;
            BucketNode<K, V>* existing = m_Buckets[index].find(key);
            if (existing) {
                existing->m_Value = value; // Update value if key exists
            } else {
                m_Buckets[index].insert(key, value); // Insert new key-value pair
                ++m_Size;
            }
        }

        /**
         * @brief Removes a key-value pair from the HashMap.
         * @param key The key to remove.
         * @return True if the key was found and removed, false otherwise.
         */
        constexpr bool remove(const K& key) noexcept {
            size_t index = m_HashFunction(key) % m_BucketCount;
            if (m_Buckets[index].remove(key)) {
                --m_Size;
                return true;
            }
            return false;
        }

        /**
         * @brief Finds a value associated with a given key (modifiable).
         * @param key The key to search for.
         * @return A pointer to the value if found, nullptr otherwise.
         */
        [[nodiscard]] constexpr V* find(const K& key) noexcept {
            size_t index = m_HashFunction(key) % m_BucketCount;
            BucketNode<K, V>* node = m_Buckets[index].find(key);
            return node ? &node->m_Value : nullptr;
        }

        /**
         * @brief Finds a value associated with a given key (constant).
         * @param key The key to search for.
         * @return A const pointer to the value if found, nullptr otherwise.
         */
        [[nodiscard]] constexpr const V* find(const K& key) const noexcept {
            size_t index = m_HashFunction(key) % m_BucketCount;
            BucketNode<K, V>* node = m_Buckets[index].find(key);
            return node ? &node->m_Value : nullptr;
        }

        /**
         * @brief Clears all key-value pairs in the HashMap.
         */
        constexpr void clear() noexcept {
            for (size_t i = 0; i < m_BucketCount; ++i) {
                m_Buckets[i].clear();
            }
            m_Size = 0;
        }

        /**
         * @brief Accesses or inserts a value associated with the given key.
         * @param key The key to access or insert.
         * @return A reference to the value associated with the key.
         */
        constexpr V& operator[](const K& key) noexcept {
            size_t index = m_HashFunction(key) % m_BucketCount;
            BucketNode<K, V>* existing = m_Buckets[index].find(key);
            if (existing) {
                return existing->m_Value;
            }
            m_Buckets[index].insert(key, V());
            return m_Buckets[index].find(key)->m_Value;
        }

        /**
         * @brief Checks if the HashMap contains a given key.
         * @param key The key to check.
         * @return True if the key is found, false otherwise.
         */
        [[nodiscard]] constexpr bool contains(const K& key) noexcept {
            size_t index = m_HashFunction(key) % m_BucketCount;
            return m_Buckets[index].find(key) != nullptr;
        }

        /**
         * @brief Returns the number of elements in the HashMap.
         * @return The number of elements in the HashMap.
         */
        [[nodiscard]] constexpr size_t count() const noexcept { return m_Size; }

        /**
         * @brief Checks if the HashMap is empty.
         * @return True if the HashMap is empty, false otherwise.
         */
        [[nodiscard]] constexpr bool isEmpty() const noexcept { return m_Size == 0; }

        /**
         * @brief Returns the number of buckets in the HashMap.
         * @return The number of buckets.
         */
        [[nodiscard]] constexpr size_t bucketCount() const noexcept { return m_BucketCount; }

        /**
         * @brief Rehashes the HashMap with a new bucket count.
         * @param new_bucket_count The new number of buckets.
         */
        constexpr void rehash(size_t new_bucket_count) noexcept {
            TCMS::Vector<Buckets<K, V>> new_buckets(new_bucket_count); // Use TCMS::Vector
            for (size_t i = 0; i < m_BucketCount; ++i) {
                for (const auto& pair : m_Buckets[i]) {
                    size_t new_index = m_HashFunction(pair.first) % new_bucket_count;
                    new_buckets[new_index].insert(pair.first, pair.second);
                }
            }
            m_Buckets = std::move(new_buckets);
            m_BucketCount = new_bucket_count;
        }

        /**
         * @brief Reserves space for at least new_capacity buckets.
         * @param new_capacity The new capacity to reserve.
         */
        constexpr void reserve(size_t new_capacity) noexcept {
            if (new_capacity > m_BucketCount) {
                rehash(new_capacity);
            }
        }

        /**
         * @brief Retrieves the value associated with a key, throwing an error if not found.
         * @param key The key to search for.
         * @return A reference to the value associated with the key.
         * @throws std::out_of_range If the key is not found.
         */
        [[nodiscard]] constexpr V& get(const K& key) {
            size_t index = m_HashFunction(key) % m_BucketCount;
            BucketNode<K, V>* node = m_Buckets[index].find(key);
            if (!node) {
                throw std::out_of_range("Key not found in HashMap");
            }
            return node->m_Value;
        }

        /**
         * @brief Iterator class for HashMap.
         */
        class Iterator {
        private:
            TCMS::Vector<Buckets<K, V>>& m_Buckets; // Reference to the buckets
            size_t m_BucketIndex;                  // Current bucket index
            typename Buckets<K, V>::Iterator m_Current; // Current iterator within the bucket

        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = std::pair<K, V>;
            using difference_type = std::ptrdiff_t;
            using pointer = std::pair<K, V>*;
            using reference = std::pair<K, V>&;

            /**
             * @brief Constructs an iterator at a specific bucket index.
             * @param buckets Reference to the buckets.
             * @param index The bucket index to start at.
             */
            constexpr Iterator(TCMS::Vector<Buckets<K, V>>& buckets, size_t index) noexcept 
                : m_Buckets(buckets), m_BucketIndex(index), m_Current(buckets[index].begin()) {
                // Move to the first non-empty bucket
                while (m_BucketIndex < m_Buckets.getLength() && m_Current == m_Buckets[m_BucketIndex].end()) {
                    ++m_BucketIndex;
                    if (m_BucketIndex < m_Buckets.getLength()) {
                        m_Current = m_Buckets[m_BucketIndex].begin();
                    }
                }
            }

            /**
             * @brief Dereference operator.
             * @return The current key-value pair.
             */
            constexpr value_type operator*() const noexcept {
                return *m_Current;
            }

            /**
             * @brief Arrow operator.
             * @return A pointer to the current key-value pair.
             */
            constexpr pointer operator->() const noexcept {
                return &(*m_Current);
            }

            /**
             * @brief Pre-increment operator.
             * @return A reference to the updated iterator.
             */
            constexpr Iterator& operator++() noexcept {
                ++m_Current;
                while (m_BucketIndex < m_Buckets.getLength() && m_Current == m_Buckets[m_BucketIndex].end()) {
                    ++m_BucketIndex;
                    if (m_BucketIndex < m_Buckets.getLength()) {
                        m_Current = m_Buckets[m_BucketIndex].begin();
                    }
                }
                return *this;
            }

            /**
             * @brief Post-increment operator.
             * @return A copy of the iterator before incrementing.
             */
            constexpr Iterator operator++(int) noexcept {
                Iterator temp = *this;
                ++(*this);
                return temp;
            }

            /**
             * @brief Equality operator.
             * @param other The iterator to compare with.
             * @return True if the iterators are equal, false otherwise.
             */
            constexpr bool operator==(const Iterator& other) const noexcept {
                return m_BucketIndex == other.m_BucketIndex && m_Current == other.m_Current;
            }

            /**
             * @brief Inequality operator.
             * @param other The iterator to compare with.
             * @return True if the iterators are not equal, false otherwise.
             */
            constexpr bool operator!=(const Iterator& other) const noexcept {
                return !(*this == other);
            }
        };

        /**
         * @brief Returns an iterator to the beginning of the HashMap.
         * @return An iterator to the first element.
         */
        [[nodiscard]] constexpr Iterator begin() noexcept { return Iterator(m_Buckets, 0); }

        /**
         * @brief Returns an iterator to the end of the HashMap.
         * @return An iterator to the end of the HashMap.
         */
        [[nodiscard]] constexpr Iterator end() noexcept { return Iterator(m_Buckets, m_Buckets.getLength()); }
    };
} // namespace TCMS