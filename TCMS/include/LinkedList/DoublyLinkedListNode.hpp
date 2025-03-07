#pragma once

#include "LinkedListNode.hpp"

// Tennis Championship Management System
namespace TCMS
{
    template <typename T>
    class DoublyLinkedListNode : public ILinkedListNode {
    public:
        DoublyLinkedListNode(T data, DoublyLinkedListNode<T>* next = nullptr, DoublyLinkedListNode<T>* previous = nullptr)
            : m_Data(data), m_Next(next), m_Previous(previous) {

        }

        T getData() const override {
            return m_Data;
        }; 

        void setData(T data) const override {
            m_Data = data;
        };

        LinkedListNode<T>* getNext() const override {
            return m_Next;
        };

        void setNext(LinkedListNode<T>* next) const override {
            m_Next = next;
        }; 

        LinkedListNode<T>* getPrevious() const {
            return m_Previous;
        };

        void setNext(LinkedListNode<T>* previous) const {
            m_Previous = previous;
        }; 
    private:
        T m_Data;
        LinkedListNode<T>* m_Next; 
        LinkedListNode<T>* m_Previous; 
    };
} // namespace TCMS