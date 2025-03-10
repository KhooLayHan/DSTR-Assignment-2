#pragma once

#include <iostream>

#include "LinkedListNode.hpp"

namespace TCMS
{
    template <typename T, typename DerivedNode>
    class LinkedList {
    public:
        LinkedList() : m_Head(nullptr), m_Tail(nullptr) {

        }

        virtual ~LinkedList() = default;

        virtual void insertBegin(T data) = 0;
        virtual void insertEnd(T data) = 0;
        
        virtual void remove(T data) = 0;
        virtual void removeBegin() = 0;
        // virtual void removeEnd() = 0;
        
        virtual void print() const = 0;

        LinkedList<T, DerivedNode> getHead() const {
            return m_Head;
        };

        LinkedList<T, DerivedNode> getTail() const {
            return m_Tail;
        };

        T getFirst() const {
            if (getHead() == nullptr) {
                throw std::runtime_error("List is empty");
            }

            return getHead()->getData();
        }

        T getLast() const {
            if (getTail() == nullptr) {
                throw std::runtime_error("List is empty");
            }

            return getTail()->getData();
        }

        bool isEmpty() const {
            return getHead() == nullptr;
        }
    protected:
        LinkedListNode<T, DerivedNode>* m_Head;
        LinkedListNode<T, DerivedNode>* m_Tail;

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


