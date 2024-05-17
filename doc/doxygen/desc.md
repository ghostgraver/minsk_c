# 说明

这是一个说明文件

```c++
#include "cpp-console/person/person.h"

#include "cpp-console/util/common_util.h"
#include "cpp-console/util/log_util.h"
#include "fmt/core.h"

Person::Person() {}

Person::Person(int age, std::string name) : m_age(age), m_name(name) {}

Person::~Person() {}

std::string Person::sayHello() {
    dzlog_info("%s", fmt::format(CommonUtil::getVersion()).c_str());
    return "Hello World";
}
```
