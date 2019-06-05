#ifndef CONTAINER_H_INCLUDED
#define CONTAINER_H_INCLUDED

#include <string>
#include <unordered_map>

struct Container
{
    Container(int capacity=0);

    void add(int count, std::string itemId);
    void allocate(int count, std::string itemId);
    void convert(int count, std::string itemId);
    void get(int count, std::string itemId);
    bool canAdd(int count, std::string itemId);
    bool canAllocate(int count, std::string itemId);
    bool canConvert(int count, std::string itemId);
    bool canGet(int count, std::string itemId);
    bool isFull();
    bool isEmpty();

    int getNumContained();
    int getNumAllocated();
    int getNumTotal();
    int getCapacity();

private:

    std::unordered_map<std::string, int> contained;
    std::unordered_map<std::string, int> allocated;

    int numContained = 0;
    int numAllocated = 0;
    int numTotal = 0;
    int capacity = 0;
};

#endif // CONTAINER_H_INCLUDED
