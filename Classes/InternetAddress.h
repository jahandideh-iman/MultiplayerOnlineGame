#pragma once
class InternetAddress
{
public:

	InternetAddress();
	InternetAddress(unsigned char a,
		unsigned char b,
		unsigned char c,
		unsigned char d,
		unsigned short port);
	InternetAddress(unsigned int address,
		unsigned short port);
	unsigned int GetAddress() const;
	unsigned char GetA() const;
	unsigned char GetB() const;
	unsigned char GetC() const;
	unsigned char GetD() const;
	unsigned short GetPort() const;

private:

	unsigned int address;
	unsigned short port;
};

