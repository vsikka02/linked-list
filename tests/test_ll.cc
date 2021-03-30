// Copyright (c) 2020 [Your Name]. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cs126linkedlist/ll.h>


using cs126linkedlist::LinkedList;

// Read more on SECTIONs here:
// `https://github.com/catchorg/Catch2/tree/master/docs`
// in the "Test Cases and Sections" file.
TEST_CASE("Test Constructors") {
  SECTION("Test Vector Parameterized Constructor") {
    const std::vector<int>& test_vector{1, 2, 3, 4, 5, 6};
    LinkedList<int> list(test_vector);
    REQUIRE(list.size() == 6);
  }
  SECTION("Test Copy Constructor") {
    const std::vector<int>& test_vector{1, 2, 3, 4, 5, 6};
    LinkedList<int> list(test_vector);
    LinkedList<int> list_2 (list);
    REQUIRE(list_2 == list);
    REQUIRE(list_2.size() == list.size());
  }
  SECTION("Test Move Constructor") {
    const std::vector<int>& test_vector{1, 2, 3, 4, 5, 6};
    LinkedList<int> list(test_vector);
    LinkedList<int> list_2(std::move(list));
    LinkedList<int> test_list(test_vector);
    REQUIRE(list_2.size() == 6);
    REQUIRE(list_2 == test_list);
  }
  SECTION("Test Empty Constructor") {
    LinkedList<int> list;
    REQUIRE(list.size() == 0);
  }
}

TEST_CASE("Test Assignment Operators") {
  SECTION("Test Copy Assignment Operator with pre-defined list") {
    const std::vector<int>& test_vector{1, 2, 3, 4, 5, 6};
    const std::vector<int>& test_vector_2{5, 4, 3, 2, 1, 0};
    LinkedList<int> list(test_vector);
    LinkedList<int> list_2(test_vector_2);
    list = list_2;
    REQUIRE(list == list_2);
  }
  SECTION("Test Move Assignment Operator with pre-defined list") {
    const std::vector<int>& test_vector{1, 2, 3, 4, 5, 6};
    const std::vector<int>& test_vector_2{5, 4, 3, 2, 1, 0};
    LinkedList<int> list(test_vector);
    LinkedList<int> list_2(test_vector_2);
    LinkedList<int> test_list(test_vector_2);
    list = std::move(list_2);
    REQUIRE(list == test_list);
    REQUIRE(list_2 == LinkedList<int>());
  }
  SECTION("Test Copy Assignment Operator with no defined list") {
    LinkedList<int> empty_list;
    const std::vector<int>& test_vector{1, 2, 3, 4, 5, 6};
    LinkedList<int> list(test_vector);

    empty_list = list;
    REQUIRE(empty_list == list);
    REQUIRE(empty_list.size() == 6);
  }
  SECTION("Test Move Assignment Operator with no defined list") {
    LinkedList<int> empty_list;
    const std::vector<int>& test_vector{1, 2, 3, 4, 5, 6};
    LinkedList<int> list(test_vector);

    empty_list = std::move(list);
    REQUIRE(empty_list != list);
    REQUIRE(empty_list.size() == 6);
  }
}

TEST_CASE("Push Back", "[constructor][push_back][size][empty]") {
  LinkedList<int> list;

  REQUIRE(list.size() == 0);
  REQUIRE(list.empty());

  SECTION("Push back one element") {
    list.push_back(1);
    REQUIRE(list.size() == 1);
    REQUIRE(list.back() == 1);
  }

  SECTION("Push back two elements") {
    list.push_back(-1);
    list.push_back(10000);
    REQUIRE(list.size() == 2);
    REQUIRE(list.back() == 10000);
  }
}

