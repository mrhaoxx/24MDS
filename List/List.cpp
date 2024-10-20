#include <iostream>
#include "List.h"  // 假设List类的声明保存在List.h文件中

int main()
{
    // 测试默认构造函数
    List<int> list1;
    std::cout << "List1 initialized. Is empty: " << std::boolalpha << list1.empty() << std::endl;

    // 测试push_back和size函数
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    std::cout << "List1 after adding 1, 2, 3 (via push_back): " << std::endl;
    for (auto it = list1.begin(); it != list1.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << "\nList1 size: " << list1.size() << std::endl;

    // 测试push_front函数
    list1.push_front(0);
    std::cout << "List1 after adding 0 (via push_front): " << std::endl;
    for (auto it = list1.begin(); it != list1.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << "\nList1 size: " << list1.size() << std::endl;

    // 测试front和back函数
    if (!list1.empty()) {
        std::cout << "Front element: " << list1.front() << std::endl;
        std::cout << "Back element: " << list1.back() << std::endl;
    }

    // 测试pop_front和pop_back函数
    if (!list1.empty()) {
        list1.pop_front();
    }
    if (!list1.empty()) {
        list1.pop_back();
    }
    std::cout << "List1 after pop_front and pop_back: " << std::endl;
    for (auto it = list1.begin(); it != list1.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << "\nList1 size: " << list1.size() << std::endl;

    // 测试拷贝赋值运算符
    List<int> list2;
    list2 = list1;
    std::cout << "List2 (assigned from List1 using copy assignment): " << std::endl;
    for (auto it = list2.begin(); it != list2.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << "\nList2 size: " << list2.size() << std::endl;

    // 测试移动赋值运算符
    List<int> list3;
    list3 = std::move(list1);
    std::cout << "List3 (assigned from List1 using move assignment): " << std::endl;
    for (auto it = list3.begin(); it != list3.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << "\nList3 size: " << list3.size() << std::endl;

    // 测试插入到指定位置
    if (list3.size() > 1) {
        auto it = list3.begin();
        ++it; // 指向第二个元素
        list3.insert(it, 99);
        std::cout << "List3 after inserting 99 at second position: " << std::endl;
        for (auto it = list3.begin(); it != list3.end(); ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << "\nList3 size: " << list3.size() << std::endl;
    }

    // 测试插入右值到指定位置
    if (list3.size() > 2) {
        auto it = list3.begin();
        ++it; // 指向第三个元素
        list3.insert(it, std::move(88));
        std::cout << "List3 after inserting 88 (as rvalue) at third position: " << std::endl;
        for (auto it = list3.begin(); it != list3.end(); ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << "\nList3 size: " << list3.size() << std::endl;
    }

    // 测试erase(iterator, iterator) 删除范围
    if (list3.size() > 2) {
        auto it1 = list3.begin();
        auto it2 = list3.begin();
        ++it2;
        ++it2; // 指向第三个元素
        if (it1 != list3.end() && it2 != list3.end()) {
            list3.erase(it1, it2); // 删除前两个元素
            std::cout << "List3 after erasing first two elements: " << std::endl;
            for (auto it = list3.begin(); it != list3.end(); ++it)
            {
                std::cout << *it << " ";
            }
            std::cout << "\nList3 size: " << list3.size() << std::endl;
        }
    }

    // 测试clear函数
    list3.clear();
    std::cout << "List3 after clearing all elements: Is empty: " << list3.empty() << std::endl;

    // 测试在空列表上调用pop_front和pop_back
    try
    {
        list3.pop_front();
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception caught on pop_front with empty list: " << e.what() << std::endl;
    }

    try
    {
        list3.pop_back();
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception caught on pop_back with empty list: " << e.what() << std::endl;
    }

    // 测试反向迭代器
    List<int> list4 = {10, 20, 30, 40, 50};
    std::cout << "List4 in reverse order (using -- operator): " << std::endl;
    if (!list4.empty()) {
        for (auto it = --list4.end(); it != --list4.begin(); --it)
        {
            std::cout << *it << " ";
        }
    }
    std::cout << "\nList4 size: " << list4.size() << std::endl;

    return 0;
}
