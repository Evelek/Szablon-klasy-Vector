#include "gtest\gtest.h"
#include "vector.h"
using namespace vec;

TEST(AddElement, OneElement) {
	Vector<int> vec;
	vec.add_new_element(34);
	size_t vectorSize = vec.size();
	EXPECT_EQ(1, vectorSize) << "Vector size after adding one element should be: 1";
}

TEST(AddElement, FewElements_1) {
	Vector<int> vec;
	vec.add_new_element(34);
	vec.add_new_element(0);
	vec.add_new_element(-3);
	vec.add_new_element(-1028);
	vec.add_new_element(39398390);
	size_t vectorSize = vec.size();
	EXPECT_EQ(5, vectorSize) << "Vector size after adding five elements should be: 5";
}

TEST(AddElement, FewElements_2) {
	Vector<int> vec;
	// Add 9999 elements
	for (size_t i = 0; i < 9999; ++i)
		vec.add_new_element(i);
	size_t vectorSize = vec.size();
	EXPECT_EQ(9999, vectorSize) << "Vector size should be: 9999";
}

TEST(AddRemoveElement, OneElement) {
	Vector<int> vec;
	vec.add_new_element(10);
	vec.remove_element();
	size_t vectorSize = vec.size();
	EXPECT_EQ(0, vectorSize) << "Vector size should be 0";
}

TEST(AddRemoveElement, FewElements_1) {
	Vector<int> vec;
	vec.add_new_element(34);
	vec.remove_element();
	vec.add_new_element(0);
	vec.remove_element();
	vec.add_new_element(-3);
	vec.remove_element();
	vec.add_new_element(-1028);
	vec.remove_element();
	vec.add_new_element(39398390);
	size_t vectorSize = vec.size();
	EXPECT_EQ(1, vectorSize) << "Vector size should be 1";
}

TEST(AddRemoveElement, FewElements_2) {
	Vector<int> vec;
	// Add 10 elements
	for (size_t i = 0; i < 10; ++i)
		vec.add_new_element(i);
	// Remove 10 elements
	for (size_t i = 0; i < 10; ++i)
		vec.remove_element();
	size_t vectorSize = vec.size();
	EXPECT_EQ(0, vectorSize) << "Vector size should be 0";
}

TEST(AddRemoveElement, FewElements_3) {
	Vector<int> vec;
	// Add 10 elements
	for (size_t i = 0; i < 11; ++i)
		vec.add_new_element(i);
	// Remove 10 elements
	for (size_t i = 0; i < 9; ++i)
		vec.remove_element();
	size_t vectorSize = vec.size();
	EXPECT_EQ(2, vectorSize) << "Vector size should be 2";
}

TEST(AddRemoveElement, FewElements_4) {
	Vector<int> vec;
	// Add 19 elements
	for (size_t i = 0; i < 19; ++i)
		vec.add_new_element(i);
	// Remove 20 elements
	for (size_t i = 0; i < 20; ++i)
		vec.remove_element();
	size_t vectorSize = vec.size();
	EXPECT_EQ(0, vectorSize) << "Vector size should be 0";
}

TEST(RemoveElement, FewElements) {
	Vector<int> vec;
	for (size_t i = 0; i < 10; ++i)
		vec.remove_element();
	size_t vectorSize = vec.size();
	EXPECT_EQ(0, vectorSize) << "Vector size should be 0";
}

TEST(RemoveElement, OneElement) {
	Vector<int> vec;
	vec.remove_element();
	size_t vectorSize = vec.size();
	EXPECT_EQ(0, vectorSize) << "Vector size should be 0";
}