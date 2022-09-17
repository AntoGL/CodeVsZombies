#include "pch.h"
#include "ObjectPool.h"

using namespace std;
using namespace testing;

struct TestObject
{
	static int CreatedObjectCount;
	static int DeleatedObjectCount;

	static int NextKey;
	int key;

	TestObject()
	{
		CreatedObjectCount++;

		key = ++NextKey;
	}

	TestObject(const int key)
		: key(key)
	{
		CreatedObjectCount++;
	}

	~TestObject()
	{
		DeleatedObjectCount++;
	}
};

int TestObject::CreatedObjectCount = 0;
int TestObject::DeleatedObjectCount = 0;
int TestObject::NextKey = 0;

TEST(ObjectPool_Test, get_FirstObject_ReturnNotNullObjectPointer)
{
	ObjectPool<TestObject, 1> pool;

	const TestObject* obj = pool.get();

	ASSERT_TRUE(nullptr != obj);
}

TEST(ObjectPool_Test, Constructor_AfterCreate_NotCreateObject)
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

TEST(ObjectPool_Test, get_NoObjectsAvailable_CreateNewObjects)
{
	ObjectPool<TestObject, 2> pool;
	pool.get();
	pool.get();
	TestObject::CreatedObjectCount = 0;

	pool.get();

	ASSERT_EQ(2, TestObject::CreatedObjectCount);
}

TEST(ObjectPool_Test, get_ObjectsAvailable_NoCreateNewObjects)
{
	ObjectPool<TestObject, 2> pool;
	pool.get();
	TestObject::CreatedObjectCount = 0;

	pool.get();

	ASSERT_EQ(0, TestObject::CreatedObjectCount);
}

TEST(ObjectPool_Test, free_AfterFree_NoDeleteObject)
{
	ObjectPool<TestObject, 2> pool;
	TestObject* object = pool.get();
	TestObject::DeleatedObjectCount = 0;

	pool.free(object);

	ASSERT_EQ(0, TestObject::DeleatedObjectCount);
}

TEST(ObjectPool_Test, get_WithArguments_ReturnObjectConstructedWithArgument)
{
	ObjectPool<TestObject, 2> pool;

	const TestObject* object = pool.get(13);

	ASSERT_EQ(13, object->key);
}