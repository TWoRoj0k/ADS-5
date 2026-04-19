// Copyright 2025 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
  static const int kSize = size;
  T data[kSize];
  int topIndex_;

 public:
  TStack() : topIndex_(-1) {}

  void push(const T& value) {
    if (topIndex_ < kSize - 1) {
      data[++topIndex_] = value;
    }
  }

  T pop() {
    if (topIndex_ >= 0) {
      return data[topIndex_--];
    }
    return T();
  }

  T top() const {
    if (topIndex_ >= 0) {
      return data[topIndex_];
    }
    return T();
  }

  bool isEmpty() const {
    return topIndex_ == -1;
  }

  int getSize() const {
    return topIndex_ + 1;
  }
};

#endif  // INCLUDE_TSTACK_H_
