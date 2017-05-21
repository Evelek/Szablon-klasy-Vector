#include "gtest\gtest.h"
#include "vector.h"
using namespace vec;

TEST(VectorCopy, AddNewElement_1) {
	Vector<int> src;
	for (size_t i = 0; i < 10; ++i)
		src.add_new_element(i);
	Vector<int> dst;
	dst = src;
	size_t srcSize = src.size();
	size_t dstSize = dst.size();
	EXPECT_EQ(10, srcSize) << "Source vector size should be 10";
	EXPECT_EQ(10, dstSize) << "Destination vector size should be 10";
}

TEST(VectorCopy, AddNewElement_2) {
	Vector<int> src;
	for (size_t i = 0; i < 10; ++i)
		src.add_new_element(i);
	Vector<int> dst;
	dst = src;
	for (size_t i = 0; i < 10; ++i)
		dst.add_new_element(i);
	size_t srcSize = src.size();
	size_t dstSize = dst.size();
	EXPECT_EQ(10, srcSize) << "Source vector size should be 10";
	EXPECT_EQ(20, dstSize) << "Destination vector size should be 20";
}

TEST(VectorCopy, ResetVector) {
	Vector<int> src;
	for (size_t i = 0; i < 10; ++i)
		src.add_new_element(i);
	Vector<int> dst;
	dst = src;
	src.reset_vector();
	dst.reset_vector();
	size_t srcSize = src.size();
	size_t dstSize = dst.size();
	EXPECT_EQ(0, srcSize) << "Source vector size should be 0";
	EXPECT_EQ(0, dstSize) << "Destination vector size should be 0";
}
