#pragma once

#include "LinkedListNode.hpp"

// Tennis Championship Management System
namespace TCMS
{
    template <typename T>
    class DoublyLinkedListNode : public LinkedListNode<T> {
    public:
        DoublyLinkedListNode(T data, DoublyLinkedListNode<T>* next = nullptr, DoublyLinkedListNode<T>* previous = nullptr)
            : m_Data(data), m_Next(next), m_Previous(previous) {

        }

        T getData() const override {
            return m_Data;
        }; 

        void setData(T data) override {
            m_Data = data;
        };

        DoublyLinkedListNode<T>* getNext() const override {
            return m_Next;
        };

        void setNext(DoublyLinkedListNode<T>* next) override {
            // m_Next = static_cast<DoublyLinkedListNode<T>*>(next);
            m_Next = next;
        }; 

        DoublyLinkedListNode<T>* getPrevious() const {
            return m_Previous;
        };

        void setPrevious(DoublyLinkedListNode<T>* previous) {
            m_Previous = previous;
        }; 
    private:
        T m_Data;
        DoublyLinkedListNode<T>* m_Next; 
        DoublyLinkedListNode<T>* m_Previous; 
    };
} // namespace TCMS