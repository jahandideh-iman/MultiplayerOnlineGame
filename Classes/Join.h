#pragma once
#include "Command.h"
class Join :
	public Command
{
public:
	Join();
	~Join();

	virtual void execute(const NetworkData &data) const override;

	virtual NetworkData *write() const override;

	virtual unsigned getCode() const override;
};

