#pragma once

class GameSocket;
class Message;
class InternetAddress;

class NetworkManager
{
public:
	static NetworkManager *get();

	void update(float dt);

	void setPort(unsigned port);

	void sendMessage(const Message &m, const InternetAddress &address);

	bool setup();
	bool teardown();

private:
	NetworkManager();
	~NetworkManager();

	unsigned extractMessageId(char* message, unsigned size);

private:
	GameSocket *socket = nullptr;

private:
	static NetworkManager *manager;


	
};

