#include "CppUTest/TestHarness.h"
#include "Engine/Buffer.h"

namespace mog
{
	TEST_GROUP(Buffer)
	{
	};

	TEST(Buffer, IsEmptyWhenCreated)
	{
		Buffer buffer;
		CHECK_TRUE(buffer.isEmpty());
	}

	TEST(Buffer, IsNotEmptyWhenWritten)
	{
		Buffer buffer;
		buffer.write("sample");
		CHECK_FALSE(buffer.isEmpty());
	}

	TEST(Buffer, SizeIsCorrectWhenWritten)
	{
		Buffer buffer;
		buffer.write("sample");
		//TODO: Check whether null terminator must be added to size or not
		CHECK_EQUAL(std::string("sample").size(), buffer.getSize());
	}

	TEST(Buffer, dataIsTheWrittenString)
	{
		Buffer buffer;
		buffer.write("sample");
		char *data = buffer.getData();
		STRCMP_EQUAL("sample",data);
		delete []data;
	}

	TEST(Buffer, IsEmptyAfferClear)
	{
		Buffer buffer;
		buffer.write("sample");
		buffer.clear();
		CHECK_TRUE(buffer.isEmpty());
	}

	TEST(Buffer, dataIsCorretAfterMoreThanOneWrite)
	{
		Buffer buffer;
		buffer.write("word1");
		buffer.write(" word2");
		char *data = buffer.getData();
		STRCMP_EQUAL("word1 word2", data);
		delete[]data;
	}

}