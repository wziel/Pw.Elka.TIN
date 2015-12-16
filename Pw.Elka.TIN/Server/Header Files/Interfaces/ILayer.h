#ifndef I_LAYER
#define I_LAYER
class ILayer
{
public:
	virtual void Send(char* buffer, int size) = 0;
	virtual void Receive(char* buffer, int size) = 0;
};

#endif