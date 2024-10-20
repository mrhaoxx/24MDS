#ifndef __LIST_MARK__
#define __LIST_MARK__

#include <utility>
#include <initializer_list>
#include <stdexcept>

/**
 * @brief 课本上的 List 实现.
 *
 * @tparam Object List 中的元素类型.
 */
template <typename Object>
class List
{
private:
    /**
     * @brief 节点的定义. 因为定义的是私有类，所以不需要考虑命名冲突.
     * 外部不会访问到这个类. 因为 struct 默认是 public 的. 所以在
     * List 类内部，Node 类的成员变量和成员函数都是可以直接访问的.
     */
    struct Node
    {
        Object data; /**<! 节点内存放的数据. */
        Node *prev;  /**<! 指向前一个节点的指针. */
        Node *next;  /**<! 指向后一个节点的指针. */
        /**
         * @brief 列表型节点的构造函数. 注意这里的默认参数的使用.
         * 使我们同时拥有一个默认构造函数和一个带参数的构造函数.
         *
         * @param d 节点内存放的数据. 默认为空.
         * @param p 前一个节点的指针. 默认为空.
         * @param n 后一个节点的指针. 默认为空.
         */
        Node(const Object &d = Object{}, Node *p = nullptr,
             Node *n = nullptr)
            : data{d}, prev{p}, next{n} {}

        /**
         * @brief 移动构造函数. 唯一的区别是节点数据是一个右值引用. 因此以 std::move 的方式传递.
         *
         * @param d 节点内存放的数据. 只有这里是一个显式的右值引用，才会调用这个构造函数.
         * @param p 前一个节点的指针. 默认为空.
         * @param n 后一个节点的指针. 默认为空.
         */
        Node(Object &&d, Node *p = nullptr, Node *n = nullptr)
            : data{std::move(d)}, prev{p}, next{n} {}
    };

public:
    /**
     * @brief 一个静态的迭代器类. 用于创建一个可以随机访问 List 的迭代器.
     * 迭代器可以看作是一个被封装的指针.
     *
     */
    class const_iterator
    {
    public:
        /**
         * @brief 默认构造函数. 用于初始化迭代器.
         *
         */
        const_iterator() : current{nullptr}
        {
        }

        /**
         * @brief 返回当前节点的数据. 注意这里是只读的.
         *
         * @return const Object& 当前节点的数据.
         */
        const Object &operator*() const
        {
            return retrieve();
        }

        /**
         * @brief 迭代器的前置自增运算符. 用于将迭代器指向下一个节点.
         *
         * @return const_iterator& 下一个节点的迭代器.
         */
        const_iterator &operator++()
        {
            current = current->next;
            return *this;
        }

        /**
         * @brief 迭代器的后置自增运算符. 用于将迭代器指向下一个节点.
         *
         * @return const_iterator 下一个节点的迭代器.
         */
        const_iterator operator++(int)
        {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        const_iterator& operator--()
        {
            current = current->prev;
            return *this;
        }

        const_iterator operator--(int)
        {
            const_iterator old = *this;
            --(*this);
            return old;
        }

        /**
         * @brief 判断两个迭代器是否相等.
         *
         * @param rhs 右操作数.
         * @return true 相等.
         * @return false 不相等.
         */
        bool operator==(const const_iterator &rhs) const
        {
            return current == rhs.current;
        }

        /**
         * @brief 判断两个迭代器是否不相等.
         *
         * @param rhs 右操作数.
         * @return true 不相等.
         * @return false 相等.
         */
        bool operator!=(const const_iterator &rhs) const
        {
            return !(*this == rhs);
        }

    protected:
        Node *current; /**<! 当前节点的指针. */

        /**
         * @brief 返回当前节点的数据.
         *
         * @return const Object& 当前节点的数据.
         */
        Object &retrieve() const
        {
            return current->data;
        }

        /**
         * @brief 一个带参数的构造函数. 用于快速调整迭代器的位置. 不宜对外开放.
         *
         * @param p 当前节点的新位置.
         */
        const_iterator(Node *p) : current{p}
        {
        }

        friend class List<Object>; /**<! 使 List 类可以访问到迭代器的私有成员和 protected 成员. */
    };

