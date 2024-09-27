#include <iostream>
#include <cstring>

class Chicken
{
    private:
        int age = 24;
        char *name = nullptr;
    public:
        Chicken(){};
        Chicken(int _age) : age(_age) {};

        Chicken(int _age, const char *_name) : age(_age) 
        {
            int len = strlen(_name) + 1;
            name = new char[len];
            for (int i = 0; i < len; i++)
                name[i] = _name[i];
        };

        Chicken(const Chicken &c)
        {
            age = c.age;
            int len = strlen(c.name) + 1;

            name = new char[len];
            for (int i = 0; i < len; i++)
                name[i] = c.name[i];
        }

        Chicken& operator=(const Chicken &c)
        {
            age = c.age;
            delete[] name;

            int len = strlen(c.name) + 1;
            name = new char[len];
            for (int i = 0; i < len; i++)
                name[i] = c.name[i];
            return *this;
        }

        ~Chicken()
        {
            if (name != nullptr)
                delete[] name;
        }
        void setAge(int _age)
        {
            age = _age;
        }
        void setName(const char *_name)
        {
            auto old_name = name;
                
            int len = strlen(_name) + 1;
            name = new char[len];
            for (int i = 0; i < len; i++)
                name[i] = _name[i];

            delete[] old_name;
        }

        const char *getName() const
        {
            return name;
        }

        const int &getAge() const
        {
            return age;
        }
};

// int main()
// {
//     Chicken c(24, "Kunkun");
//     std::cout << "Hi, everyone! My name is " << c.getName() << ", I am " << c.getAge() << " years old." << std::endl;
//     return 0;
// }