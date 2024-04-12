#include <cassert>
#include <mutex>
#include <string>
#include <unordered_map>

#include "../json_helper.h"
//#include "logger/log.h"

class Foo {
 public:
  struct SubClass {
    std::string name;
    float pi = 0.0;

    JSON_HELPER(name, pi);
  };

  enum Color {
    kUnknown = 0,
    kBlue = 1,
    kRead = 2,
    kBlack = 3,
  };

  enum class Gender {
    kUnknown = 0,
    kMale = 1,
    kFemale = 2,
  };

 public:
  // basic type
  int32_t money = 0;
  int64_t uid = 0;
  uint32_t age = 0;
  double birthday = 0;
  std::string name;

  // stl container
  std::vector<int> list;
  std::set<std::string> set;
  // std::unordered_map<std::string, bool> map;
  std::unordered_map<int, int> map;

  // enum
  Color color;

  // enum class
  Gender gender;

  // nested class
  SubClass sub_class;

  // static variable
  static constexpr uint64_t id = 100;

  // pointer
  int* pi = nullptr;
  std::string* ps = nullptr;
  SubClass* p_sub_class = nullptr;

  //  skip types
  std::mutex mtx_;

 public:
  JSON_HELPER(money, uid, age, birthday, name, list, set, color, gender, sub_class, map, pi, ps, p_sub_class);
};
