#pragma once

#include "Iterator.hpp"

namespace TCMS
{
    template <typename Key, typename Value>
    class ForwardIterator : public Iterator<BucketNode<Key, Value>, std::forward_iterator_tag> {
    public:
        using Base = Iterator<BucketNode<Key, Value>, std::forward_iterator_tag>;
        using typename Base::Pointer;
        using typename Base::Reference;
        
        explicit ForwardIterator(Pointer ptr = nullptr) : Base(ptr, nullptr, nullptr) {}

        ForwardIterator& operator++() {
            Assert::runtimeAssert(Base::m_Pointer != nullptr, "Incrementing nullptr iterator!");
            Base::m_Pointer = Base::m_Pointer->m_Next; // Follow the linked list
            return *this;
        }

        ForwardIterator operator++(int) {
            ForwardIterator temp = *this;
            ++(*this);
            return temp;
        }

        // Override dereference operator to return a key-value pair
        std::pair<Key, Value> operator*() const {
            Assert::runtimeAssert(Base::m_Pointer != nullptr, "Dereferencing nullptr iterator!");
            return {Base::m_Pointer->m_Key, Base::m_Pointer->m_Value};
        }

        // Override arrow operator to return a pointer to the key-value pair
        std::pair<Key, Value>* operator->() const {
            Assert::runtimeAssert(Base::m_Pointer != nullptr, "Accessing nullptr iterator!");
            return reinterpret_cast<std::pair<Key, Value>*>(Base::m_Pointer);
        }
    };
} // namespace TCMS