    /**
     * @brief 动态的迭代器，可以修改节点的数据. 它继承自 const_iterator. 体现 
     * iterator IS-A const_iterator 的关系.
     * 
     */
    class iterator : public const_iterator
    {
    public:
        iterator()
        {
        }

        Object &operator*()
        {
            return const_iterator::retrieve();
        }

        const Object &operator*() const
        {
            return const_iterator::operator*();
        }

        iterator &operator++()
        {
            this->current = this->current->next;
            return *this;
        }

        iterator operator++(int)
        {
            iterator old = *this;
            ++(*this);
            return old;
        }

        iterator& operator--()
        {
            this->current = this->current->prev;
            return *this;
        }

        iterator operator--(int)
        {
            iterator old = *this;
            --(*this);
            return old;
        }

    protected:
        iterator(Node *p) : const_iterator{p}
        {
        }

        friend class List<Object>;  /**<! 同样使 List 类可以访问到迭代器的私有成员和 protected 成员. */
    };

public:
    List() { init(); }

    List(std::initializer_list<Object> il) : List()
    {
        for (const auto &x : il)
            push_back(x);
    }

    List(const List &rhs)
    {
        init();
        for (auto &x : rhs)
            push_back(x);
    }

    ~List()
    {
        clear();
        delete head;
        delete tail;
    }

    List &operator=(List copy)
    {
        std::swap(theSize, copy.theSize);
        std::swap(head, copy.head);
        std::swap(tail, copy.tail);
        return *this;
    }

    List(List &&rhs) : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}
    {
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }

    iterator begin()
    {
        return {head->next};
    }

    const_iterator begin() const
    {
        return {head->next};
    }

    iterator end()
    {
        return {tail};
    }

    const_iterator end() const
    {
        return {tail};
    }

    int size() const
    {
        return theSize;
    }

    bool empty() const
    {
        return size() == 0;
    }

    void clear()
    {
        while (!empty())
            pop_front();
    }

    Object &front()
    {
        return *begin();
    }

    const Object &front() const
    {
        return *begin();
    }

    Object &back()
    {
        return *--end();
    }

    const Object &back() const
    {
        return *--end();
    }

    void push_front(const Object &x)
    {
        insert(begin(), x);
    }

    void push_front(Object &&x)
    {
        insert(begin(), std::move(x));
    }

    void push_back(const Object &x)
    {
        insert(end(), x);
    }

    void push_back(Object &&x)
    {
        insert(end(), std::move(x));
    }

    void pop_front()
    {
        if (!empty())
        {
            erase(begin());
        }
        else
        {
            throw std::underflow_error("List is empty. Cannot pop front.");
        }
    }

    void pop_back()
    {
        if (!empty())
        {
            erase(--end());
        }
        else
        {
            throw std::underflow_error("List is empty. Cannot pop back.");
        }
    }

    iterator insert(iterator itr, const Object &x)
    {
        Node *p = itr.current;
        theSize++;
        return {p->prev = p->prev->next = new Node{x, p->prev, p}};
    }

    iterator insert(iterator itr, Object &&x)
    {
        Node *p = itr.current;
        theSize++;
        return {p->prev = p->prev->next = new Node{std::move(x), p->prev, p}};
    }

    iterator erase(iterator itr)
    {
        if (itr == end() || empty())
        {
            throw std::out_of_range("Invalid iterator or List is empty. Cannot erase.");
        }

        Node *p = itr.current;
        iterator retVal{p->next};
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        theSize--;
        return retVal;
    }

    iterator erase(iterator from, iterator to)
    {
        if (empty())
        {
            throw std::out_of_range("List is empty. Cannot erase range.");
        }
        while (from != to && from != end())
        {
            from = erase(from);
        }
        return to;
    }

private:
    int theSize;    /**<! 数据节点总数. */
    Node *head;     /**<! 头指针. */
    Node *tail;     /**<! 尾指针. */
    
    void init()
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
};

#else
// DO NOTHING.
#endif
