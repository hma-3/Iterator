#include <iostream>

using namespace std;

class Iterator {
public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() const = 0;
    virtual int currentItem() const = 0;
};

class ConcreteIterator : public Iterator {
    int* array;
    int size;
    int index;
public:
    ConcreteIterator(int* array, int size) : array(array), size(size), index(0) {}

    void first() override {
        index = 0;
    }

    void next() override {
        if (!isDone()) {
            ++index;
        }
    }

    bool isDone() const override {
        return index >= size;
    }

    int currentItem() const override {
        if (!isDone()) {
            return array[index];
        }
        return -1;
    }
};

class Aggregate {
public:
    virtual Iterator* createIterator() = 0;
    virtual int getItem(int index) const = 0;
    virtual int getSize() const = 0;
};

class ConcreteAggregate : public Aggregate {
    int* array;
    int size;
public:
    ConcreteAggregate(int* array, int size) : array(array), size(size) {}

    Iterator* createIterator() override {
        return new ConcreteIterator(array, size);
    }

    int getItem(int index) const override {
        if (index >= 0 && index < size) {
            return array[index];
        }
        return -1;
    }

    int getSize() const override {
        return size;
    }
};

int main() {
    int array[] = { 1, 2, 3, 4, 5 };
    int size = sizeof(array) / sizeof(array[0]);

    ConcreteAggregate aggregate(array, size);
    Iterator* iterator = aggregate.createIterator();

    for (iterator->first(); !iterator->isDone(); iterator->next()) {
        cout << "Current item: " << iterator->currentItem() << endl;
    }

    delete iterator;

    return 0;
}