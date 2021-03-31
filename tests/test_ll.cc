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

    list_2.push_back(7);

    REQUIRE(list_2 != list);
    REQUIRE(list_2.size() == 7);
    REQUIRE(list.size() == 6);
  }
  SECTION("Test Move Constructor") {
    const std::vector<int>& test_vector{1, 2, 3, 4, 5, 6};
    LinkedList<int> list(test_vector);
    LinkedList<int> list_2(std::move(list));
    LinkedList<int> test_list(test_vector);

    REQUIRE(list_2.size() == 6);
    REQUIRE(list_2 == test_list);
    REQUIRE(list.empty());
  }
  SECTION("Test Empty Constructor") {
    LinkedList<int> list;

    REQUIRE(list.size() == 0);
    REQUIRE(list.empty());
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

    list.push_back(7);

    REQUIRE(list != list_2);
    REQUIRE(list.size() == 7);
    REQUIRE(list_2.size() == 6);
  }
  SECTION("Test Move Assignment Operator with pre-defined list") {
    const std::vector<int>& test_vector{1, 2, 3, 4, 5, 6};
    const std::vector<int>& test_vector_2{5, 4, 3, 2, 1, 0};
    LinkedList<int> list(test_vector);
    LinkedList<int> list_2(test_vector_2);
    LinkedList<int> test_list(test_vector_2);

    list = std::move(list_2);

    REQUIRE(list == test_list);
    REQUIRE(list_2.empty());
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

  SECTION("Pop Front Zero Elements") {
    list.pop_back();
    REQUIRE(list.size() == 0);
    REQUIRE(list.empty());
  }

  SECTION("Pop Front one element") {
    list.push_back(1);
    list.pop_front();

    REQUIRE(list.size() == 0);
    REQUIRE(list.empty());
  }
  SECTION("Pop Front with More than One Element") {
    list.push_back(1);
    list.push_back(2);
    list.pop_front();

    REQUIRE(list.front() == 2);
    REQUIRE(list.size() == 1);
  }
}

TEST_CASE("Pop Back") {
  LinkedList<int> list;

  SECTION("Pop Back with No Elements") {
    list.pop_back();

    REQUIRE(list.empty());
    REQUIRE(list.size() == 0);
  }

  SECTION("Pop Back One Element") {
    list.push_back(1);
    list.pop_back();

    REQUIRE(list.size() == 0);
    REQUIRE(list.empty());
  }
  SECTION("Pop Back with More than One Element") {
    list.push_back(1);
    list.push_back(2);
    list.pop_back();

    REQUIRE(list.back() == 1);
    REQUIRE(list.size() == 1);
  }
}

