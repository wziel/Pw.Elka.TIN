#ifndef I_TCP_LAYER_MANAGER
#define I_TCP_LAYER_MANAGER

class ILayer;

class ITcpLayerManager
{
public:
	virtual bool Initialize(int socketfd) = 0;
	virtual int End() = 0;
};

#endif