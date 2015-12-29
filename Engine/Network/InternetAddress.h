#pragma once
namespace mog
{
	namespace network
	{
		class InternetAddress
		{
		public:

			InternetAddress();
			InternetAddress(const InternetAddress&other);

			InternetAddress(unsigned short port);
			InternetAddress(unsigned char a,
				unsigned char b,
				unsigned char c,
				unsigned char d,
				unsigned short port);
			InternetAddress(unsigned int address,
				unsigned short port);
			//InternetAddress(char *address, unsigned short port);

			unsigned int getAddress() const;
			unsigned char getA() const;
			unsigned char getB() const;
			unsigned char getC() const;
			unsigned char getD() const;
			unsigned short getPort() const;

			void setAddress(unsigned address);
			void setPort(unsigned short port);

		private:
			unsigned int address;
			unsigned short port;
		};
	}
}