#pragma once

struct NetworkData{

	NetworkData(char *data, unsigned size)
	{
		this->data = data;
		this->size = size;
	}

	char *data;
	unsigned size;
};

class Message
{

public:
	Message();
	virtual ~Message();

	virtual void execute(const NetworkData &data) const = 0;
	virtual NetworkData *write() const = 0;
	virtual unsigned getCode() const = 0;

protected:
	static unsigned int code;
};

