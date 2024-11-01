#include <codecvt>

/**
 * 1. Convert utf-16 to utf-8 or vice versa
 * 2. Remove spaces from a string
 */

// 1. Convert utf-16 to utf-8 or vice versa
// https://en.cppreference.com/w/cpp/locale/codecvt_utf8_utf16
void convert_strings() {
  std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> convert;
  std::string utf8 = convert.to_bytes(u"Hello, world");
  std::u16string utf16 = convert.from_bytes("Hello, world");
}

// 2. Remove spaces from a string
void remove_spaces() {
  std::string s = "Hello, world";
  std::remove_if(s.begin(), s.end(), isspace);
}