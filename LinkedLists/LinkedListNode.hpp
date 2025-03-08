#pragma once

// Tennis Championship Management System
namespace TCMS
{
    template <typename T, typename DerivedNode>
    class LinkedListNode {
    public:
        // Pure virtual functions
        virtual T getData() const = 0; 
        virtual void setData(T data) = 0;

        virtual DerivedNode* getNext() const = 0;
        virtual void setNext(DerivedNode* next) = 0; 

        // Virtual destructor
        virtual ~LinkedListNode() = default; 
    };
} // namespace TCMS