TEST_CASE("Push Front", "[constructor][push_back][size][empty]") {
  LinkedList<int> list;

  REQUIRE(list.size() == 0);
  REQUIRE(list.empty());

  SECTION("Push Front one element") {
    list.push_front(1);
    REQUIRE(list.size() == 1);
    REQUIRE(list.front() == 1);
  }

  SECTION("Push Front two elements") {
    list.push_front(-1);
    list.push_front(10000);
    REQUIRE(list.size() == 2);
    REQUIRE(list.front() == 10000);
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
    REQUIRE(list == LinkedList<int>());
  }
  SECTION("Clear Empty List") {
    list.clear();
    REQUIRE(list.size() == 0);
    REQUIRE(list == LinkedList<int>());
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
    REQUIRE(list == list2);
  }
  SECTION("Unequal List") {
    list.push_back(2);
    list.push_back(3);
    LinkedList<int> list2 = LinkedList(list);
    list.push_back(1);
    REQUIRE_FALSE(list == list2);
  }
}

TEST_CASE("Test Unequal Operator") {
  LinkedList<int> list;
  SECTION("Equal Lists") {
    list.push_back(1);
    list.push_back(2);
    LinkedList<int> list2;
    list2.push_back(1);
    list2.push_back(2);
    REQUIRE_FALSE(list != list2);
  }
  SECTION("Unequal List") {
    list.push_back(2);
    list.push_back(3);
    LinkedList<int> list2 = LinkedList(list);
    list2.push_back(1);
    REQUIRE(list != list2);
  }
}

TEST_CASE("Remove Nth Element") {
  std::vector<int> test_vector{0, 1, 2, 3, 4, 5};
  LinkedList<int> list = LinkedList<int>(test_vector);
  SECTION("Remove Element in Middle") {
    list.RemoveNth(2);
    REQUIRE(list.size() == 5);
  }
  SECTION("Remove First Element") {
    list.RemoveNth(0);
    REQUIRE(list.size() == 5);
  }
  SECTION("Remove Last Element") {
    list.RemoveNth(5);
    REQUIRE(list.size() == 5);
  }
  SECTION("Remove Invalid Element") {
    REQUIRE_THROWS_AS(list.RemoveNth(6), std::out_of_range);
  }
}

TEST_CASE("Test Destructor") {
  std::vector<int> test_vector{0, 1, 2, 3, 4, 5};
  LinkedList<int> list = LinkedList<int>(test_vector);
  list.~LinkedList();
  REQUIRE(list == LinkedList<int>());
  REQUIRE(list.empty());
}

TEST_CASE("Remove All Odd Values") {
  SECTION("Remove Odd Nodes from List with Odd Indexes") {
    std::vector<int> test_vector{0, 1, 2, 3, 4, 5};
    LinkedList<int> list = LinkedList<int>(test_vector);
    std::vector<int> even_vector{0, 2, 4};
    list.RemoveOdd();
    REQUIRE(list.size() == 3);
    REQUIRE(list == LinkedList<int>(even_vector));
  }
  SECTION("Remove Odd Nodes from List with Even Number of Indexes") {
    std::vector<int> test_vector{0, 1, 2, 3, 4, 5, 6};
    LinkedList<int> list = LinkedList<int>(test_vector);
    std::vector<int> even_vector{0, 2, 4, 6};
    list.RemoveOdd();
    REQUIRE(list.size() == 4);
    REQUIRE(list == LinkedList<int>(even_vector));
  }
  SECTION("No odd Nodes") {
    LinkedList<int> list;
    list.push_back(1);
    list.RemoveOdd();
    REQUIRE(list.size() == 1);
    LinkedList<int> test_list;
    test_list.push_back(1);
    REQUIRE(list == test_list);
  }
  SECTION("Empty List") {
    LinkedList<int> list;
    list.RemoveOdd();
    REQUIRE(list.size() == 0);
    REQUIRE(list == LinkedList<int>());
  }
}

TEST_CASE("Test Print") {
  std::vector<int> test_vector{0, 1, 2, 3, 4, 5};
  LinkedList<int> list = LinkedList<int>(test_vector);
  std::stringstream ss;
  ss << list;
  REQUIRE(ss.str() == "Data: 0\nData: 1\nData: 2\nData: 3\nData: 4\nData: 5\n");
}
