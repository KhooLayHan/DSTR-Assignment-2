#pragma once

// Tennis Championship Management System
namespace TCMS
{
    template <typename T>
    class LinkedListNode {
    public:
        // Pure virtual functions
        virtual T getData() const = 0; 
        virtual void setData(T data) = 0;

        virtual LinkedListNode<T>* getNext() const = 0;
        virtual void setNext(LinkedListNode<T>* next) = 0; 

        // Virtual destructor
        virtual ~LinkedListNode() = default; 
    };
} // namespace TCMS