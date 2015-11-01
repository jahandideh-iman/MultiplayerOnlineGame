#pragma once
class Message
{
public:
	Message();
	virtual ~Message();

	virtual void read() = 0;
	virtual void write() = 0;

protected:
	static unsigned int code;
};

