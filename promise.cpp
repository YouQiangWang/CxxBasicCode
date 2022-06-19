
#include <iostream>
#include <thread>
#include <string>
#include <chrono>
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
    friend ostream &operator<<(ostream &os, Person per);

public:
    string name_;
    int age_;
};

ostream &operator<<(ostream &os, Person per)
{
    os << "Person name:" << per.name_ << ", person age:" << per.age_;
    return os;
}

void promSetPerson(std::future<Person> &fut)
{
    std::chrono::steady_clock time;
    auto t1 = time.now();

    Person per = fut.get();

    auto t2 = time.now();
    auto useTime = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    cout << "get future use :" << useTime.count() << "ms" << endl;
    std::cout << per << endl;
}

int main()
{
    Person oriPerson;
    std::promise<Person> prom;
    std::future<Person> fut2 = prom.get_future();

    std::thread t1(promSetPerson, std::ref((fut2)));
    std::this_thread::sleep_for(std::chrono::milliseconds(820));
    Person lastPerson;
    string lastName("daNiu");
    lastPerson.setPersonInfo(lastName, 29);

    prom.set_value(lastPerson);

    t1.join();
    return 0;
}
