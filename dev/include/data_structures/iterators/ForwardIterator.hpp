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
        
        explicit ForwardIterator(Pointer ptr) : Base(ptr) {

        }

        ForwardIterator& operator++() {
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
