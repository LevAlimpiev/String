#include "cppstring.h"
#include <cstring>

String::String() : str_(nullptr), size_(0), capacity_(0) {
}

String::String(size_t size, char symbol) {
  Reserve(size);
  for (size_t i = 0; i < size; ++i) {
    str_[i] = symbol;
  }
  size_ = size;
}

String::String(const char* other) : str_(nullptr), size_(0), capacity_(0) {
  size_t other_size = strlen(other);
  Reserve(other_size);

  size_ = other_size;

  for (size_t i = 0; i < other_size; ++i) {
    str_[i] = other[i];
  }
}
// NO lint probably may be size > other, probably process logic
String::String(const char* other, size_t size) : str_(nullptr), size_(0), capacity_(0) {
  size_t len = std::min(strlen(other), size);

  Reserve(len);
  size_ = len;
  for (size_t i = 0; i < len; ++i) {
    str_[i] = other[i];
  }
}

String::String(const String& other) : str_(nullptr), size_(0), capacity_(0) {
  Reserve(other.size_);
  for (size_t i = 0; i < other.size_; ++i) {
    str_[i] = other.str_[i];
  }
  size_ = other.size_;
}

String::~String() {
  delete[] str_;
  size_ = 0;
  capacity_ = 0;
  str_ = nullptr;
}

void String::Reserve(size_t new_capacity) {
  new_capacity = std::max(new_capacity, capacity_);
  new_capacity = std::min(new_capacity, k_max_string_size_);

  auto new_str = new char[new_capacity];
  for (size_t i = 0; i < size_; ++i) {
    new_str[i] = str_[i];
  }

  delete[] str_;
  str_ = new_str;
  capacity_ = new_capacity;
}

size_t String::Size() const {
  return size_;
}

size_t String::Length() const {
  return size_;
}

size_t String::Capacity() const {
  return capacity_ * sizeof(char);
}

char& String::At(size_t index) {
  if (index >= size_) {
    throw StringOutOfRange{};
  }
  return str_[index];
}

const char& String::At(size_t index) const {
  if (index >= size_) {
    throw StringOutOfRange{};
  }
  return str_[index];
}

char& String::Front() {
  return str_[0];
}

const char& String::Front() const {
  return str_[0];
}

char& String::Back() {
  return str_[size_ - 1];
}

const char& String::Back() const {
  return str_[size_ - 1];
}

char* String::Data() {
  return str_;
}

char* String::CStr() {
  return str_;
}

const char* String::Data() const {
  return str_;
}

const char* String::CStr() const {
  return str_;
}

bool String::Empty() const {
  return size_ == 0;
}

void String::Clear() {
  while (size_ != 0) {
    PopBack();
  }
}

void String::Swap(String& other) {
  std::swap(str_, other.str_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

void String::PopBack() {
  str_[size_ - 1] = '\0';
  --size_;
}

void String::PushBack(const char symbol) {
  if (size_ == capacity_) {
    Reserve(std::max(static_cast<size_t>(1), capacity_ * k_capacity_multiplier_));
  }
  str_[size_] = symbol;
  ++size_;
}

void String::Resize(size_t new_size, char symbol) {
  if (size_ < new_size) {
    Reserve(new_size);
  }
  for (size_t i = size_; i < new_size; ++i) {
    str_[i] = symbol;
  }
  size_ = new_size;
}

void String::ShrinkToFit() {
  auto new_str = new char[size_];
  for (size_t i = 0; i < size_; ++i) {
    new_str[i] = str_[i];
  }

  delete[] str_;
  str_ = new_str;
  capacity_ = size_;
}

char& String::operator[](size_t index) {
  return str_[index];
}

const char& String::operator[](size_t index) const {
  return str_[index];
}

String& String::operator=(const String& other) {
  auto new_str = new char[other.size_];
  for (size_t i = 0; i < other.size_; ++i) {
    new_str[i] = other[i];
  }
  delete[] str_;

  str_ = new_str;
  size_ = other.size_;
  capacity_ = other.size_;
  return *this;
}

String& String::operator+=(const String& other) {

  auto new_str = new char[size_ + other.size_];
  size_t i = 0;
  for (; i < size_; ++i) {
    new_str[i] = str_[i];
  }
  for (; i - size_ < other.size_; ++i) {
    new_str[i] = other[i - size_];
  }

  delete[] str_;
  str_ = new_str;
  capacity_ = size_ + other.size_;
  size_ = size_ + other.size_;

  return *this;
}

String String::operator+(const String& other) const {
  String new_string;
  new_string.Reserve(size_ + other.size_);
  for (size_t i = 0; i < size_; ++i) {
    new_string.PushBack(str_[i]);
  }
  for (size_t i = 0; i < other.size_; ++i) {
    new_string.PushBack(other[i]);
  }
  return new_string;
}

bool String::operator<(const String& other) const {
  for (size_t i = 0; i < std::min(size_, other.size_); ++i) {
    if (str_[i] < other[i]) {
      return true;
    }
    if (str_[i] > other[i]) {
      return false;
    }
  }
  return size_ < other.size_;
}

bool String::operator>(const String& other) const {
  for (size_t i = 0; i < std::min(size_, other.size_); ++i) {
    if (str_[i] > other[i]) {
      return true;
    }
    if (str_[i] < other[i]) {
      return false;
    }
  }
  return size_ > other.size_;
}

bool String::operator<=(const String& other) const {
  for (size_t i = 0; i < std::min(size_, other.size_); ++i) {
    if (str_[i] < other[i]) {
      return true;
    }
    if (str_[i] > other[i]) {
      return false;
    }
  }
  return size_ <= other.size_;
}

bool String::operator>=(const String& other) const {
  for (size_t i = 0; i < std::min(size_, other.size_); ++i) {
    if (str_[i] > other[i]) {
      return true;
    }
    if (str_[i] > other[i]) {
      return false;
    }
  }
  return size_ >= other.size_;
}

bool String::operator==(const String& other) const {
  for (size_t i = 0; i < std::min(size_, other.size_); ++i) {
    if (str_[i] != other[i]) {
      return false;
    }
  }
  return size_ == other.size_;
}

bool String::operator!=(const String& other) const {
  return !(*this == other);
}

std::ostream& String::operator<<(std::ostream& out) {
  for (size_t i = 0; i < this->size_; ++i) {
    out << this->str_[i];
  }
  return out;
}

std::ostream& operator<<(std::ostream& out, const String& str) {
  for (size_t i = 0; i < str.Size(); ++i) {
    out << str[i];
  }
  return out;
}

String operator+(const char* c_str, const String& str) {
  return String(c_str) + str;
}
