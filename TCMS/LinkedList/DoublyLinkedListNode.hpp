#pragma once

#include "LinkedListNode.hpp"

// Tennis Championship Management System
namespace TCMS
{
    template <typename T>
    class DoublyLinkedListNode : public LinkedListNode<T, DoublyLinkedListNode<T>> {
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

        LinkedListNode<T>* getNext() const override {
            return m_Next;
        };

        void setNext(LinkedListNode<T>* next) override {
            m_Next = static_cast<DoublyLinkedListNode<T>*>(next);
        }; 

        LinkedListNode<T>* getPrevious() const {
            return m_Previous;
        };

        void setPrevious(LinkedListNode<T>* previous) {
            m_Previous = static_cast<DoublyLinkedListNode<T>*>(previous);
        }; 
    private:
        T m_Data;
        LinkedListNode<T>* m_Next; 
        LinkedListNode<T>* m_Previous; 
    };
} // namespace TCMS