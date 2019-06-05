#include "../catch.hpp"
#include "../../core/Container.h"

TEST_CASE("Container", "[container, unit]")
{
    SECTION("constructor")
    {
        SECTION("w/ capacity=0")
        {
            Container container;
            REQUIRE(container.getNumContained() == 0);
            REQUIRE(container.getNumAllocated() == 0);
            REQUIRE(container.getNumTotal() == 0);
            REQUIRE(container.getCapacity() == 0);
        }
        SECTION("w/ capacity=100")
        {
            Container container(100);
            REQUIRE(container.getNumContained() == 0);
            REQUIRE(container.getNumAllocated() == 0);
            REQUIRE(container.getNumTotal() == 0);
            REQUIRE(container.getCapacity() == 100);
        }
    }
}

TEST_CASE("isFull/isEmpty")
{
    SECTION("a container with zero capacity")
    {
        Container container(0);
        REQUIRE(container.getCapacity() == 0);
        REQUIRE(container.isFull() == true);
        REQUIRE(container.isEmpty() == true);
    }
    SECTION("an empty container")
    {
        Container container(5);

        REQUIRE(container.getNumTotal() == 0);
        REQUIRE(container.isFull() == false);
        REQUIRE(container.isEmpty() == true);
    }
    SECTION("a container with some items")
    {
        Container container(5);
        container.add(3, "items");

        REQUIRE(container.getNumTotal() > 0);
        REQUIRE(container.isFull() == false);
        REQUIRE(container.isEmpty() == false);
    }
    SECTION("a full container")
    {
        Container container(5);
        container.add(5, "items");

        REQUIRE(container.getNumTotal() == 5);
        REQUIRE(container.isFull() == true);
        REQUIRE(container.isEmpty() == false);
    }
}

SCENARIO("canAdd")
{
    GIVEN("given a container with zero capacity")
    {
        Container container(0);
        THEN("you cannot add anything")
        {
            REQUIRE(container.canAdd(1, "item") == false);
        }
    }
    GIVEN("given a non-full container with capacity 5")
    {
        Container container(5);
        container.add(3, "item");
        REQUIRE(container.isFull() == false);
        THEN("you can add 1000 items");
        {
            REQUIRE(container.canAdd(4, "item") == true);
        }
    }
    GIVEN("given a full container")
    {
        Container container(5);
        container.add(5, "item");
        REQUIRE(container.isFull() == true);
        THEN("you cannot add 1 item")
        {
            REQUIRE(container.canAdd(1, "item") == false);
        }
    }
}
SCENARIO("canAllocate")
{
    GIVEN("given a container with zero capacity")
    {
        Container container(0);
        THEN("you cannot allocate anything")
        {
            REQUIRE(container.canAllocate(1, "item") == false);
        }
    }
    GIVEN("given a non-full container with capacity 5")
    {
        Container container(5);
        container.add(3, "item");
        REQUIRE(container.isFull() == false);
        THEN("you can allocate 1000 items");
        {
            REQUIRE(container.canAllocate(4, "item") == true);
        }
    }
    GIVEN("given a full container")
    {
        Container container(5);
        container.add(5, "item");
        REQUIRE(container.isFull() == true);
        THEN("you cannot allocate 1 item")
        {
            REQUIRE(container.canAllocate(1, "item") == false);
        }
    }
}
SCENARIO("canConvert")
{
    GIVEN("a container with zero capacity")
    {
        Container container(0);
        REQUIRE(container.getCapacity() == 0);

        THEN("you cannot convert 1 item")
        {
            REQUIRE(container.canConvert(1, "item") == false);
        }
    }
    GIVEN("a container without any allocated items")
    {
        Container container(5);
        REQUIRE(container.getNumAllocated() == 0);

        THEN("you cannot convert 1 item")
        {
            REQUIRE(container.canConvert(1, "item") == false);
        }
    }

    GIVEN("a container containing 5 items and nothing allocated")
    {
        Container container(5);
        container.add(5, "item");
        REQUIRE(container.getNumContained() == 5);

        THEN("you cannot convert 1 item")
        {
            REQUIRE(container.canConvert(1, "item") == false);
        }
    }

    GIVEN("a container allocated with 1 item")
    {
        Container container(5);
        container.allocate(1, "item");

        REQUIRE(container.getNumAllocated() == 1);

        THEN("you can convert 1 item")
        {
            REQUIRE(container.canConvert(1, "item") == true);
        }
        THEN("you cannot convert 2 items")
        {
            REQUIRE(container.canConvert(2, "item") == false);
        }
    }
}
SCENARIO("canGet")
{
    GIVEN("given a container with zero capacity")
    {
        Container container(0);

        REQUIRE(container.getCapacity() == 0);

        THEN("you cannot get anything")
        {
            REQUIRE(container.canGet(1, "item") == false);
        }
    }
    GIVEN("given an empty container")
    {
        Container container(5);

        REQUIRE(container.isEmpty() == true);

        THEN("you cannot get 1 item")
        {
            REQUIRE(container.canGet(1, "item") == false);
        }
    }
    GIVEN("given a container containing 3 items")
    {
        Container container(5);
        container.add(3, "item");

        REQUIRE(container.getNumContained() == 3);

        THEN("you can get 3 items")
        {
            REQUIRE(container.canGet(3, "item") == true);
        }
        THEN("you cannot get 4 items")
        {
            REQUIRE(container.canGet(4, "item") == false);
        }
    }
    GIVEN("given a container allocated with 1 item")
    {
        Container container(5);
        container.allocate(1, "item");

        REQUIRE(container.getNumAllocated() == 1);

        THEN("you cannot get 1 item")
        {
            REQUIRE(container.canGet(1, "item") == false);
        }
        THEN("you cannot get 2 items")
        {
            REQUIRE(container.canGet(2, "item") == false);
        }
    }
}

