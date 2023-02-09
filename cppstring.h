#pragma once
#include <stdexcept>
#include <iostream>

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
  char* str_;
  size_t size_;
  size_t capacity_;
  const size_t k_capacity_multiplier_ = 2;

 public:
  String();
  String(size_t size, char symbol);
  String(const char* other);  // NOLINT
  String(const char* other, size_t size);

  String(const String& other);
  ~String();

  void Reserve(size_t new_capacity);
  size_t Size() const;
  size_t Length() const;
  size_t Capacity() const;

  char& At(size_t index);
  const char& At(size_t index) const;
  char& Front();
  const char& Front() const;
  char& Back();
  const char& Back() const;
  char* Data();
  char* CStr();
  const char* Data() const;
  const char* CStr() const;

  bool Empty() const;
  void Clear();
  void Swap(String& other);
  void PopBack();
  void PushBack(const char symbol);
  void Resize(size_t new_size, char symbol);
  void ShrinkToFit();

  char& operator[](size_t index);
  const char& operator[](size_t index) const;
  String& operator=(const String& other);
  String& operator+=(const String& other);
  String operator+(const String& other) const;
  bool operator<(const String& other) const;
  bool operator>(const String& other) const;
  bool operator<=(const String& other) const;
  bool operator>=(const String& other) const;
  bool operator==(const String& other) const;
  bool operator!=(const String& other) const;
  std::ostream& operator<<(std::ostream& out);
};

std::ostream& operator<<(std::ostream& out, const String& str);
String operator+(const char* c_str, const String& str);