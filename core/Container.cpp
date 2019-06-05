#include "Container.h"

#include <cassert>
#include <cmath>

Container::Container(int capacity)
: capacity(capacity)
{
    assert(capacity >= 0 && "Container.container>capacity should be non-negative");
}

void Container::add(int count, std::string itemId)
{
    assert(count > 0 && "Container.add>count should be positive");
    assert(!isFull() && "Container.add can't add when full");

    // clamp count so as not to exceed capacity
    count = std::min(count, capacity-numTotal);

    contained[itemId] += count;
    numContained += count;
    numTotal += count;
}
void Container::allocate(int count, std::string itemId)
{
    assert(count > 0 && "Container.allocate>count should be positive");
    assert(!isFull() && "Container.allocate can't allocate when full");

    // clamp count so as not to exceed capacity
    count = std::min(count, capacity-numTotal);

    allocated[itemId] += count;
    numAllocated += count;
    numTotal += count;
}
void Container::convert(int count, std::string itemId)
{
    assert(count > 0 && "Container.convert>count should be positive");
    assert(count <= allocated[itemId] && "Container.convert>count bigger than allocated");

    allocated[itemId] -= count;
    contained[itemId] += count;

    numAllocated -= count;
    numContained += count;
}
void Container::get(int count, std::string itemId)
{
    assert(count > 0 && "Container.get>count should be positive");
    assert(count <= contained[itemId] && "Container.get>count bigger than contained");

    contained[itemId] -= count;
    numContained -= count;
    numTotal -= count;
}
bool Container::canAdd(int count, std::string itemId)
{
    assert(count > 0 && "Container.canAdd>count should be positive");
    return !isFull();
}
bool Container::canAllocate(int count, std::string itemId)
{
    assert(count > 0 && "Container.canAllocate>count should be positive");
    return !isFull();
}
bool Container::canConvert(int count, std::string itemId)
{
    assert(count > 0 && "Container.canGet>count should be positive");
    return allocated[itemId] >= count;
}
bool Container::canGet(int count, std::string itemId)
{
    assert(count > 0 && "Container.canGet>count should be positive");
    return contained[itemId] >= count;
}
bool Container::isFull()
{
    return numTotal == capacity;
}
bool Container::isEmpty()
{
    return numTotal == 0;
}


int Container::getNumContained()
{
    return numContained;
}
int Container::getNumAllocated()
{
    return numAllocated;
}
int Container::getNumTotal()
{
    return numTotal;
}
int Container::getCapacity()
{
    return capacity;
}
