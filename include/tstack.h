// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 public:
  TStack() : top_(-1) {}

  void push(T value) {
    if (top_ < size - 1) {
      data_[++top_] = value;
    }
  }

  T pop() {
    if (top_ >= 0) {
      return data_[top_--];
    }
    return T();
  }

  T getTop() const {
    return data_[top_];
  }

  bool isEmpty() const {
    return top_ == -1;
  }

  bool isFull() const {
    return top_ == size - 1;
  }

 private:
  T data_[size];
  int top_;
};

#endif  // INCLUDE_TSTACK_H_
