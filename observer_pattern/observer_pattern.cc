#include <iostream>
#include <list>
#include <string>
#include <memory>

using std::cout;
using std::endl;
using std::list;
using std::string;
using std::unique_ptr;

class Observer {
public:
    virtual void update(const string& message) = 0;
    virtual ~Observer(){};
};

class Subject {
public:
    virtual void RegisterObserver(Observer*) = 0;
    virtual void RemoveObserver(Observer*) = 0;
    virtual void NotifyObserver(const string& message) = 0;
    virtual ~Subject(){};
};

class ConcreteSubject : public Subject {
public:
    void RegisterObserver(Observer* ob) override {
        if (ob) {
            observers_.push_back(ob);
        }
    }

    void RemoveObserver(Observer* ob) override {
        if (ob) {
            observers_.remove(ob);
        }
    }

    void NotifyObserver(const string& message) override {
        for (auto& e : observers_) {
            e->update(message);
        }
    }

private:
    list<Observer*> observers_;
};

class ConcreteObserver : public Observer {
public:
    ConcreteObserver(int id)
        : id_(id)
    {}
    void update(const string& message) override {
        cout << id_ << ":" << message << endl;
    }

private:
    int id_;
};

class ConcreteObserver1 : public Observer {
public:
    ConcreteObserver1(string name)
        : name_(name)
    {}
    void update(const string& message) override {
        cout << name_ << ":" << message << endl;
    }

private:
    string name_;
};

int main(int argc, char* argv[]) {
    unique_ptr<Observer> ob1(new ConcreteObserver(1));
    unique_ptr<Observer> ob2(new ConcreteObserver(2));
    unique_ptr<Observer> ob3(new ConcreteObserver(3));
    unique_ptr<Observer> ob4(new ConcreteObserver1("libai"));

    unique_ptr<Subject> sub(new ConcreteSubject());

    sub->RegisterObserver(ob1.get());
    sub->RegisterObserver(ob2.get());
    sub->RegisterObserver(ob3.get());
    sub->RegisterObserver(ob4.get());

    sub->NotifyObserver("\ttime for lunch!");

    sub->RemoveObserver(ob2.get());

    sub->NotifyObserver("\ttime for bed!");

    return 0;
}