SCENARIO("Adding items")
{
    GIVEN("an empty container with capacity 5")
    {
        Container container(5);
        int pastNumAllocated = container.getNumAllocated();

        REQUIRE(container.isEmpty() == true);
        REQUIRE(container.getCapacity() == 5);

        WHEN("you add 1 item")
        {
            THEN("the number of items contained becomes 1")
            AND_THEN("the number of items allocated does not change")
            AND_THEN("the number of total items becomes 1")
            {
                container.add(1, "item");

                REQUIRE(container.getNumContained() == 1);
                REQUIRE(container.getNumAllocated() == pastNumAllocated);
                REQUIRE(container.getNumTotal() == 1);
            }
        }
        WHEN("you add 1000 items")
        {
            THEN("the number of items contained becomes 5")
            AND_THEN("the number of items allocated does not change")
            AND_THEN("the number of total items becomes 5")
            {
                container.add(1000, "item");

                REQUIRE(container.getNumContained() == 5);
                REQUIRE(container.getNumAllocated() == pastNumAllocated);
                REQUIRE(container.getNumTotal() == 5);
            }
        }
    }
}
SCENARIO("Allocating items")
{
    GIVEN("an empty container with capacity 5")
    {
        Container container(5);
        int pastNumContained = container.getNumContained();

        REQUIRE(container.isEmpty() == true);
        REQUIRE(container.getCapacity() == 5);

        WHEN("you allocate 1 item")
        {
            THEN("the number of items contained does not change")
            AND_THEN("the number of items allocated becomes 1")
            AND_THEN("the number of total items becomes 1")
            {
                container.allocate(1, "item");

                REQUIRE(container.getNumContained() == pastNumContained);
                REQUIRE(container.getNumAllocated() == 1);
                REQUIRE(container.getNumTotal() == 1);
            }
        }
        WHEN("you allocate 1000 items")
        {
            THEN("the number of items contained does not change")
            AND_THEN("the number of items allocated becomes 5")
            AND_THEN("the number of total items becomes 5")
            {
                container.allocate(1000, "item");

                REQUIRE(container.getNumContained() == pastNumContained);
                REQUIRE(container.getNumAllocated() == 5);
                REQUIRE(container.getNumTotal() == 5);
            }
        }
    }
}
SCENARIO("Converting items")
{
    GIVEN("a container containing 1 item and is allocated with 3 items")
    {
        Container container(5);
        container.add(1, "item");
        container.allocate(3, "item");

        int pastNumTotal = container.getNumTotal();

        REQUIRE(container.getNumContained() == 1);
        REQUIRE(container.getNumAllocated() == 3);

        WHEN("you convert 1 item")
        {
            THEN("the number of items contained becomes 2")
            AND_THEN("the number of items allocated becomes 2")
            AND_THEN("the number of total does not change")
            {
                container.convert(1, "item");

                REQUIRE(container.getNumContained() == 2);
                REQUIRE(container.getNumAllocated() == 2);
                REQUIRE(container.getNumTotal() == pastNumTotal);
            }
        }
    }
}
SCENARIO("Getting items")
{
    GIVEN("a container containing 3 items")
    {
        Container container(5);
        container.add(3, "item");

        int pastNumAllocated = container.getNumAllocated();

        REQUIRE(container.getNumContained() == 3);

        WHEN("you get 1 item")
        {
            THEN("the number of items contained becomes 2")
            AND_THEN("the number of items allocated does not change")
            AND_THEN("the number of total items becomes 2")
            {
                container.get(1, "item");

                REQUIRE(container.getNumContained() == 2);
                REQUIRE(container.getNumAllocated() == pastNumAllocated);
                REQUIRE(container.getNumTotal() == 2);
            }
        }
    }
}


