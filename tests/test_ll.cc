// Copyright (c) 2020 [Your Name]. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cs126linkedlist/ll.h>


using cs126linkedlist::LinkedList;

// Read more on SECTIONs here:
// `https://github.com/catchorg/Catch2/tree/master/docs`
// in the "Test Cases and Sections" file.
TEST_CASE("Push Back", "[constructor][push_back][size][empty]") {
  LinkedList<int> list;

  REQUIRE(list.size() == 0);
  REQUIRE(list.empty());

  SECTION("Push back one element") {
    list.push_back(1);
    REQUIRE(list.size() == 1);
  }

  SECTION("Push back two elements") {
    list.push_back(-1);
    list.push_back(10000);
    REQUIRE(list.size() == 2);
  }
}

TEST_CASE("Test Vector Constructor") {
  const std::vector<int>& test_vector {1,2,3,4,5,6};
  LinkedList<int> list (test_vector);
  REQUIRE(list.size() == 6);
}

TEST_CASE("Push Front", "[constructor][push_back][size][empty]") {
  LinkedList<int> list;

  REQUIRE(list.size() == 0);
  REQUIRE(list.empty());

  SECTION("Push Front one element") {
    list.push_front(1);
    REQUIRE(list.size() == 1);
  }

  SECTION("Push Front two elements") {
    list.push_front(-1);
    list.push_front(10000);
    REQUIRE(list.size() == 2);
  }
}

TEST_CASE("Pop Front") {
  LinkedList<int> list;
  SECTION("Pop Front one element") {
    list.push_back(1);
    list.pop_front();
    REQUIRE(list.size() == 0);
  }
}

TEST_CASE("Pop Back") {
  LinkedList<int> list;
  SECTION("Pop Back One Element") {
    list.push_back(1);
    list.pop_back();
    REQUIRE(list.size() == 0);
  }
}

TEST_CASE("Test Clear List") {
  LinkedList<int> list;
  SECTION("Clear List with 3 Objects") {
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.clear();
    REQUIRE(list.size() == 0);
  }
}

TEST_CASE("Check Equal Operator") {
  LinkedList<int> list;
  SECTION("Equal Lists") {
    list.push_back(1);
    list.push_back(2);
    LinkedList<int> list2;
    list2.push_back(1);
    list2.push_back(2);
    REQUIRE((list == list2) == true);
  }
  SECTION("Unequal List") {
    list.push_back(2);
    list.push_back(3);
    LinkedList<int> list2 = LinkedList(list);
    list.push_back(1);
    REQUIRE_FALSE(list == list2);
  }
}

TEST_CASE("Remove Nth Element") {
  std::vector<int> test_vector {0,1,2,3,4,5};
  LinkedList<int> list = LinkedList<int>(test_vector);
}