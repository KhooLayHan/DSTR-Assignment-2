#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <cassert>
#include <iterator>
#include <utility> // For std::pair

#include "../../utils/Assert.hpp"

namespace TCMS
{
    /**
     * @brief A node in the bucket of a hash map, storing a key-value pair.
     * 
     * @tparam Key The type of the key.
     * @tparam Value The type of the value.
     */
    template <typename Key, typename Value>
    struct BucketNode {
        Key m_Key;                  // The key stored in the node.
        Value m_Value;              // The value associated with the key.
        BucketNode* m_Next;         // Pointer to the next node in the bucket.

        /**
         * @brief Constructs a new BucketNode.
         * 
         * @param key The key to store.
         * @param value The value to associate with the key.
         */
        BucketNode(const Key& key, const Value& value)
            : m_Key(key), m_Value(value), m_Next(nullptr) {}

        // Alias for the value type (required by ForwardIterator).
        using value_type = std::pair<Key, Value>;
    };

    /**
     * @brief A forward iterator for traversing the nodes in a bucket.
     * 
     * @tparam Key The type of the key.
     * @tparam Value The type of the value.
     */
    template <typename Key, typename Value>
    class HashMapForwardIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<Key, Value>; // Iterator returns a key-value pair.
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        /**
         * @brief Constructs a new HashMapForwardIterator.
         * 
         * @param ptr Pointer to the current node in the bucket.
         */
        explicit HashMapForwardIterator(BucketNode<Key, Value>* ptr = nullptr) : m_Current(ptr) {}

        /**
         * @brief Dereference operator. Returns the key-value pair at the current node.
         * 
         * @return value_type The key-value pair.
         */
        value_type operator*() const {
            Assert::runtimeAssert(m_Current != nullptr, "Dereferencing nullptr iterator!");
            return {m_Current->m_Key, m_Current->m_Value}; // Return a key-value pair.
        }

        /**
         * @brief Arrow operator. Returns a pointer to the key-value pair at the current node.
         * 
         * @return pointer A pointer to the key-value pair.
         */
        pointer operator->() const {
            Assert::runtimeAssert(m_Current != nullptr, "Accessing nullptr iterator!");
            return &(**this); // Return a pointer to the key-value pair.
        }

        /**
         * @brief Pre-increment operator. Moves the iterator to the next node.
         * 
         * @return HashMapForwardIterator& A reference to the updated iterator.
         */
        HashMapForwardIterator& operator++() {
            Assert::runtimeAssert(m_Current != nullptr, "Incrementing nullptr iterator!");
            m_Current = m_Current->m_Next; // Move to the next node.
            return *this;
        }

        /**
         * @brief Post-increment operator. Moves the iterator to the next node.
         * 
         * @return HashMapForwardIterator The iterator before incrementing.
         */
        HashMapForwardIterator operator++(int) {
            HashMapForwardIterator temp = *this;
            ++(*this);
            return temp;
        }

        /**
         * @brief Equality operator. Checks if two iterators are equal.
         * 
         * @param other The iterator to compare with.
         * @return true If the iterators are equal.
         * @return false If the iterators are not equal.
         */
        bool operator==(const HashMapForwardIterator& other) const noexcept {
            return m_Current == other.m_Current;
        }

        /**
         * @brief Inequality operator. Checks if two iterators are not equal.
         * 
         * @param other The iterator to compare with.
         * @return true If the iterators are not equal.
         * @return false If the iterators are equal.
         */
        bool operator!=(const HashMapForwardIterator& other) const noexcept {
            return m_Current != other.m_Current;
        }

