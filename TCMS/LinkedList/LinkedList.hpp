#pragma once

#include <iostream>

#include "LinkedListNode.hpp"

namespace TCMS
{
    template <typename T>
    class LinkedList {
    public:
        LinkedList() : m_Head(nullptr) {

        }

        virtual ~LinkedList() {
            while (m_Head != nullptr) {
                LinkedListNode<T>* temp = m_Head;
                m_Head = m_Head->getNext();

                delete temp;
                temp = nullptr;
            }
        }

        virtual void insert(T data) = 0;
        virtual void remove(T data) = 0;
        virtual void print() const = 0;
    protected:
        LinkedListNode<T>* m_Head;
    };

} // namespace TCMS


