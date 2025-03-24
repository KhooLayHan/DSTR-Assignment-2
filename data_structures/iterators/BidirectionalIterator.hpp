#pragma once

#include "./Iterator.hpp"

namespace TCMS
{
    /**
     * @brief A bidirectional iterator that extends the base Iterator class.
     * @tparam T The type of elements the iterator points to.
     */
    template <typename T>
    class BidirectionalIterator : public Iterator<T, std::bidirectional_iterator_tag> {
    public:
        using Base = Iterator<T, std::bidirectional_iterator_tag>; // Alias for the base class
        using typename Base::Pointer;                             // Pointer type alias
        using typename Base::Reference;                           // Reference type alias

        /**
         * @brief Constructs a BidirectionalIterator.
         * @param ptr Pointer to the current element.
         * @param begin Pointer to the beginning of the range.
         * @param end Pointer to the end of the range.
         */
        explicit BidirectionalIterator(Pointer ptr, Pointer begin, Pointer end) 
            : Base(ptr, begin, end) {}

        /**
         * @brief Pre-increment operator.
         * @return A reference to the updated iterator.
         * @throws std::runtime_error If the iterator is null.
         */
        BidirectionalIterator& operator++() {
            Assert::runtimeAssert(Base::m_Pointer != nullptr, "Incrementing nullptr iterator!");
            ++Base::m_Pointer;
            return *this;
        }

        /**
         * @brief Post-increment operator.
         * @return A copy of the iterator before incrementing.
         */
        BidirectionalIterator operator++(int) {
            BidirectionalIterator temp = *this;
            ++(*this);
            return temp;
        }

        /**
         * @brief Pre-decrement operator.
         * @return A reference to the updated iterator.
         * @throws std::runtime_error If the iterator is null.
         */
        BidirectionalIterator& operator--() {
            Assert::runtimeAssert(Base::m_Pointer != nullptr, "Decrementing nullptr iterator!");
            --Base::m_Pointer;
            return *this;
        }

        /**
         * @brief Post-decrement operator.
         * @return A copy of the iterator before decrementing.
         */
        BidirectionalIterator operator--(int) {
            BidirectionalIterator temp = *this;
            --(*this);
            return temp;
        }
    };
} // namespace TCMS