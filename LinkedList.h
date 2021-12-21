#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

template<typename T>
class LinkedList {
private:
    class LinkedNode {
    private:
    protected:
        virtual void setNull() {
            prev = next = NULL;
        }
    public:
        LinkedNode *prev, *next;
        T data;

        LinkedNode() {
            setNull();
            data = T();
        }

        LinkedNode(const LinkedNode& copy) {
            setNull();
            data = copy.data;
        }

        LinkedNode(const T input) {
            setNull();
            data = input;
        }

        virtual ~LinkedNode() {
        }

        virtual LinkedNode& operator=(const LinkedNode& assign) {
            /* 若要完全指向請使用此段註解
               prev = assign.prev;
               next = assign.next; */
            data = assign.data;
            return *this;
        }

        virtual bool operator<(const LinkedNode& right) const {
            return data < right.data;
        }

        virtual bool operator==(const LinkedNode& right) const {
            return data == right.data;
        }

        virtual bool operator!=(const LinkedNode& right) const {
            return !operator==(right);
        }

        virtual bool operator<=(const LinkedNode& right) const {
            return operator<(right) || operator==(right);
        }

        virtual bool operator>(const LinkedNode& right) const {
            return !operator<=(right);
        }

        virtual bool operator>=(const LinkedNode& right) const {
            return !operator<(right);
        }

        virtual bool equals(const LinkedNode& right) const {
            return this == &right;
        }
    };

    virtual void setNull() {
        head = tail = NULL;
        count = 0;
    }

    virtual T compare(bool min) const {
        if (count <= 0) {
            throw std::length_error("串列沒有任何資料");
        }

        T ret = head->data;
        LinkedNode *current = head->next;
        while (current != NULL) {
            T compare = current->data;
            if (min ? compare < ret : compare > ret) {
                ret = compare;
            }
            current = current->next;
        }
        return ret;
    }

    virtual bool sort(bool min) {
        if (count <= 0) {
            return false;
        }

        LinkedNode *current = head;
        for (int i = 0; i < count - 1; ++i) {
            T compare = current->data;
            LinkedNode *swapNode = current;

            LinkedNode *other = current->next;
            while (other != NULL) {
                T data = other->data;
                if (min ? data < compare : data > compare) {
                    compare = data;
                    swapNode = other;
                }
                other = other->next;
            }

            if (swapNode != current) {
                std::swap(current->data, swapNode->data);
            }
            current = current->next;
        }
        return true;
    }

    virtual void clone(const LinkedList& copy) {
        setNull();
        LinkedNode *copyNode = copy.head;
        for (int i = 0; i < copy.count; ++i) {
            LinkedNode *addNode = new LinkedNode(*copyNode);
            if (i == 0) {
                head = tail = addNode;
            } else {
                tail->next = addNode;
                addNode->prev = tail;
                tail = addNode;
            }
            copyNode = copyNode->next;
        }
        count = copy.count;
    }
protected:
    LinkedNode *head, *tail;
    int count;

    virtual bool compareLowerReverse(const LinkedList& right) const {
        if (count < right.count) {
            return true;
        } else if (count == right.count) {
            LinkedNode *leftCurrent = tail;
            LinkedNode *rightCurrent = right.tail;

            while (leftCurrent != NULL) {
                if (leftCurrent->data < rightCurrent->data) {
                    return true;
                } else if (leftCurrent->data > rightCurrent->data) {
                    return false;
                }
                leftCurrent = leftCurrent->prev;
                rightCurrent = rightCurrent->prev;
            }
        }
        return false;
    }
public:
    LinkedList() {
        setNull();
    }

    LinkedList(const LinkedList& copy) {
        clone(copy);
    }

    template<typename Array, size_t ArraySize>
    LinkedList(const Array (&input)[ArraySize]) : LinkedList(input, false) {
    }

    template<typename Array, size_t ArraySize>
    LinkedList(const Array (&input)[ArraySize], bool reverse) {
        setNull();
        for (size_t i = 0; i < ArraySize; ++i) {
            if (reverse) {
                push_front(input[i]);
            } else {
                push_back(input[i]);
            }
        }
    }

    virtual ~LinkedList() {
        clear();
    }

    virtual bool push_front(const T element) {
        return insert(0, element);
    }

