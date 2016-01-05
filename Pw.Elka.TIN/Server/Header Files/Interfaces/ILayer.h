#ifndef I_LAYER
#define I_LAYER
class ILayer
{
public:
	virtual ~ILayer() {};
	virtual void Send(unsigned char* buffer, int size) = 0;
	virtual void Receive(unsigned char* &buffer, int &size) = 0;
};

#endif