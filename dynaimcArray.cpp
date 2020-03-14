#include <iostream>

//初始化数据默认大小
constexpr int default_array_cap = 10;
constexpr int default_array_length = 1;
constexpr int default_array_from_index = 0;

template <class T>
class dynarray {
  //------------------
  //      data member
  //------------------
  int capacity_;  // array total size
  int length_;    // current array size
  int front_index;
  T* array_;  // pointer array

  bool dynaimcResize(const int new_capacity) {
    auto* temp = new T[new_capacity];
    // copy array to new array with new capacity
    for (auto i{0}; i < length_; ++i) {
      // transfer ownership of every element
      temp[i] = array_[(front_index + i) % capacity_];
    }
    // free old array
    delete[] array_;
    // point to *temp
    capacity_ = new_capacity;
    // reset front index to 0
    front_index = 0;
    array_ = temp;
    temp = nullptr;  // pointer dangling
    // return statement
    return true;
  }

 public:
  //--------------------
  //       constructors
  //--------------------
  //移动构造
  explicit dynarray(T&& r_ref)
      : capacity_{default_array_cap},
        length_{default_array_length},
        front_index{default_array_from_index} {
    //分配内存
    array_ = new T[capacity_];
    //调用移动函数，赋值数组0位值
    array_[0] = std::move(r_ref);
  }

  explicit dynarray(): capacity_{default_array_cap},
        length_{0},
        front_index{default_array_from_index}{
     //分配内存
    array_ = new T[capacity_];
  }
  
  //拷贝构造
  explicit dynarray(const T& data)
      : capacity_{default_array_cap},
        length_{default_array_length},
        front_index{default_array_from_index} {
    //分配内存
    array_ = new T[capacity_];
    //调用拷贝赋值，赋值数组0位值
    array_[0] = data;
  }
  //析构释放内存
  ~dynarray() {
    delete[] array_;
    array_ = nullptr;
  }
  //-----------------
  // 公共方法
  //-----------------

  // add l value at the end of dynarray
  bool append(const T& data)  {
    if (array_ == nullptr) {
      array_ = new T[default_array_cap];
    }
    //扩容
    else if (length_ >= capacity_) {
      dynaimcResize(static_cast<int>(capacity_ * 1.5));
    }
    // insert at length index module capacity
    array_[(front_index + length_) % capacity_] = data;
    // increase length
    ++length_;
    return true;
  }

  // add r value at the end of dynarray
  bool append(T&& r_ref)  {
    if (array_ == nullptr) {
      array_ = new T[default_array_cap];
    }
    // 扩容
    else if (length_ >= capacity_) {
      dynaimcResize(static_cast<int>(capacity_ * 1.5));
    }
    // add end index length
    array_[(front_index + length_) % capacity_] = std::move(r_ref);
    // increase length
    ++length_;
    return true;
  }

  // remove last element
  bool pop()  {
    if (length_ == 0) {
      throw std::range_error("Array length_ is 0");
    }
    //减容操作
    if (length_ < (capacity_ / 5)) {
      dynaimcResize(capacity_ / 2);
    }
    --length_;
    return true;
  }

  T& get_at(const int index) const {
    if (index >= length_) {
      throw std::out_of_range("Out of bounds index");
    }
    return array_[(front_index + index) % capacity_];
  }
};


int main() {
  //初始化动态数组
  dynarray<char> arraylist;
  //尾部添加元素
  arraylist.append('b');
  arraylist.append('f');
  std::cout << arraylist.get_at(1) << std::endl;
  arraylist.pop();
  std::cout << arraylist.get_at(0) << std::endl;
}
