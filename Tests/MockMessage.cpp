#include "MockMessage.h"

std::function<void()> mog::network::MockMessage::executeOnServerFunction = nullptr;
std::function<void()> mog::network::MockMessage::executeOnClientFunction = nullptr;



void mog::network::MockMessage::setExecuteOnServerCommand(std::function<void()> f)
{
	executeOnServerFunction = f;
}

void mog::network::MockMessage::setExecuteOnClientCommand(std::function<void()> f)
{
	executeOnClientFunction = f;
}

void mog::network::MockMessage::executeOnServer(ServerGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const
{
	if (executeOnServerFunction != nullptr)
		executeOnServerFunction();
}

void mog::network::MockMessage::executeOnClient(ClientGame *game, const ParameterContainer &parameters, const network::InternetAddress &address) const
{
	if (executeOnClientFunction != nullptr)
		executeOnClientFunction();
}

