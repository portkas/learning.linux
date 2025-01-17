// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// A sample program demonstrating using Google C++ testing framework.

#ifndef GOOGLETEST_SAMPLES_SAMPLE3_INL_H_
#define GOOGLETEST_SAMPLES_SAMPLE3_INL_H_

#include <stddef.h>

// Queue is a simple queue implemented as a singled-linked list.
//
// The element type must support copy constructor.
template <typename E>  // E is the element type
class Queue;

// QueueNode is a node in a Queue, which consists of an element of
// type E and a pointer to the next node.
template <typename E>  // E is the element type
class QueueNode {
  // 通过将Queue类声明为QueueNode的友元类，Queue可以访问QueueNode的私有成员。
  // 因为Queue类需要直接操作队列节点（如添加新节点、删除节点等）。
  friend class Queue<E>;    // 为什么声明一个友元？为了让Queue访问QueueNode？？？

 public:
  // Gets the element in this node.
  const E& element() const { return element_; }

  // Gets the next node in the queue.
  QueueNode* next() { return next_; }
  const QueueNode* next() const { return next_; }

 private:
  // Creates a node with a given element value.  The next pointer is
  // set to NULL.
  explicit QueueNode(const E& an_element)
      : element_(an_element), next_(nullptr) {}

  // We disable the default assignment operator and copy c'tor.
  // 通过将赋值操作符和拷贝构造函数声明为私有，禁止QueueNode的复制！！！
  const QueueNode& operator=(const QueueNode&);
  QueueNode(const QueueNode&);

  E element_;
  QueueNode* next_;
};

template <typename E>  // E is the element type.
class Queue {
 public:
  // Creates an empty queue.
  Queue() : head_(nullptr), last_(nullptr), size_(0) {}

  // D'tor.  Clears the queue.
  ~Queue() { Clear(); }

  // Clears the queue.
  // 删除队列中所有的节点，并重置头节点，尾节点，队列大小
  void Clear() {
    if (size_ > 0) {
      // 1. Deletes every node.
      QueueNode<E>* node = head_;
      QueueNode<E>* next = node->next();
      for (;;) {
        delete node;
        node = next;
        if (node == nullptr) break;
        next = node->next();
      }

      // 2. Resets the member variables.
      head_ = last_ = nullptr;
      size_ = 0;
    }
  }

  // Gets the number of elements.
  size_t Size() const { return size_; }

  // 提供两种不同版本的 Head() 和 Last() 函数是为了支持不同的使用场景：非 const 上下文和 const 上下文
  // 在某些情况下，您可能需要修改队列中的节点（例如，更新节点的数据或重新链接节点），这时需要非 const 版本。
  // 当您有一个 const 的 Queue 对象时，只能调用 const 版本的成员函数。

  // Gets the first element of the queue, or NULL if the queue is empty.
  QueueNode<E>* Head() { return head_; }
  const QueueNode<E>* Head() const { return head_; }

  // Gets the last element of the queue, or NULL if the queue is empty.
  QueueNode<E>* Last() { return last_; }
  const QueueNode<E>* Last() const { return last_; }

  // Adds an element to the end of the queue.  A copy of the element is
  // created using the copy constructor, and then stored in the queue.
  // Changes made to the element in the queue doesn't affect the source
  // object, and vice versa.

  // 将一个元素添加到队列的末尾，使用元素的拷贝构造函数创建一个新的节点，并将其添加到队列的末尾
  void Enqueue(const E& element) {
    QueueNode<E>* new_node = new QueueNode<E>(element);

    if (size_ == 0) {
      head_ = last_ = new_node;
      size_ = 1;
    } else {
      last_->next_ = new_node;
      last_ = new_node;
      size_++;
    }
  }

  // Removes the head of the queue and returns it.  Returns NULL if the queue is empty.
  // 移除队列的头元素，如果队列为空，则返回nullptr，否则，返回头节点元素并删除头节点
  E* Dequeue() {
    if (size_ == 0) {
      return nullptr;
    }

    const QueueNode<E>* const old_head = head_;
    head_ = head_->next_;
    size_--;
    if (size_ == 0) {
      last_ = nullptr;
    }

    E* element = new E(old_head->element());
    delete old_head;

    return element;
  }

  // Applies a function/functor on each element of the queue, and
  // returns the result in a new queue.  The original queue is not
  // affected.
  // 对队列中的每一个元素应用一个函数或函数对象，并返回一个新队列，其中包含应用函数后的元素，原始队列不受影响
  template <typename F>
  Queue* Map(F function) const {
    Queue* new_queue = new Queue();
    for (const QueueNode<E>* node = head_; node != nullptr;
         node = node->next_) {
      new_queue->Enqueue(function(node->element()));
    }

    return new_queue;
  }

 private:
  QueueNode<E>* head_;  // The first node of the queue.
  QueueNode<E>* last_;  // The last node of the queue.
  size_t size_;         // The number of elements in the queue.

  // We disallow copying a queue.
  Queue(const Queue&);
  const Queue& operator=(const Queue&);
};

#endif  // GOOGLETEST_SAMPLES_SAMPLE3_INL_H_
