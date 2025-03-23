#pragma once

#include "./Iterator.hpp"

namespace TCMS
{
    template <typename T>
    class BidirectionalIterator : public Iterator<T, std::bidirectional_iterator_tag> {
    public:
        using Base = Iterator<T, std::bidirectional_iterator_tag>;
        using typename Base::Pointer;
        using typename Base::Reference;
        
        explicit BidirectionalIterator(Pointer ptr, Pointer begin, Pointer end) : Base(ptr, begin, end) {

        }

        BidirectionalIterator& operator++() {
            Assert::runtimeAssert(Base::m_Pointer != nullptr, "Incrementing nullptr iterator!");
            ++Base::m_Pointer;
            return *this;
        }

        BidirectionalIterator operator++(int) {
            BidirectionalIterator temp = *this;
            ++(*this);
            return temp;
        }

        BidirectionalIterator& operator--() {
            Assert::runtimeAssert(Base::m_Pointer != nullptr, "Decrementing nullptr iterator!");
            --Base::m_Pointer;
            return *this;
        }

        BidirectionalIterator operator--(int) {
            BidirectionalIterator temp = *this;
            --(*this);
            return temp;
        }
    };
} // namespace TCMS