    virtual bool push_back(const T element) {
        return insert(count, element);
    }

    template<typename Array, size_t ArraySize>
    void addAll(const Array (&input)[ArraySize]) {
        for (size_t i = 0; i < ArraySize; ++i) {
            push_back(input[i]);
        }
    }

    virtual void addAll(const LinkedList<T>& element) {
        for (LinkedList<T>::iterator itr = element.begin(); itr != element.end(); ++itr) {
            push_back(*itr);
        }
    }

    virtual bool insert(int index, const T element) {
        if (index < 0 || index > count) {
            return false;
        }

        LinkedNode *node = new LinkedNode(element);
        if (count == 0) {
            head = tail = node;
            ++count;
            return true;
        }
        if (index == 0) {
            node->next = head;
            head->prev = node;
            head = node;
        } else if (index == count) {
            node->prev = tail;
            tail->next = node;
            tail = node;
        } else {
            LinkedNode *current = head;
            if (index < count / 2) {
                for (int i = 0; i < index - 1; ++i) {
                    current = current->next;
                }
                node->prev = current;
                node->next = current->next;
                current->next->prev = node;
                current->next = node;
            } else {
                current = tail;
                int reverseIndex = count - 1 - index;
                for (int i = 0; i < reverseIndex; ++i) {
                    current = current->prev;
                }
                node->prev = current->prev;
                node->next = current;
                current->prev->next = node;
                current->prev = node;
            }
        }
        ++count;
        return true;
    }

    virtual bool pop_front() {
        return remove(0);
    }

    virtual bool pop_back() {
        return remove(count - 1);
    }

