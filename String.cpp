#include <iostream>
#include <string>

#include "cppstring.h";
void GetInfo(const String& s) {
  std::cout << '\n';
  std::cout << s << "\n";
  std::cout << "capacity: " << s.Capacity() << "   "
            << "size: " << s.Size() << "\n";
  std::cout << '\n';
}

#include <cassert>

void TestPushAndPop() {
  String s;
  s.PushBack('a');
  s.PushBack('a');
  s.PushBack('a');
  s.PopBack();
  s.PopBack();
  s.PopBack();
  s.PushBack('a');
  s.PushBack('a');
  s.PushBack('a');
  s.PushBack('a');
  s.PushBack('a');
  s.PushBack('a');
  s.PushBack('a');
  s.PushBack('a');
  s.PushBack('a');
  s.Clear();
  int n = 1e4;
  for (int i = 0; i < n; ++i) {
    s.PushBack('a');
    assert(i + 1 == s.Size());
    if (i < 1000) {
      String a = s;
    }
  }
  s.ShrinkToFit();
  s.Clear();
  s.ShrinkToFit();
  for (int i = 0; i < n; ++i) {
    s.PushBack('a');
    s += "bcfd";
  }
  s.Clear();
  s.ShrinkToFit();
  assert(s.Size() == 0 && s.Capacity() == 0);
  assert(s.Empty() == true);
  std::cout << "TestPushAndPop passed\n";
}

void TestSwap() {
  String a = "aba";
  String b = "c";
  a.Swap(b);
  assert(a == "c" && b == "aba");
  String c = "klm";
  c.Swap(c);
  assert(c == "klm");
  std::cout << "TestSwap passed\n";
}

void TestGetMethods() {
  String a = "abacabayh";
  assert(a[0] == a.At(0));
  assert(a[0] == a.Front());
  assert(a[a.Size() - 1] == a.Back());
  assert(a[0] == *a.Data());
  std::cout << "TestGetMethods passed\n";
}

void Print(String s) {
  std::cout << '\n';
  std::cout << "capacity: " << s.Capacity() << "   "
            << "size: " << s.Size() << "\n";
  for (size_t i = 0; i < s.Size(); ++i) {
    std::cout << s[i];
  }
  std::cout << '\n';
}

void GetInfoStdString(std::string s) {
  std::cout << '\n';
  std::cout << s << "\n";
  std::cout << "capacity: " << s.capacity() << "   "
            << "size: " << s.size() << "\n";
  std::cout << '\n';
}
void TestCopy() {
  String s = "a";
  s += s;
  assert(s == "aa");
  s = s + s;
  assert(s == "aaaa");
  s.Clear();
  s += s;
  assert(s == "");
  s += "aba";
  assert(s == "aba");
  s = "aba" + s;
  assert(s == "abaaba");
  std::cout << "TestCopy passed\n";
}

void TestResize() {
  String s = "abcdeg";
  s.Resize(3, 'y');
  assert(s == "abc");
  s.Resize(5, 'y');
  assert(s == "abcyy");
  std::cout << "TestResize passed\n";
}

void TestConstructors() {
  String a(5, 'a');
  assert(a == "aaaaa");
  String b(a);
  assert(b == "aaaaa");
  String c(b);
  assert(c == b);
  c.Clear();
  assert(c == "");
  assert(a == "aaaaa");
  assert(b == "aaaaa");
  std::cout << "TestConstructors passed\n";
}

int main() {
  TestGetMethods();
  TestPushAndPop();
  TestSwap();
  TestCopy();
  TestConstructors();
  TestResize();
  return 0;
}
