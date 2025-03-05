#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "./Iterator.hpp"

namespace PerformanceEvaluation
{   
    template <typename Key, typename Value>
    struct BucketNode {
        Key m_Key;
        Value m_Value;
        
        BucketNode* m_Previous;
        BucketNode* m_Next;
        
        BucketNode(const Key& key, const Value& value) 
            : m_Key(key), m_Value(value), m_Previous(nullptr), m_Next(nullptr) {
            
        } 
    };

    // Doubly Linked List implementation to store key-value pairs and is used for HashMap  
    template <typename Key, typename Value>
    class Buckets {
        public:
            Buckets() : m_Head(nullptr) {

            }

            ~Buckets() {
                Clear();
            }

            void Insert(const Key& key, const Value& value) {
                BucketNode<Key, Value>* existing = Find(key);

                if (existing) {
                    existing->m_Value = value; // Update existing key
                    return;
                }

                // BucketNode<Key, Value>* node = new BucketNode<Key, Value>(key, value);

                // if (!m_Head) {
                //     m_Head = node;
                //     m_Tail = node; 
                // } else {
                //     m_Tail->m_Next = node;
                //     node->m_Previous = m_Tail;
                //     m_Tail = node;
                // }

                BucketNode<Key, Value>* new_node = new BucketNode<Key, Value>(key, value);
                
                if (!m_Head) {
                    m_Head = new_node;
                    return;
                }

                new_node->m_Next = m_Head;
                m_Head->m_Previous = new_node;
                m_Head = new_node;
            }

            bool Remove(const Key& key) {
                BucketNode<Key, Value>* curr = m_Head;
                
                while (curr) {
                    if (curr->m_Key == key) {
                        if (curr->m_Previous) 
                            curr->m_Previous->m_Next = curr->m_Next;
                        if (curr->m_Next) 
                            curr->m_Next->m_Previous = curr->m_Previous;
                        if (curr == m_Head) 
                            m_Head = curr->m_Next;
                        
                        delete curr;
                        return true;
                    }
                    
                    curr = curr->m_Next;
                }
                
                return false;
            }

            BucketNode<Key, Value>* Find(const Key& key) noexcept {
                BucketNode<Key, Value>* temp = m_Head;

                while (temp) {
                    if (temp->m_Key == key)
                        return temp;
                    
                    temp = temp->m_Next;
                }

                return nullptr;
            }

            void Clear() {
                BucketNode<Key, Value>* temp = m_Head;
                
                while (temp) {
                    BucketNode<Key, Value>* next = temp->m_Next;

                    delete temp;
                    temp = next;
                }

                m_Head = nullptr;
            }

            BucketNode<Key, Value>* GetHead() const {
                return m_Head;
            }

            BucketNode<Key, Value>* begin() { return m_Head; }

            // Iterator support for Buckets
            // Iterator<BucketNode<Key, Value>> begin() { return Iterator<BucketNode<Key, Value>>(m_Head); }
            Iterator<BucketNode<Key, Value>> end() { return Iterator<BucketNode<Key, Value>>(nullptr); }

        private:
            BucketNode<Key, Value>* m_Head;
            // BucketNode<Key, Value>* m_Tail;
    };
} // namespace PerformanceEvaluation
