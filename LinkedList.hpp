#pragma once
#include<iostream>
#include <cstddef>
#include <exception>

template <class T>
class LinkedList {
private:
    template <class T>
    struct Node {
        T key;
        Node<T>* next;
        Node(T key) : key(key), next(nullptr) {};

    };

    Node<T>* front;

    size_t size;

public:
    LinkedList() : front(nullptr), size(0) {
    };
    
    ~LinkedList() {

        while (front) {

            Node<T>* cur = this->front;
            this->front = this->front->next;
            delete cur;
            size--;
        }

    };
    
    LinkedList(const LinkedList<T>& other) {

        Node<T>* traverseOther = other.front;
        int i = 0;
        while (i < other.size) {
            insertAtPos(traverseOther->key, i);
            i++;
            traverseOther = traverseOther->next;
        }

    };
    
    bool operator==(const LinkedList<T>& other) const {

        if (this->size == 0 && other.size == 0) {
            return true;
        }

        if (this->size != other.size) {
            return false;
        }

        Node<T>* cur = this->front;
        Node<T>* OthCur = other.front;

        while (cur)
        {

            if (cur->key != OthCur->key) {
                return false;
            }
            cur = cur->next;
            OthCur = OthCur->next;
        }

        return true;

    }
    
    LinkedList<T>& operator=(const LinkedList<T>& other) {

        this->~LinkedList();

        Node<T>* traverseOther = other.front;
        int i = 0;
        while (i < other.size) {
            insertAtPos(traverseOther->key, i);
            i++;
            traverseOther = traverseOther->next;
        }

        return *this;
    }

    void insertAtPos(T a, std::size_t pos = 0) {

        Node<T>* toInsert = new Node<T>(a);
        if (pos > size || pos < 0) {

            throw std::out_of_range("Position greater than the size of the list.");

        }
        else if (pos == 0) {

            toInsert->next = front;
            this->front = toInsert;

        }
        else {

            Node<T>* cur = this->front;
            while (--pos)
            {
                cur = cur->next;
            }

            toInsert->next = cur->next;
            cur->next = toInsert;

        }

        this->size++;

    }

    void push_back(T a) {

        Node<T>* toInsert = new Node<T>(a);

        Node<T>* cur = this->front;
        int pos = size;

        if (pos == 0) {

            this->front = toInsert;
            this->size++;
            return;
        }

        while (--pos)
        {
            cur = cur->next;
        }

        cur->next = toInsert;
        
        this->size++;
    }

    void removeAtPos(std::size_t pos) {

        if (pos > size || pos < 0) {

            throw std::out_of_range("Position greater than the size of the list.");
            return;

        }
        else if (pos == 0) {

            Node<T>* cur = this->front->next;
            delete this->front;
            this->front = cur;

        }
        else {

            Node<T>* cur = this->front;
            while (--pos)
            {
                cur = cur->next;
            }
            Node<T>* temp = cur->next;
            cur->next = temp->next;
            delete temp;

        }
        this->size--;

    }
    
    const T& getElementAtPos(unsigned pos) {

        if (pos > size) {
            throw std::out_of_range("Position greater than the size of the list.");
        }

        Node<T>* cur = this->front;
        while (pos--)
        {
            cur = cur->next;
        }

        return cur->key;

    }
    
    T& top() const {

        return this->front->key;

    }
    
    std::size_t getSize() {

        return this->size;

    }
    
    Node<T>* Merge(Node<T>* a, Node<T>* b) {

        Node<T>* cur = nullptr;
        if (!a) {
            return b;
        }
        else if (!b) {
            return a;
        }

        if (a->key <= b->key) {

            cur = a;
            cur->next = Merge(a->next, b);
        }
        else {
            cur = b;
            cur->next = Merge(a, b->next);
        }

        return cur;
    }
   