    private:
        BucketNode<Key, Value>* m_Current; // Pointer to the current node.
    };

    /**
     * @brief A bucket in a hash map, implemented as a singly linked list of key-value pairs.
     * 
     * @tparam Key The type of the key.
     * @tparam Value The type of the value.
     */
    template <typename Key, typename Value>
    class Buckets {
    public:
        // Use the custom iterator with Key and Value as template arguments.
        using Iterator = HashMapForwardIterator<Key, Value>;

        /**
         * @brief Constructs a new Buckets object.
         */
        Buckets() : m_Head(nullptr) {}

        /**
         * @brief Destructor. Clears the bucket and deallocates memory.
         */
        ~Buckets() {
            clear();
        }

        /**
         * @brief Inserts a key-value pair into the bucket. If the key already exists, updates the value.
         * 
         * @param key The key to insert or update.
         * @param value The value to associate with the key.
         */
        void insert(const Key& key, const Value& value) {
            BucketNode<Key, Value>* existing = find(key);

            if (existing) {
                existing->m_Value = value; // Update existing key.
                return;
            }

            BucketNode<Key, Value>* new_node = new BucketNode<Key, Value>(key, value);
            new_node->m_Next = m_Head;
            m_Head = new_node;
        }

        /**
         * @brief Removes a key-value pair from the bucket.
         * 
         * @param key The key to remove.
         * @return true If the key was found and removed.
         * @return false If the key was not found.
         */
        bool remove(const Key& key) {
            BucketNode<Key, Value>* curr = m_Head;
            BucketNode<Key, Value>* prev = nullptr;

            while (curr) {
                if (curr->m_Key == key) {
                    if (prev) {
                        prev->m_Next = curr->m_Next;
                    } else {
                        m_Head = curr->m_Next;
                    }
                    delete curr;
                    return true;
                }
                prev = curr;
                curr = curr->m_Next;
            }
            return false;
        }

        /**
         * @brief Finds a key-value pair in the bucket.
         * 
         * @param key The key to search for.
         * @return BucketNode<Key, Value>* A pointer to the node containing the key-value pair, or nullptr if not found.
         */
        BucketNode<Key, Value>* find(const Key& key) noexcept {
            BucketNode<Key, Value>* temp = m_Head;

            while (temp) {
                if (temp->m_Key == key)
                    return temp;
                temp = temp->m_Next;
            }

            return nullptr;
        }

        /**
         * @brief Finds a key-value pair in the bucket (const version).
         * 
         * @param key The key to search for.
         * @return BucketNode<Key, Value>* A pointer to the node containing the key-value pair, or nullptr if not found.
         */
        BucketNode<Key, Value>* find(const Key& key) const noexcept {
            BucketNode<Key, Value>* temp = m_Head;

            while (temp) {
                if (temp->m_Key == key)
                    return temp;
                temp = temp->m_Next;
            }

            return nullptr;
        }

        /**
         * @brief Clears the bucket, deallocating all nodes.
         */
        void clear() {
            BucketNode<Key, Value>* temp = m_Head;
            while (temp) {
                BucketNode<Key, Value>* next = temp->m_Next;
                delete temp;
                temp = next;
            }
            m_Head = nullptr;
        }

        /**
         * @brief Returns the head of the bucket.
         * 
         * @return BucketNode<Key, Value>* A pointer to the head node.
         */
        BucketNode<Key, Value>* getHead() const {
            return m_Head;
        }

        /**
         * @brief Returns an iterator to the beginning of the bucket.
         * 
         * @return Iterator An iterator to the first node.
         */
        Iterator begin() { return Iterator(m_Head); }

        /**
         * @brief Returns an iterator to the end of the bucket.
         * 
         * @return Iterator An iterator to the end (nullptr).
         */
        Iterator end() { return Iterator(nullptr); }

        /**
         * @brief Returns a const iterator to the beginning of the bucket.
         * 
         * @return Iterator A const iterator to the first node.
         */
        Iterator begin() const { return Iterator(m_Head); }

        /**
         * @brief Returns a const iterator to the end of the bucket.
         * 
         * @return Iterator A const iterator to the end (nullptr).
         */
        Iterator end() const { return Iterator(nullptr); }

    private:
        BucketNode<Key, Value>* m_Head; // Pointer to the head of the bucket.
    };
} // namespace TCMS