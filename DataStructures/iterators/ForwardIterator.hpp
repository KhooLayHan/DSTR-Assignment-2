#pragma once

#include "Iterator.hpp"

namespace TCMS
{
    template <typename T>
    class ForwardIterator : public Iterator<T, std::forward_iterator_tag> {
    public:
        using Base = Iterator<T, std::forward_iterator_tag>;
        using typename Base::Pointer;
        using typename Base::Reference;
        
        explicit ForwardIterator(Pointer ptr, Pointer begin, Pointer end) : Base(ptr, begin, end) {

        }

        ForwardIterator& operator++() {
            Assert::runtimeAssert(Base::m_Pointer != nullptr, "Incrementing nullptr iterator!");
            ++Base::m_Pointer;
            return *this;
        }

        ForwardIterator operator++(int) {
            ForwardIterator temp = *this;
            ++(*this);
            return temp;
        }
    };
} // namespace TCMS
