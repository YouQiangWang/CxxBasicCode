#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <functional>
#include <future>

using namespace std;
struct Person
{
public:
    Person &setPersonInfo(string &name, int age)
    {
        name_ = name;
        age_ = age;
        return *this;
    }
    static Person getPersonInfo()
    {

        return Person{};
    }
    friend ostream &operator<<(ostream &os, Person per);

public:
    string name_ = string("");
    int age_ = 0;
};

ostream &operator<<(ostream &os, Person per)
{
    os << "Person name:" << per.name_ << ", person age:" << per.age_;
    return os;
}

int main()
{
    Person oriPerson;
    string name1("GaoShuai");
    std::packaged_task<Person()> task1(std::bind(&Person::setPersonInfo, &oriPerson, std::ref(name1), 22));
    std::future<Person> fut1 = task1.get_future();
    std::thread(std::move(task1)).detach();
    std::cout << fut1.get() << endl;

    std::packaged_task<Person(string &, int)> task2(std::bind(&Person::setPersonInfo, &oriPerson, std::placeholders::_1, std::placeholders::_2));
    std::future<Person> fut2 = task2.get_future();
    string name2("liuming");
    std::thread(std::move(task2), std::ref(name2), 36).detach();
    std::cout << fut2.get() << endl;

    return 0;
}
