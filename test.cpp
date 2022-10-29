#define CATCH_CONFIG_MAIN // This should come **before** including the 'catch.hpp'.
#include "LinkedList.h"
#include "catch.h"
using namespace std;

TEST_CASE("LinkedList adding elements") {
	LinkedList<int> list;

	SECTION("initial size should be zero") {
		REQUIRE(list.getSize() == 0);
	}

	SECTION("adding element should increase the size") {
		list.insertAtPos(1, 0);
		REQUIRE(list.getSize() == 1);
	}

	SECTION("adding element should increase the size") {
		list.insertAtPos(1, 0);
		CHECK(list.getSize() == 1);
		list.insertAtPos(2, 0);
		CHECK(list.getSize() == 2);
		list.insertAtPos(12, 1);
		CHECK(list.getElementAtPos(1) == 12);
	}
	SECTION("Adding of element out of range should throw out of range error") {
		REQUIRE_THROWS_AS(list.insertAtPos(10, 10), std::out_of_range);
	}
}

TEST_CASE("LinkedList getting elements") {
	LinkedList<int> list;
	list.insertAtPos(1, 0);
	list.insertAtPos(10, 0);
	list.insertAtPos(100, 0);
	list.insertAtPos(1000, 0);

	list.insertAtPos(15, 1);
	list.insertAtPos(16, 2);

	SECTION("non exising position should throw out of rance") {
		REQUIRE_THROWS_AS(list.getElementAtPos(100), std::out_of_range);
	}
	SECTION("adding element should increase the size") {
		CHECK(list.getElementAtPos(0) == 1000);
		CHECK(list.getElementAtPos(1) == 15);
		CHECK(list.getElementAtPos(2) == 16);
		CHECK(list.getElementAtPos(3) == 100);
		CHECK(list.getElementAtPos(4) == 10);
		CHECK(list.getElementAtPos(5) == 1);
	}
}

TEST_CASE("LinkedList removing elements") {
	LinkedList<int> list;
	list.insertAtPos(1, 0);
	list.insertAtPos(10, 0);
	list.insertAtPos(100, 0);
	list.insertAtPos(1000, 0);

	list.insertAtPos(15, 1);
	list.insertAtPos(16, 2);

	SECTION("non exising position should throw out of rance") {
		REQUIRE_THROWS_AS(list.removeAtPos(100), std::out_of_range);
	}

	SECTION("removing element should decrease the size and move the position of the next elements") {
		list.removeAtPos(4);
		CHECK(list.getElementAtPos(4) == 1);
	}
	// Add operator =, iter... for homework...

}

//Additional tests:

TEST_CASE("Operator ==") {

	LinkedList<int> list1;
	LinkedList<int> list2;

	CHECK((list1 == list2) == true);

	list1.push_back(1);
	list1.push_back(2);
	list1.push_back(3);
	list1.push_back(4);
	list1.push_back(5);

	list2.push_back(1);
	list2.push_back(2);
	list2.push_back(3);
	list2.push_back(4);
	list2.push_back(5);

	REQUIRE((list1 == list2) == true);

	list2.push_back(6);

	REQUIRE((list1 == list2) == false);
}

TEST_CASE("Operator =") {

	LinkedList<int> list1;
	LinkedList<int> list2;

	list1.push_back(1);
	list1.push_back(2);
	list1.push_back(3);
	list1.push_back(4);
	list1.push_back(5);

	REQUIRE((list1 == list2) == false);

	list2 = list1;

	REQUIRE((list1 == list2) == true);

}

TEST_CASE("sort") {

	LinkedList<int> list;
	list.push_back(5);
	list.push_back(4);
	list.push_back(3);
	list.push_back(2);
	list.push_back(1);

	REQUIRE(list.isSorted() == false);

	list.sort();

	REQUIRE(list.isSorted() == true);

}

bool tst(const int &testVal) {

	if (testVal > 10) {
		return true;
	}
	return false;
}

TEST_CASE("FilterList") {

	LinkedList<int> list;
	list.push_back(12);
	list.push_back(8);
	list.push_back(1);
	list.push_back(0);
	list.push_back(592);
	list.push_back(5);
	list.push_back(9);
	list.push_back(11);


	LinkedList<int> listCorrectAns;
	listCorrectAns.push_back(12);
	listCorrectAns.push_back(592);
	listCorrectAns.push_back(11);

	LinkedList<int> returned = list.filterList(tst);

	REQUIRE(returned == listCorrectAns);

}


int tst2(const int& testVal) {

	return testVal + 1;

}

TEST_CASE("mapList") {

	LinkedList<int> list;
	list.push_back(12);
	list.push_back(8);
	list.push_back(1);
	list.push_back(0);
	list.push_back(592);
	list.push_back(5);
	list.push_back(9);
	list.push_back(11);

	LinkedList<int> listCorrectAns;
	listCorrectAns.push_back(13);
	listCorrectAns.push_back(9);
	listCorrectAns.push_back(2);
	listCorrectAns.push_back(1);
	listCorrectAns.push_back(593);
	listCorrectAns.push_back(6);
	listCorrectAns.push_back(10);
	listCorrectAns.push_back(12);

	LinkedList<int> returned = list.mapList(tst2);

	REQUIRE(listCorrectAns == returned);
}

TEST_CASE("removeEachK") {

	LinkedList<int> test1;
	LinkedList<int> test2;
	LinkedList<int> test3;
	test1.push_back(1);
	test1.push_back(2);
	test1.push_back(3);
	test1.push_back(4);
	test1.push_back(5);
	test1.push_back(6);
	test1.push_back(7);
	test1.push_back(8);
	test1.push_back(9);

	LinkedList<int> listCorrectAns1;
	LinkedList<int> listCorrectAns2;
	LinkedList<int> listCorrectAns3;

	listCorrectAns1.push_back(1);
	listCorrectAns1.push_back(2);
	listCorrectAns1.push_back(3);
	listCorrectAns1.push_back(4);
	listCorrectAns1.push_back(5);
	listCorrectAns1.push_back(7);
	listCorrectAns1.push_back(8);
	listCorrectAns1.push_back(9);

	REQUIRE((test1 == listCorrectAns1) == false);
	test1.removeEachK(test1, 6);
	REQUIRE((test1 == listCorrectAns1) == true);

	test2.push_back(1);
	test2.push_back(2);
	test2.push_back(3);
	test2.push_back(4);
	test2.push_back(5);
	test2.push_back(6);
	test2.push_back(7);
	test2.push_back(8);
	test2.push_back(9);
	

	listCorrectAns2.push_back(1);
	listCorrectAns2.push_back(2);
	listCorrectAns2.push_back(4);
	listCorrectAns2.push_back(5);
	listCorrectAns2.push_back(7);
	listCorrectAns2.push_back(8);

	REQUIRE((test2 == listCorrectAns2) == false);
	test2.removeEachK(test2, 3);
	REQUIRE((test2 == listCorrectAns2) == true);


	test3.push_back(1);
	test3.push_back(2);
	test3.push_back(3);
	test3.push_back(4);
	test3.push_back(5);
	test3.push_back(6);
	test3.push_back(7);
	test3.push_back(8);
	test3.push_back(9);

	listCorrectAns3.push_back(1);
	listCorrectAns3.push_back(3);
	listCorrectAns3.push_back(5);
	listCorrectAns3.push_back(7);
	listCorrectAns3.push_back(9);

	REQUIRE((test3 == listCorrectAns3) == false);
	test3.removeEachK(test3, 2);
	REQUIRE((test3 == listCorrectAns3) == true);

}
