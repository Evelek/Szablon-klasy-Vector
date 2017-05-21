#include "gtest\gtest.h"
#include "vector.h"
using namespace vec;

TEST(resetVector, reset_1) {
	Vector<int> vec;
	vec.reset_vector();
	size_t vectorSize = vec.size();
	EXPECT_EQ(0, vectorSize) << "Vector size should be 0";
}

TEST(resetVector, reset_2) {
	Vector<int> vec;
	for (size_t i = 0; i < 20; ++i)
		vec.add_new_element(i);
	vec.reset_vector();
	size_t vectorSize = vec.size();
	EXPECT_EQ(0, vectorSize) << "Vector size should be 0";
}

TEST(resetVector, reset_3) {
	Vector<int> vec;
	for (size_t i = 0; i < 300; ++i)
		vec.add_new_element(i);
	for (size_t i = 0; i < 300; ++i)
		vec.remove_element();
	vec.reset_vector();
	size_t vectorSize = vec.size();
	EXPECT_EQ(0, vectorSize) << "Vector size should be 0";
}

TEST(resetVector, reset_4) {
	Vector<int> vec;
	for (size_t i = 0; i < 10; ++i)
		vec.remove_element();
	vec.reset_vector();
	size_t vectorSize = vec.size();
	EXPECT_EQ(0, vectorSize) << "Vector size should be 0";
}
