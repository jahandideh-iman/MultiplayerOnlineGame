#include "CppUTest/TestHarness.h"
#include "Engine/Core/Buffer.h"

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

		//NOTE: Null Terminator is counted
		CHECK_EQUAL(std::string("sample").size() +1, buffer.getSize());
	}

	TEST(Buffer, DataIsTheWrittenString)
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

	TEST(Buffer, DataIsCorretAfterMoreThanOneWrite)
	{
		Buffer buffer;
		buffer.write("word1");
		buffer.write(" word2");

		char *data = buffer.getData();
		STRCMP_EQUAL("word1 word2", data);
		delete[]data;
	}

	TEST(Buffer, CanBeInitializedByString)
	{
		std::string input = "input";

		Buffer buffer(input);

		char *data = buffer.getData();
		STRCMP_EQUAL(input.c_str(), data);
		delete[]data;
	}

}