    virtual bool remove(int index) {
        if (count == 0 || index < 0 || index >= count) {
            return false;
        }
        if (count == 1) {
            delete head;
            setNull();
            return true;
        }

        LinkedNode *current = head;
        if (index == 0) {
            current->next->prev = NULL;
            head = current->next;
            delete current;
        } else if (index == count - 1) {
            current = tail;
            current->prev->next = NULL;
            tail = current->prev;
            delete current;
        } else {
            LinkedNode *current = head;
            if (index < count / 2) {
                for (int i = 0; i < index; ++i) {
                    current = current->next;
                }
            } else {
                current = tail;
                int reverseIndex = count - 1 - index;
                for (int i = 0; i < reverseIndex; ++i) {
                    current = current->prev;
                }
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }
        --count;
        return true;
    }

    virtual bool removeByValue(const T data) {
        LinkedNode *current = head;
        for (int index = 0; current != NULL; current = current->next, ++index) {
            if (current->data == data) {
                return remove(index);
            }
        }
        return false;
    }

    virtual int size() const {
        return count;
    }

    virtual int length() const {
        return count;
    }

    virtual bool empty() const {
        return count <= 0;
    }

    virtual bool isEmpty() const {
        return empty();
    }

    virtual bool add(const T element) {
        return push_back(element);
    }

    virtual T& get(int index) const {
        if (index < 0 || index >= count) {
            throw std::out_of_range("嘗試存取超出範圍資料");
        }

        LinkedNode *current = head;
        if (index < count / 2) {
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
        } else {
            current = tail;
            int reverseIndex = count - 1 - index;
            for (int i = 0; i < reverseIndex; ++i) {
                current = current->prev;
            }
        }
        return current->data;
    }

    virtual bool swap(int left, int right) {
        if (left < 0 || right < 0 || left >= count || right >= count) {
            return false;
        } else if (left == right) {
            return true;
        }
        T& leftElement = get(left);
        T& rightElement = get(right);
        std::swap(leftElement, rightElement);
        return true;
    }

    virtual T& front() const {
        if (head == NULL) {
            throw std::invalid_argument("嘗試存取空指標元素");
        }
        return head->data;
    }

    virtual T& back() const {
        if (tail == NULL) {
            throw std::invalid_argument("嘗試存取空指標元素");
        }
        return tail->data;
    }

    virtual int indexOf(const T data) const {
        LinkedNode *current = head;
        for (int ret = 0; current != NULL; current = current->next, ++ret) {
            if (current->data == data) {
                return ret;
            }
        }
        return -1;
    }

    virtual bool contains(const T data) const {
        LinkedNode *current = head;
        while (current != NULL) {
            if (current->data == data) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    virtual LinkedNode* find(const T& data) const {
        LinkedNode *current = head;
        while (current != NULL) {
            if (current->data == data) {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }

    virtual LinkedNode* findGreaterEqual(const T data) const {
        LinkedNode *current = head;
        while (current != NULL) {
            if (current->data >= data) {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }

    virtual LinkedNode* findLowerEqual(const T data) const {
        LinkedNode *current = head;
        while (current != NULL) {
            if (current->data <= data) {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }

    virtual bool insertBefore(LinkedNode *target, const T element) {
        if (target == NULL) {
            push_back(element);
            return true;
        }

        LinkedNode *node = new LinkedNode(element);
        if (target->prev == NULL) {
            head = node;
            node->next = target;
            target->prev = node;
        } else {
            target->prev->next = node;
            node->prev = target->prev;
            node->next = target;
            target->prev = node;
        }
        ++count;
        return true;
    }

    virtual bool insertAfter(LinkedNode *target, const T element) {
        if (target == NULL) {
            push_front(element);
            return true;
        }

        LinkedNode *node = new LinkedNode(element);
        if (target->next == NULL) {
            tail = node;
            node->prev = target;
            target->next = node;
        } else {
            target->next->prev = node;
            node->prev = target;
            node->next = target->next;
            target->next = node;
        }
        ++count;
        return true;
    }

    virtual bool set(int index, const T element) {
        if (index < 0 || index >= count) {
            return false;
        }

        LinkedNode *current = head;
        if (index < count / 2) {
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
            current->data = element;
        } else {
            current = tail;
            int reverseIndex = count - 1 - index;
            for (int i = 0; i < reverseIndex; ++i) {
                current = current->prev;
            }
            current->data = element;
        }
        return true;
    }

    virtual void clear() {
        LinkedNode *pending = head;
        if (pending == NULL) {
            return;
        }

        while (pending->next != NULL) {
            pending = pending->next;
            delete pending->prev;
        }
        delete pending;
        setNull();
    }

    virtual std::string show_front() const {
        std::string ret = "[ ";
        LinkedNode *current = head;
        while (current != NULL) {
            std::stringstream ss;
            ss << current->data;
            ret += ss.str() + " ";
            current = current->next;
        }
        ret += "]";
        return ret;
    }

    virtual std::string show_back() const {
        std::string ret = "[ ";
        LinkedNode *current = tail;
        while (current != NULL) {
            std::stringstream ss;
            ss << current->data;
            ret += ss.str() + " ";
            current = current->prev;
        }
        ret += "]";
        return ret;
    }

    virtual std::string show() const {
        return show_front();
    }

    virtual T* toArray() const {
        T* array = new T[count];
        LinkedNode *current = head;
        for (int i = 0; i < count; ++i) {
            array[i] = current->data;
            current = current->next;
        }
        return array;
    }

    virtual std::vector<T> toVector() const {
        std::vector<T> ret;
        LinkedNode *current = head;
        while (current != NULL) {
            ret.push_back(current->data);
            current = current->next;
        }
        return ret;
    }

    virtual void reverse() {
        LinkedNode *current = head;
        while (current != NULL) {
            std::swap(current->prev, current->next);
            current = current->prev;
        }
        std::swap(head, tail);
    }

    virtual std::string showDetail() const {
        std::stringstream ss;

        ss << count;
        int indexLength = ss.str().length();
        ss.str("");
        ss.clear();

        ss << tail;
        int addressLength = ss.str().length();
        ss.str("");
        ss.clear();

        ss << "[大小 : " << count << " 指標頭 : " << head << " 指標尾 : " << tail << "]\r\n";
        LinkedNode *current = head;
        for (int index = 0; index < count; ++index) {
            LinkedNode *next = current->next;
            ss << "註標 : " << std::setw(indexLength) << index << " 上一個 : " << std::setw(addressLength) << current->prev << " 目前 : " << std::setw(addressLength) << current << " 下一個 : " << std::setw(addressLength) << next << " 資料 : " << current->data;
            if (next != NULL) {
                ss << "\r\n";
            }
            current = next;
        }
        return ss.str();
    }

    virtual T min() const {
        return compare(true);
    }

    virtual T max() const {
        return compare(false);
    }

    virtual bool sort() {
        return sort(true);
    }

    virtual bool reverseSort() {
        return sort(false);
    }

    int index(const LinkedNode* node) const {
        LinkedNode *current = head;

        for (int i = 0; current != NULL; ++i, current = current->next) {
            if (*node == current) {
                return i;
            }
        }
        return -1;
    }

    virtual LinkedList& operator=(const LinkedList& assign) {
        clear();

        // 完全複製串列
        clone(assign);

        /* 若要僅指向 請使用以下方法
           count = assign.count;
           head = assign.head;
           tail = assign.tail; */
        return *this;
    }

    virtual T& operator[](int index) const {
        return get(index);
    }

    virtual bool operator<(const LinkedList& right) const {
        if (count < right.count) {
            return true;
        } else if (count == right.count) {
            LinkedNode *leftCurrent = head;
            LinkedNode *rightCurrent = right.head;
            while (leftCurrent != NULL) {
                if (leftCurrent->data < rightCurrent->data) {
                    return true;
                } else if (leftCurrent->data > rightCurrent->data) {
                    return false;
                }
                leftCurrent = leftCurrent->next;
                rightCurrent = rightCurrent->next;
            }
        }
        return false;
    }

    virtual bool operator==(const LinkedList& right) const {
        if (count != right.count) {
            return false;
        }

        LinkedNode *leftCurrent = head;
        LinkedNode *rightCurrent = right.head;
        while (leftCurrent != NULL) {
            if (leftCurrent->data != rightCurrent->data) {
                return false;
            }

            leftCurrent = leftCurrent->next;
            rightCurrent = rightCurrent->next;
        }
        return true;
    }

    virtual bool operator!=(const LinkedList& right) const {
        return !operator==(right);
    }

    virtual bool operator<=(const LinkedList& right) const {
        return operator<(right) || operator==(right);
    }

    virtual bool operator>(const LinkedList& right) const {
        return !operator<=(right);
    }

    virtual bool operator>=(const LinkedList& right) const {
        return !operator<(right);
    }

    virtual bool equals(const LinkedList& right) const {
        return this == &right;
    }

    class iterator {
    private:
    protected:
        LinkedNode* ptr;
    public:
        iterator(LinkedNode* input) {
            ptr = input;
        }

        virtual iterator operator++() {
            if (ptr == NULL) {
                return *this;
            }

            ptr = ptr->next;
            return *this;
        }

        virtual iterator operator--() {
            if (ptr == NULL) {
                return *this;
            }

            ptr = ptr->prev;
            return *this;
        }

        virtual iterator operator++(int trash) {
            return operator++();
        }

        virtual iterator operator--(int trash) {
            return operator--();
        }

        virtual T& operator*() const {
            if (ptr == NULL) {
                throw std::invalid_argument("嘗試存取空指標疊代");
            }
            return ptr->data;
        }

        virtual LinkedNode* operator->() const {
            return ptr;
        }

        virtual bool operator==(const iterator& right) const {
            return ptr == right.ptr;
        }

        virtual bool operator!=(const iterator& right) const {
            return !operator==(right);
        }

        virtual bool operator==(const LinkedNode* right) const {
            return ptr == right;
        }

        virtual bool operator!=(const LinkedNode* right) const {
            return !operator==(right);
        }

        bool operator<(const iterator& right) const {
            int current = index(ptr);
            int target = index(right.ptr);
            if (current == -1 || target == -1) {
                return false;
            }
            return current < target;
        }

        bool operator<(const LinkedNode* right) const {
            int current = index(ptr);
            int target = index(right);
            if (current == -1 || target == -1) {
                return false;
            }
            return current < target;
        }

        bool operator<=(const iterator& right) const {
            return operator<(right) || operator==(right);
        }

        bool operator>(const iterator& right) const {
            return !operator<=(right);
        }

        bool operator>=(const iterator& right) const {
            return !operator<(right);
        }

        bool operator<=(const LinkedNode* right) const {
            return operator<(right) || operator==(right);
        }

        bool operator>(const LinkedNode* right) const {
            return !operator<=(right);
        }

        bool operator>=(const LinkedNode* right) const {
            return !operator<(right);
        }
    };

    virtual iterator begin() const {
        return iterator(head);
    }

    virtual iterator end() const {
        return iterator(NULL);
    }

    virtual iterator last() const {
        return iterator(tail);
    }
};

#endif
