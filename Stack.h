#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <iostream>
#include "LinkedList.h"

template<typename T>
class Stack : protected LinkedList<T> {
private:
protected:
    typedef LinkedList<T> super;

    enum StackMode {
        BACK = 0, FRONT = 1
    };

    StackMode mode;

    virtual void setMode(int value) {
        if (value == 1) {
            mode = FRONT;
        } else {
            mode = BACK;
        }
    }
public:
    Stack() {
        mode = BACK;
    }

    Stack(int mode) {
        setMode(mode);
    }

    Stack(const Stack& copy) : super::LinkedList(copy) {
        setMode(copy.mode);
    }

    template<typename Array, size_t ArraySize>
    Stack(const Array (&input)[ArraySize]) : super::LinkedList(input, true) {
        mode = BACK;
    }

    template<typename Array, size_t ArraySize>
    Stack(const Array (&input)[ArraySize], int mode) : super::LinkedList(input, mode != 1) {
        setMode(mode);
    }

    template<typename Array, size_t ArraySize>
    Stack(const Array (&input)[ArraySize], bool reverse) : super::LinkedList(input, !reverse) {
        mode = BACK;
    }

    template<typename Array, size_t ArraySize>
    Stack(const Array (&input)[ArraySize], int mode, bool reverse) : super::LinkedList(input, mode == 1 ? reverse : !reverse) {
        setMode(mode);
    }

    virtual bool push(const T element) {
        return mode == BACK ? super::push_back(element) : super::push_front(element);
    }

    virtual bool pop() {
        return mode == BACK ? super::pop_back() : super::pop_front();
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

    virtual T& top() const {
        if (super::count == 0) {
            throw std::length_error("嘗試存取空堆疊元素");
        }
        return mode == BACK ? super::tail->data : super::head->data;
    }

    virtual T& peek() const {
        return top();
    }

    virtual void changeMode() {
        super::reverse();
        mode = mode == BACK ? FRONT : BACK;
    }

    virtual std::string show() const {
        return mode == BACK ? super::show_back() : super::show_front();
    }

    Stack& operator=(const Stack& assign) {
        mode = assign.mode;
        return super::operator=(assign);
    }

    virtual bool operator<(const Stack& right) const {
        if (mode == right.mode) {
            if (mode == BACK) {
                return super::compareLowerReverse(right);
            } else {
                return super::operator<(right);
            }
        }

        Stack compareA(*this), compareB(right);
        if (compareA.mode == FRONT) {
            compareA.changeMode();
        } else if (compareB.mode == FRONT) {
            compareB.changeMode();
        }
        return compareA.super::compareLowerReverse(compareB);
    }

    virtual bool operator==(const Stack& right) const {
        if (mode == right.mode) {
            return super::operator==(right);
        }

        Stack compareA(*this), compareB(right);
        if (compareA.mode == FRONT) {
            compareA.changeMode();
        } else if (compareB.mode == FRONT) {
            compareB.changeMode();
        }
        return compareA.super::operator==(compareB);
    }

    virtual bool operator!=(const Stack& right) const {
        return !operator==(right);
    }

    virtual bool operator<=(const Stack& right) const {
        return operator<(right) || operator==(right);
    }

    virtual bool operator>(const Stack& right) const {
        return !operator<=(right);
    }

    virtual bool operator>=(const Stack& right) const {
        return !operator<(right);
    }
};

#endif