    void Split(Node<T>* curFront, Node<T>** ThisFront, Node<T>** ThisBack) {

        Node<T>* slow = curFront;
        Node<T>* fast = curFront->next;


        while (fast) {

            fast = fast->next;

            if (fast) {

                fast = fast->next;
                slow = slow->next;

            }
        }

        *ThisFront = curFront;
        *ThisBack = slow->next;
        slow->next = nullptr;

    }

    void MergeSort(Node<T>** curFront) {

        Node<T>* fr = *curFront;
        Node<T>* first;
        Node<T>* second;

        if (fr == nullptr || fr->next == nullptr) {
            return;
        }

        Split(fr, &first, &second);
        MergeSort(&first);
        MergeSort(&second);
        *curFront = Merge(first, second);
        
    }

    void sort() { 

        MergeSort(&this->front);

    }

    bool isSorted() {

        Node<T>* cur = this->front;

        while (cur->next) {

            if (cur->key > cur->next->key) {
                return false;
            }
            cur = cur->next;

        }

        return true;
    }

    LinkedList<T> mapList(T(*m)(const T&)) {

        LinkedList<T> ListToReturn;
        Node<T>* curListFront = this->front;

        while (curListFront)
        {

            ListToReturn.push_back(m(curListFront->key));
            curListFront = curListFront->next;

        }

        return ListToReturn;

    }
    
    LinkedList<T> filterList(bool (*b)(const T&)) {

        LinkedList<T> ListToReturn;
        Node<T>* curListFront = this->front;

        while (curListFront)
        {
            if (b(curListFront->key)) {
                ListToReturn.push_back(curListFront->key);
            }
            curListFront = curListFront->next;

        }
        return ListToReturn;
    }

    void removeEachK(LinkedList<T>& object, size_t k) {
        
        size_t countToK = 0;
        size_t i = 0;

        while (true) {

            if (countToK == k) {

                if ((i - 1) >= object.size) {
                    break;
                }

                object.removeAtPos(i-1);

                countToK = 0;
                i--;
                continue;
            }

            countToK++;
            i++;
        }

    }
    
    struct Iterator { // can this be also class?
        Iterator() : current(nullptr) {};
        Iterator(Node<T>* _current) : current(_current) {};
        friend bool operator==(const Iterator& a, const Iterator& b) {
            return a.current == b.current;
        }
        friend bool operator!=(const Iterator& a, const Iterator& b) {
            return a.current != b.current;
        }
        T& operator*() const {
            return current->key;
        }
        Iterator& operator++() {
            if(current){
                current = current->next;
            }
        }
        Iterator operator++(int) {
            Iterator iter = *this;
            ++* this;
            return iter;
        }
    private:
        Node<T>* current;
    };
    Iterator begin() { return Iterator(this->front); }
    Iterator end() { return Iterator(nullptr); } // is there a way to know this value?
};


template <class T>
class DoubleLinkedList {
private:
    template <class T>
    struct Node {
        T key;
        Node<T>* next;
        Node<T>* prev;
        Node(T key) : key(key), next(nullptr), prev(nullptr) {};

    };

    Node<T>* front;

    size_t size;

public:
    DoubleLinkedList() : front(nullptr), size(0) {
    };
    ~DoubleLinkedList() {

        while (front) {

            Node<T>* cur = this->front;
            this->front = this->front->next;
            delete cur;
            size--;
        }

    };
    DoubleLinkedList(const LinkedList<T>& other) {

        Node<T>* traverseOther = other.front;
        int i = 0;
        while (i < other.size) {
            insertAtPos(traverseOther->key, i);
            i++;
            traverseOther = traverseOther->next;
        }

    };
    bool operator==(const DoubleLinkedList<T>& other) const {

        if (this->size != other.size) {
            return false;
        }

        Node<T>* cur = this->front;
        Node<T>* OthCur = other.front;

        while (cur)
        {

            if (cur->key != OthCur->key) {
                return false;
            }
            cur = cur->next;
            OthCur = OthCur->next;
        }

        return true;

    }
    DoubleLinkedList<T>& operator=(const DoubleLinkedList<T>& other) {

        this->~LinkedList();

        Node<T>* traverseOther = other.front;
        int i = 0;
        while (i < other.size) {
            insertAtPos(traverseOther->key, i);
            i++;
            traverseOther = traverseOther->next;
        }

        return *this;
    }

