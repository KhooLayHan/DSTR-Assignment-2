#pragma once

#include "LinkedListNode.hpp"

// Tennis Championship Management System
namespace TCMS
{
    template <typename T>
    class SinglyLinkedListNode : public LinkedListNode<T> {
    public:
        SinglyLinkedListNode(T data, SinglyLinkedListNode<T>* next = nullptr)
            : m_Data(data), m_Next(next) {

        }

        T getData() const override {
            return m_Data;
        }; 

        void setData(T data) override {
            m_Data = data;
        };

        SinglyLinkedListNode<T>* getNext() const override {
            return m_Next;
        };

        void setNext(SinglyLinkedListNode<T>* next) override {
            // m_Next = static_cast<SinglyLinkedListNode<T>*>(next);
            m_Next = next;
        }; 
    private:
        T m_Data;
        SinglyLinkedListNode<T>* m_Next; 
    };
} // namespace TCMS