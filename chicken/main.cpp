#include <iostream>

#include "Chicken.cpp"

int main()
{
    auto print = [](const Chicken &c)
    { std::cout << "Hi, everyone! My name is " << c.getName() << ", I am " << c.getAge() << " years old." << std::endl; };
    Chicken c(24, "Kunkun");
    print(c);
    Chicken d;
    d = c;
    print(d); // 测试【赋值运算符】是否正确，能正确输出给 20 分
    Chicken a = c;
    print(a); // 测试【赋值构造函数】是否正确，能正确输出给 20 分
    c.setName("Xukun Cai");
    print(c);
    print(a);
    print(d); // 测试是否为【深度复制】，本行与上两行能正确输出给 20 分
    Chicken b;
    b = d = c;
    print(b);
    print(d); // 测试【连续赋值】功能，本行与上一行能正确输出给 20 分

    b.setName("test");
    b.setName(b.getName());
    print(b);

    return 0;
}