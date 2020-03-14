#include <iostream>

template <class T>
class node {
 private:
 public:
  node<T>* next_;
  T data;
  node(T r_ref) : next_{nullptr} { data = r_ref; }
  ~node() { next_ = nullptr; }
};

template <class T>
class singleList {
 private:
  //头结点
  node<T>* head_;
  int length_;

 public:
  explicit singleList() : head_{nullptr}, length_(0) {}
  ~singleList() { head_ = nullptr; }

  // add element at the end of list
  bool append(T r_ref) {
    node<T>* newNode = new node<T>(r_ref);
    if (length_ == 0) {
      head_ = newNode;
      length_ = 1;
    } else {
      auto* lastNode = linkedfast();
      lastNode->next_ = newNode;
      ++length_;
      lastNode = nullptr;
    }
    newNode = nullptr;
    return true;
  }

  // remove element at the end of list
  bool pop() {
    if (length_ == 0) {
      throw std::range_error("list length is 0");
    }
    auto* tempnode_ = head_;
    while (tempnode_->next_ != nullptr) {
      tempnode_ = tempnode_->next_;
    }
    tempnode_ = nullptr;
  }

  node<T>* linkedfast() {
    auto* tempnode_ = head_;
    while (tempnode_->next_ != nullptr) {
      tempnode_ = tempnode_->next_;
    }
    return tempnode_;
  }

  //根据指定索引查找元素
  T get(int index) {
    if (index < 0 || index > length_) {
      throw std::out_of_range("out of bounds index");
    }
    if (length_ == 0) {
      throw std::range_error("list length is 0");
    }
    auto* node = head_;
    while (index > 0) {
      node = node->next_;
      --index;
    }
    T data = node->data;
    node == nullptr;
    return data;
  }
};

int main() {
  singleList<int> list;
  int count = 2;
  for (size_t i = 0; i < count; i++) {
    list.append(i);
  }
  list.pop();
  std::cout << list.get(0) << std::endl;
}
