#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <iostream>
#include "LinkedList.h"

template<typename T>
class Queue : protected LinkedList<T> {
private:
protected:
    typedef LinkedList<T> super;

    enum QueueMode {
        BACK = 0, FRONT = 1
    };

    QueueMode mode;

    virtual void setMode(int value) {
        if (value == 1) {
            mode = FRONT;
        } else {
            mode = BACK;
        }
    }
public:
    Queue() {
        mode = BACK;
    }

    Queue(int mode) {
        setMode(mode);
    }

    Queue(const Queue& copy) : super::LinkedList(copy) {
        setMode(copy.mode);
    }

    template<typename Array, size_t ArraySize>
    Queue(const Array (&input)[ArraySize]) : super::LinkedList(input, false) {
        mode = BACK;
    }

    template<typename Array, size_t ArraySize>
    Queue(const Array (&input)[ArraySize], int mode) : super::LinkedList(input, mode == 1) {
        setMode(mode);
    }

    template<typename Array, size_t ArraySize>
    Queue(const Array (&input)[ArraySize], bool reverse) : super::LinkedList(input, reverse) {
        mode = BACK;
    }

    template<typename Array, size_t ArraySize>
    Queue(const Array (&input)[ArraySize], int mode, bool reverse) : super::LinkedList(input, mode == 1 ? !reverse : reverse) {
        setMode(mode);
    }

    virtual bool push(const T element) {
        return mode == BACK ? super::push_back(element) : super::push_front(element);
    }

    virtual bool pop() {
        return mode == BACK ? super::pop_front() : super::pop_back();
    }

    virtual T& front() const {
        if (super::count == 0) {
            throw std::length_error("嘗試存取空佇列元素");
        }
        return mode == BACK ? super::head->data : super::tail->data;
    }

    virtual T& back() const {
        if (super::count == 0) {
            throw std::length_error("嘗試存取空佇列元素");
        }
        return mode == BACK ? super::tail->data : super::head->data;
    }

    virtual bool empty() const {
        return super::empty();
    }

    virtual bool isEmpty() const {
        return empty();
    }

    virtual int length() const {
        return super::length();
    }

    virtual int size() const {
        return super::size();
    }

    virtual void clear() {
        return super::clear();
    }

    virtual void changeMode() {
        super::reverse();
        mode = mode == BACK ? FRONT : BACK;
    }

    virtual std::string show() const {
        return mode == BACK ? super::show_front() : super::show_back();
    }

    Queue& operator=(const Queue& assign) {
        mode = assign.mode;
        return super::operator=(assign);
    }

    virtual bool operator<(const Queue& right) const {
        if (mode == right.mode) {
            if (mode == BACK) {
                return super::operator<(right);
            } else {
                return super::compareLowerReverse(right);
            }
        }

        Queue compareA(*this), compareB(right);
        if (compareA.mode == FRONT) {
            compareA.changeMode();
        } else if (compareB.mode == FRONT) {
            compareB.changeMode();
        }
        return compareA.super::operator<(compareB);
    }

    virtual bool operator==(const Queue& right) const {
        if (mode == right.mode) {
            return super::operator==(right);
        }

        Queue compareA(*this), compareB(right);
        if (compareA.mode == FRONT) {
            compareA.changeMode();
        } else if (compareB.mode == FRONT) {
            compareB.changeMode();
        }
        return compareA.super::operator==(compareB);
    }

    virtual bool operator!=(const Queue& right) const {
        return !operator==(right);
    }

    virtual bool operator<=(const Queue& right) const {
        return operator<(right) || operator==(right);
    }

    virtual bool operator>(const Queue& right) const {
        return !operator<=(right);
    }

    virtual bool operator>=(const Queue& right) const {
        return !operator<(right);
    }
};

#endif
