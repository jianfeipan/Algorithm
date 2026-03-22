/*
idea:
    data structure: array-> squential, continuous memory (faster w/r)
    head, tail -> queue empty  and  queue full, increment direction 
    circular: %k  

*/

class MyCircularDeque {
private:
    int m_capacity;
    int* m_data;
    int m_head;
    int m_tail;
    int m_elmCount;

public:
    MyCircularDeque(int k):
        m_capacity(k), 
        m_data(new int[m_capacity]),
        m_head(0),
        m_tail(0),
        m_elmCount(0){
    }
    
    bool insertFront(int value) {
        if(isFull()) return false;

        if(m_elmCount!=0) m_head = (m_head - 1 + m_capacity) % m_capacity;
        m_data[m_head] = value;
        ++m_elmCount;
        return true;
    }
    
    bool insertLast(int value) {
        if(isFull()) return false;

        if(m_elmCount!=0) m_tail = (m_tail + 1) % m_capacity;
        m_data[m_tail] = value;
        ++m_elmCount;
        return true;
    }
    
    bool deleteFront() {
        if(isEmpty()) return false;
        --m_elmCount;
        
        if(m_elmCount!=0) m_head = (m_head + 1) % m_capacity;
        
        return true;
    }
    
    bool deleteLast() {
        if(isEmpty()) return false;
        --m_elmCount;

        if(m_elmCount!=0) m_tail = (m_tail - 1 + m_capacity) % m_capacity;
        return true;
    }
    
    int getFront() {
        if(isEmpty()) return -1;
        return m_data[m_head];
    }
    
    int getRear() {
        if(isEmpty()) return -1;
        return m_data[m_tail];
    }
    
    bool isEmpty() {
        return m_elmCount==0;
    }
    
    bool isFull() {
        return m_elmCount == m_capacity;
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
