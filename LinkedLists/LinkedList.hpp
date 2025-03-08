#pragma once

#include <iostream>

#include "LinkedListNode.hpp"

namespace TCMS
{
    template <typename T, typename DerivedNode>
    class LinkedList {
    public:
        LinkedList() : m_Head(nullptr) {

        }

        virtual ~LinkedList() = default;

        virtual void insert(T data) = 0;
        virtual void remove(T data) = 0;
        virtual void print() const = 0;
    protected:
        LinkedListNode<T, DerivedNode>* m_Head;

        // Upcast: Convert DerivedNode* to LinkedListNode<T, DerivedNode>*
        LinkedListNode<T, DerivedNode>* upcastFunc(DerivedNode* node) {
            return static_cast<LinkedListNode<T, DerivedNode>*>(node);
        }

        // Downcast: Convert LinkedListNode<T, DerivedNode>* to DerivedNode*
        DerivedNode* downcastFunc(LinkedListNode<T, DerivedNode>* node) const {
            return static_cast<DerivedNode*>(node);
        }
    };

} // namespace TCMS