TEST_CASE("Test Clear List") {
  LinkedList<int> list;
  SECTION("Clear List with 3 Elements") {
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
  LinkedList<int> list (test_vector);

  SECTION("Remove Element in Middle") {
    list.RemoveNth(2);

    std::vector<int> vector{0,1,3,4,5};
    LinkedList<int> list_2 (vector);

    REQUIRE(list == list_2);
    REQUIRE(list.size() == 5);
  }
  SECTION("Remove First Element") {
    list.RemoveNth(0);

    std::vector<int> vector{1,2,3,4,5};
    LinkedList<int> list_2 (vector);

    REQUIRE(list == list_2);
    REQUIRE(list.size() == 5);
  }
  SECTION("Remove Last Element") {
    list.RemoveNth(5);

    std::vector<int> vector{0,1,2,3,4};
    LinkedList<int> list_2 (vector);

    REQUIRE(list == list_2);
    REQUIRE(list.size() == 5);
  }
  SECTION("Remove Invalid Element") {
    REQUIRE_THROWS_AS(list.RemoveNth(6), std::out_of_range);
  }
}

TEST_CASE("Test Destructor") {
  std::vector<int> test_vector{0, 1, 2, 3, 4, 5};
  LinkedList<int> list (test_vector);
  list.~LinkedList();

  REQUIRE(list == LinkedList<int>());
  REQUIRE(list.empty());
}

TEST_CASE("Remove All Odd Values") {
  SECTION("Remove Odd Nodes from List with Odd Indexes") {
    std::vector<int> test_vector{0, 1, 2, 3, 4, 5};
    LinkedList<int> list(test_vector);

    list.RemoveOdd();

    REQUIRE(list.size() == 3);

    std::vector<int> even_vector{0, 2, 4};
    REQUIRE(list == LinkedList<int>(even_vector));
  }
  SECTION("Remove Odd Nodes from List with Even Number of Indexes") {
    std::vector<int> test_vector{0, 1, 2, 3, 4, 5, 6};
    LinkedList<int> list(test_vector);

    list.RemoveOdd();
    REQUIRE(list.size() == 4);

    std::vector<int> even_vector{0, 2, 4, 6};

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
  SECTION("Full Vector") {
    std::vector<int> test_vector{0, 1, 2, 3, 4, 5};
    LinkedList<int> list(test_vector);
    std::stringstream ss;
    ss << list;

    REQUIRE(ss.str() ==
            "0, 1, 2, 3, 4, 5");
  }
  SECTION("Empty Vector") {
    LinkedList<int> list;
    std::stringstream ss;
    ss<<list;

    REQUIRE(ss.str() == "");
  }
}

TEST_CASE("Test other Element Types") {
  SECTION("Floats") {
    std::vector<float> test_vector {0.2, 3.14, 5.67};
    LinkedList<float> list (test_vector);

    REQUIRE(list.front() == Approx(0.2));
    REQUIRE(list.back() == Approx(5.67));
    REQUIRE(list.size() == 3);
  }
  SECTION("Strings") {
    std::vector<std::string> test_vector {"hello", "world", "!" };
    LinkedList<std::string> list (test_vector);

    REQUIRE(list.front() == "hello");
    REQUIRE(list.back() == "!");
    REQUIRE(list.size() == 3);
  }
}

TEST_CASE("Iterator Test") {
  std::vector<int> test_vector{12343, 1565, 768, 869};
  LinkedList<int> list (test_vector);
  SECTION("Test Iterator Begin") {
    LinkedList<int>::iterator it = list.begin();

    REQUIRE(*it == 12343);
  }
  SECTION("Test Iterator Full") {
    std::vector<int> vector;

    for (LinkedList<int>::iterator it = list.begin(); it != list.end(); ++it) {
      vector.push_back(*it);
    }

    REQUIRE(vector == test_vector);
  }
  SECTION("Test ++ Operator") {
    LinkedList<int>::iterator it = list.begin();
    REQUIRE(*it == 12343);

    ++it;

    REQUIRE(*it == 1565);
  }
  SECTION("Test != Operator") {
    LinkedList<int>::iterator it = list.begin();

    std::vector<int> test_vector_2{1256, 176, 243, 968};
    LinkedList<int> list_2 (test_vector_2);

    LinkedList<int>::iterator it_2 = list_2.begin();

    REQUIRE(it != it_2);
  }
}

TEST_CASE("Const Iterator Tests") {
  const std::vector<int> test_vector{12343, 1565, 768, 869};
  const LinkedList<int> list (test_vector);
  SECTION("Test Const Iterator Begin") {
    LinkedList<int>::const_iterator it = list.begin();

    REQUIRE(*it == 12343);
  }
  SECTION("Test Iterator Full") {
    std::vector<int> vector;

    for (LinkedList<int>::const_iterator it = list.begin(); it != list.end(); ++it) {
      vector.push_back(*it);
    }

    REQUIRE(vector == test_vector);
  }
  SECTION("Test ++ Operator") {
    LinkedList<int>::const_iterator it = list.begin();
    REQUIRE(*it == 12343);

    ++it;

    REQUIRE(*it == 1565);
  }
  SECTION("Test != Operator") {
    LinkedList<int>::const_iterator it = list.begin();

    const std::vector<int> test_vector_2{1256, 176, 243, 968};
    const LinkedList<int> list_2 (test_vector_2);

    LinkedList<int>::const_iterator it_2 = list_2.begin();

    REQUIRE(it != it_2);
  }
}
