#include "CppUTest/TestHarness.h"
#include "Network/NetworkManager.h"
#include "Network/Message.h"
#include "Network/MessageDatabase.h"
#include "Network/GameSocket.h"
#include "Network/InternetAddress.h"
#include "Engine/Buffer.h"
#include <map>
#include <string>
#include "Engine/GlobalData.h"


namespace mog
{
	namespace network
	{

		class MockSocket;

		class MockSocketDataBase
		{
		public:

			void add(unsigned short port, MockSocket *socket)
			{
				sockets.emplace(port, socket);
			}

			MockSocket *find(unsigned short port)
			{
				return sockets.find(port)->second;
			}

			~MockSocketDataBase()
			{
				sockets.clear();
			}

			static MockSocketDataBase *db;

		private:
			std::map<unsigned short, MockSocket*> sockets;
		};


		MockSocketDataBase *MockSocketDataBase::db = nullptr;

		class MockSocket : public network::GameSocket
		{
		public:
			virtual void open(unsigned short port) override 
			{ 
				this->port = port; 
				MockSocketDataBase::db->add(port, this);
			}

			virtual bool send(const Address &destination,
				const char * data,
				int size)
			{
				MockSocketDataBase::db->find(destination.getPort())->buffer.write(data);
				return true;
			}

			virtual int receive(Address &sender,
				void * data,
				int size)
			{
				char *newData = buffer.getData();
				strcpy_s((char*)data, size, newData);

				delete []newData;
				return buffer.getSize();
				buffer.clear();
			}

			unsigned short port;
			Buffer buffer;
		};

		class MockMessage : public network::Message
		{
		public:

			~MockMessage()
			{
				int a=2;
			}
			void execute(const ParameterContainer &parameters, const network::InternetAddress &address) const
			{
				const_cast<MockMessage*>(this)->isExecuted = true;
			}

			AUTOID(MockMessage, getID);

			static bool isExecuted;;
		};

		bool MockMessage::isExecuted = false;

		TEST_GROUP(NetworkManager)
		{
			NetworkManager *manager = nullptr;

			void setup() override
			{
				manager = NetworkManager::get();
				MockSocketDataBase::db = new MockSocketDataBase();
			}

			void teardown() override
			{
				NetworkManager::clear();
				delete MockSocketDataBase::db;
			}
		};

		TEST(NetworkManager, ExecutesMessageOnRecieve)
		{
			auto serverManager = new NetworkManager();
			auto clientManager = new NetworkManager();

			serverManager->initialSocket<MockSocket>();
			clientManager->initialSocket<MockSocket>();

			serverManager->setPort(8081);
			clientManager->setPort(8082);


			REGISTER_MESSAGE(MockMessage);
			serverManager->sendMessage(MockMessage(), network::InternetAddress(8082));
			clientManager->update(0.5);

			CHECK_TRUE(MockMessage::isExecuted);
			network::MessageDatabase::clear();
			mog::GlobalData::clear();

			delete clientManager;
			delete serverManager; 

		}
	}
}
