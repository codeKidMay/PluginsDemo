#include "TestJsonConvert.h"

void Foo::Serialize()
{
    Foo foo;
    std::string json_str;
    ::json_helper::Marshal(foo, &json_str, true);
    std::cout << "============ with style ============" << std::endl;
    std::cout << json_str << std::endl;

    std::cout << "=========== without style ==========" << std::endl;
    ::json_helper::Marshal(foo, &json_str);
    std::cout << json_str << std::endl;
}

void Foo::Deserialize()
{
    std::string json_str = R"(
{
  "age": 24,
  "birthday": 3.1099999999999999,
  "color": 1,
  "gender": 1,
  "list": [-5, 10, 100, 20033],
  "map": {
    "10": 20,
    "30": 123
  },
  "money": -1,
  "name": "foo",
  "p_sub_class": {
    "name": "p_sub_class",
    "pi": 3.1415925025939941
  },
  "pi": "nullptr",
  "ps": "string",
  "set": ["cc", "kkk-mmm"],
  "sub_class": {
    "name": "sub_class",
    "pi": 3.1414999961853027
  },
  "uid": 1234567890
}
    )";

    Foo foo;

    // 读取成 ::Json::Value 再转成 String
    // 保证是一个合法 Json
    {
        Json::Value root;
        Json::Reader reader;
        if (!reader.parse(json_str, root)) {
            std::cout << "jsoncpp parse fail!" << std::endl;
        }
        Json::StyledWriter writer;
        std::cout << "======================= jsoncpp =======================" << std::endl;
        std::cout << "jsoncpp str:" << writer.write(root) << std::endl;
        std::cout << "=======================================================" << std::endl;
    }

    json_helper::Unmarshal(json_str, &foo);
    //std::cout << ::json_helper::ToStringFormatted(foo) << std::endl;
}
