﻿#pragma once

#include <string>

#include "json/json.h"
#include "marshal.h"
#include "unmarshal.h"

namespace json_helper {

template <typename T>
bool Unmarshal(const std::string& str, T* const obj) {
  Json::Value root;
  Json::Reader reader;
  if (!reader.parse(str, root)) {
    std::cout << "[JsonHelper][Warning] jsoncpp parse fail, str: " << str << std::endl;
    return false;
  }
  return Unmarshal(root, obj);
}

template <typename T>
bool Unmarshal(const char* str, T* const obj) {
  return Unmarshal(std::string(str), obj);
}

template <typename T>
bool Marshal(const T& obj, std::string* const json_str, bool with_style = false) {
  Json::Value root;

  // 允许部分字段序列化失败
  bool ret = Marshal(obj, &root);
  // if (!Marshal(obj, &root)) {
  //     *json_str = "";
  //     return false;
  // }

  if (with_style) {
    Json::StyledWriter writer;
    *json_str = writer.write(root);
  } else {
    Json::FastWriter writer;
    *json_str = writer.write(root);
  }

  return ret;
}

template <typename T>
std::string ToString(const T& obj) {
  std::string res;
  if (!Marshal(obj, &res, false)) {
    return "";
  }
  if (res.back() == '\n') {
    res.erase(res.size() - 1);
  }
  return res;
}

template <typename T>
std::string ToStringFormatted(const T& obj) {
  std::string res;
  if (!Marshal(obj, &res, true)) {
    return "";
  }
  if (res.back() == '\n') {
    res.erase(res.size() - 1);
  }
  return res;
}

#define JSON_HELPER(...) \
  JSON_HELPER_UNMARSHAL_MEMBER_FUNCTION(__VA_ARGS__) JSON_HELPER_MARSHAL_MEMBER_FUNCTION(__VA_ARGS__)

}  // namespace json_helper
