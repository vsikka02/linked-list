// Copyright (c) 2020 CS126SP20. All rights reserved.

#include "ll.h"

#include <cassert>
#include <utility>
#include <vector>

// TODO(you): Implement these methods.

namespace cs126linkedlist {

template <typename ElementType>
LinkedList<ElementType>::LinkedList() {
  head_ = nullptr;
  size_ = 0;
}

template <typename ElementType>
LinkedList<ElementType>::LinkedList(const std::vector<ElementType>& values) {
  head_ = nullptr;
  size_ = 0;
  for (ElementType value: values) {
    push_back(value);
  }
}

// Copy constructor
template <typename ElementType>
LinkedList<ElementType>::LinkedList(const LinkedList<ElementType>& source) {
  head_ = nullptr;
  size_ = 0;
  for (ElementType value: source) {
    push_back(value);
  }
}

// Move constructor
template <typename ElementType>
LinkedList<ElementType>::LinkedList(LinkedList<ElementType>&& source) noexcept {
  head_ = source.head_;
  size_ = source.size();

  source.head_ = nullptr;
  source.size_ = 0;
}

// Destructor
template <typename ElementType>
LinkedList<ElementType>::~LinkedList() {
}

// Copy assignment operator
template <typename ElementType>
LinkedList<ElementType>& LinkedList<ElementType>::operator=(
    const LinkedList<ElementType>& source) {
  if (!(this->empty())) {
    this->clear();
  }
  for (ElementType value: source) {
    push_back(value);
  }
  return *this;
}

// Move assignment operator
template <typename ElementType>
LinkedList<ElementType>& LinkedList<ElementType>::operator=(
    LinkedList<ElementType>&& source) noexcept {
  if (!(this->empty())) {
    this->clear();
  }
  head_ = source.head_;
  size_ = source.size();
  source.head_ = nullptr;
  source.size_ = 0;

  return *this;
}

template <typename ElementType>
void LinkedList<ElementType>::push_front(const ElementType& value) {
  Node *node = new Node();
  node->data_ = value;
  node->next_ = head_;
  head_ = node;
  size_++;
}

template <typename ElementType>
void LinkedList<ElementType>::push_back(const ElementType& value) {
  Node* current_node = head_;
  size_t current_index = 0;
  if (head_ == nullptr) {
    push_front(value);
    return;
  }
  for (iterator it = begin(); it != end(); ++it) {
    if (current_index == size_ - 1) {
      Node *node = new Node();
      node->data_ = value;
      node->next_ = nullptr;
      current_node->next_ = node;
    }
    current_node = current_node->next_;
    current_index++;
  }
  size_++;
}

template <typename ElementType>
ElementType LinkedList<ElementType>::front() const {
  return head_->data_;
}

template <typename ElementType>
ElementType LinkedList<ElementType>::back() const {
  Node* current_node = head_;
  size_t current_index = 0;
  Node* last_node;
  for (const_iterator it = begin(); it != end(); ++it) {
    if (current_index == size_ - 1) {
      last_node = current_node;
    }
    current_node = current_node->next_;
    current_index++;
  }
  return last_node->data_;
}

template <typename ElementType>
void LinkedList<ElementType>::pop_front() {
  if (empty()) {
    return;
  }
  Node *temp = head_;
  head_ = head_ -> next_;
  delete temp;

  size_--;
}

template <typename ElementType>
void LinkedList<ElementType>::pop_back() {
  if(empty()) {
    return;
  }
  if (size_ == 1) {
    pop_front();
    return;
  } else {
    Node* current_node = head_;
    size_t current_index = 0;
    for (iterator it = begin(); it != end(); ++it) {
      if (current_index == size_ - 2) {
        Node* remove = current_node->next_;
        current_node->next_ = nullptr;
        delete remove;
        break;
      }
      current_node = current_node->next_;
      current_index++;
    }
  }
  size_ --;
}

template <typename ElementType>
size_t LinkedList<ElementType>::size() const {
  return size_;
}

template <typename ElementType>
bool LinkedList<ElementType>::empty() const {
  return size_ == 0 && head_ == nullptr;
}

template <typename ElementType>
void LinkedList<ElementType>::clear() {
  Node *current_node = head_;
  for (iterator it = begin(); it != end(); ++it) {
    pop_front();
    current_node = current_node -> next_;
  }
}

template <typename ElementType>
std::ostream& operator<<(std::ostream& os,
                         const LinkedList<ElementType>& list) {
  for(ElementType value: list) {
    os << "Data: " << value<< std::endl;
  }
  return os;
}

template <typename ElementType>
void LinkedList<ElementType>::RemoveNth(size_t n){
  if (n >= size_) {
    throw std::out_of_range("Index out of Bounds");
  }
  if (size_ == 0) {
    head_ = nullptr;
    size_ = 0;
  }
  size_t current_index = 0;
  Node* current_node = head_;
  if (n == 0) {
    pop_front();
    return;
  }
  for (iterator it = begin(); it != end(); ++it) {
    if (current_node->next_ == nullptr) {
      pop_back();
      break;
    } else if (current_index == n - 1) {
      Node* temp = current_node->next_;
      current_node->next_ = current_node->next_->next_;
      delete temp;
      break;
    }
    current_node = current_node->next_;
    current_index++;
  }
  size_--;
}

template <typename ElementType>
void LinkedList<ElementType>::RemoveOdd() {
  if (size_ <= 1) {
    return;
  }
  size_t current_index = 0;
  for (iterator it = begin(); it != end(); ++it) {
    if (current_index >= 1) {
      RemoveNth(current_index);
    }
    current_index++;
    if (current_index >= size_) {
      return;
    }
  }
}

template <typename ElementType>
bool LinkedList<ElementType>::operator==(
    const LinkedList<ElementType>& rhs) const {
  Node* current_node = head_;
  Node* other_node = rhs.head_;
  while (current_node != nullptr && other_node != nullptr) {
    if (current_node->data_ != other_node->data_) {
      return false;
    }
    current_node = current_node->next_;
    other_node = other_node->next_;
  }
  return (current_node == nullptr && other_node == nullptr);
}

template <typename ElementType>
bool LinkedList<ElementType>::operator!=(
    const LinkedList<ElementType>& rhs) const {
  Node* current_node = head_;
  Node* other_node = rhs.head_;
  while (current_node != nullptr && other_node != nullptr) {
    if (current_node->data_ != other_node->data_) {
      return true;
    }
    current_node = current_node->next_;
    other_node = other_node->next_;
  }
  return !(current_node == nullptr && other_node == nullptr);
}

template <typename ElementType>
typename LinkedList<ElementType>::iterator& LinkedList<ElementType>::iterator::
operator++() {
  current_ = current_->next_;
  return *this;
}

template <typename ElementType>
ElementType& LinkedList<ElementType>::iterator::operator*() const {
  return current_->data_;
}

template <typename ElementType>
bool LinkedList<ElementType>::iterator::operator!=(
    const typename LinkedList<ElementType>::iterator& other) const {
  return current_ != other.current_;
}

template <typename ElementType>
typename LinkedList<ElementType>::iterator LinkedList<ElementType>::begin() {
  return iterator(head_);
}

template <typename ElementType>
typename LinkedList<ElementType>::iterator LinkedList<ElementType>::end() {
  return iterator(nullptr);
}

template <typename ElementType>
typename LinkedList<ElementType>::const_iterator&
LinkedList<ElementType>::const_iterator::operator++() {
  current_ = current_->next_;
  return *this;
}

template <typename ElementType>
const ElementType& LinkedList<ElementType>::const_iterator::operator*() const {
  return current_->data_;
}

template <typename ElementType>
bool LinkedList<ElementType>::const_iterator::operator!=(
    const typename LinkedList<ElementType>::const_iterator& other) const {
  return current_ != other.current_;
}

template <typename ElementType>
typename LinkedList<ElementType>::const_iterator
LinkedList<ElementType>::begin() const {
  return const_iterator(head_);
}

template <typename ElementType>
typename LinkedList<ElementType>::const_iterator LinkedList<ElementType>::end()
    const {
  return const_iterator(nullptr);
}

}  // namespace cs126linkedlist
