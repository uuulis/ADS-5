// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
    T data[size];
    int top;

 public:
    TStack() : top(-1) {}

    void Push(const T& value) {
        if (top < size - 1) {
            data[++top] = value;
        }
    }

    void Pop() {
        if (top >= 0) {
            --top;
        }
    }

    T Top() const {
        if (top >= 0) {
            return data[top];
        }
        return T();
    }

    bool IsEmpty() const {
        return top == -1;
    }

    bool IsFull() const {
        return top == size - 1;
    }
};

#endif // INCLUDE_TSTACK_H_
