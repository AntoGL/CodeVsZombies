#include "pch.h"
#include "ObjectPool.h"

using namespace std;
using namespace testing;

struct TestObject
{
	static int CreatedObjectCount;

	TestObject()
	{
		CreatedObjectCount++;
	}
};

int TestObject::CreatedObjectCount = 0;

TEST(ObjectPool_Test, get_FirstObject_ReturnNotNullObjectPointer)
{
	ObjectPool<TestObject, 1> pool;

	const TestObject* obj = pool.get();

	ASSERT_TRUE(nullptr != obj);
}

TEST(ObjectPool_Test, AfterFirstGet_NotCreateObject)
{
	TestObject::CreatedObjectCount = 0;
	ObjectPool<TestObject, 1> pool;

	ASSERT_EQ(0, TestObject::CreatedObjectCount);
}

TEST(ObjectPool_Test, get_AfterFirstGet_CreateChunkSizeObjects)
{
	TestObject::CreatedObjectCount = 0;
	ObjectPool<TestObject, 2> pool;

	pool.get();

	ASSERT_EQ(2, TestObject::CreatedObjectCount);
}