// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

template<typename T>
class TPQueue {
 private:
  struct Node {
    T data_;
    Node* next_;

    explicit Node(const T& data, Node* next = nullptr)
        : data_(data), next_(next) {}
  };

  Node* head_;

 public:
  TPQueue() : head_(nullptr) {}

  ~TPQueue() {
    while (head_ != nullptr) {
      Node* temp = head_;
      head_ = head_->next_;
      delete temp;
    }
  }

  TPQueue(const TPQueue&) = delete;
  TPQueue& operator=(const TPQueue&) = delete;

  void push(const T& item) {
    Node* new_node = new Node(item);

    if (head_ == nullptr || item.prior > head_->data_.prior) {
      new_node->next_ = head_;
      head_ = new_node;
    } else {
      Node* current = head_;
      while (current->next_ != nullptr &&
             item.prior <= current->next_->data_.prior) {
        current = current->next_;
      }
      new_node->next_ = current->next_;
      current->next_ = new_node;
    }
  }

  T pop() {
    if (empty()) {
      throw std::runtime_error("pop from empty queue");
    }
    Node* temp = head_;
    T item_data = temp->data_;
    head_ = head_->next_;
    delete temp;
    return item_data;
  }

  bool empty() const {
    return head_ == nullptr;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