    void insertAtPos(T a, std::size_t pos = 0) {

        Node<T>* toInsert = new Node<T>(a);
        if (pos > size || pos < 0) {

            throw std::out_of_range("Position greater than the size of the list.");

        }
        else if (pos == 0) {

            toInsert->next = front;
            if (front) {
                front->prev = toInsert;
            }
            this->front = toInsert;

        }
        else {

            Node<T>* cur = this->front;
            while (--pos)
            {
                cur = cur->next;
            }
            if (cur->next) {
                toInsert->next = cur->next;
                cur->next->prev = toInsert;
            }
            toInsert->prev = cur;
            cur->next = toInsert;

        }

        this->size++;

    }
    void removeAtPos(std::size_t pos) {

        if (pos > size || pos < 0) {

            throw std::out_of_range("Position greater than the size of the list.");
            return;

        }
        else if (pos == 0) {

            Node<T>* cur = this->front->next;
            cur->prev = nullptr;
            delete this->front;
            this->front = cur;

        }
        else {

            Node<T>* cur = this->front;
            while (--pos)
            {
                cur = cur->next;
            }
            Node<T>* temp = cur->next;
            cur->next = temp->next;
            if (temp->next) {
                temp->next->prev = cur;
            }
            delete temp;

        }
        this->size--;

    }
    const T& getElementAtPos(unsigned pos) {

        if (pos > size) {
            throw std::out_of_range("Position greater than the size of the list.");
        }

        Node<T>* cur = this->front;
        while (pos--)
        {
            cur = cur->next;
        }

        return cur->key;

    }
    T& top() const {

        return this->front->key;

    }
    std::size_t getSize() {

        return this->size;

    }

    void push_back(T a) {

        Node<T>* toInsert = new Node<T>(a);

        Node<T>* cur = this->front;
        int pos = size;

        if (pos == 0) {

            this->front = toInsert;
            this->size++;
            return;
        }

        while (--pos)
        {
            cur = cur->next;
        }

        cur->next = toInsert;
        toInsert->prev = cur;

        this->size++;
    }

    struct Iterator { // can this be also class?
        Iterator() : current(nullptr) {};
        Iterator(Node<T>* _current) : current(_current) {};
        friend bool operator==(const Iterator& a, const Iterator& b) {
            return a.current == b.current;
        }
        friend bool operator!=(const Iterator& a, const Iterator& b) {
            return a.current != b.current;
        }
        T& operator*() const {
            return current->key;
        }
        Iterator& operator++() {
            if (current) {
                current = current->next;
            }
        }
        Iterator operator++(int) {
            Iterator iter = *this;
            ++* this;
            return iter;
        }
        Iterator& operator--() {
            if (current) {
                current = current->prev;
            }
        }
        Iterator operator--(int) {
            Iterator iter = *this;
            --* this;
            return iter;
        }

    private:
        Node<T>* current;
    };
    Iterator begin() { return Iterator(this->front); }
    Iterator end() { return Iterator(nullptr); } // is there a way to know this value?

};



template<class T>
class Deque {

private:
    DoubleLinkedList<T> deqList;

public:

    void pushFront(T data) {

        deqList.insertAtPos(data);

    }

    void pushBack(T data) {
        
        deqList.push_back(data);

    }

    void popFront() {

        deqList.removeAtPos(0);

    }

    void popBack() {

        deqList.removeAtPos(deqList.getSize() - 1);
    }

    bool Empty() {

        if (deqList.getSize()) {
            return false;
        }
        return true;
    }


};
