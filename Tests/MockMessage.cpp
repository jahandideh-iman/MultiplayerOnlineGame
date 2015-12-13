#include "MockMessage.h"

std::function<void()> mog::network::MockMessage::executeFunction = nullptr;



void mog::network::MockMessage::setExecuteCommand(std::function<void()> f)
{
	executeFunction = f;
}

void mog::network::MockMessage::execute(const ParameterContainer &parameters, const network::InternetAddress &address) const
{
	if (executeFunction != nullptr)
		executeFunction();
}
