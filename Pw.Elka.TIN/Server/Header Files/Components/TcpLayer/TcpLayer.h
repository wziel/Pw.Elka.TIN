#pragma once
#include "../../Interfaces/ILayer.h"
#include "../../Interfaces/ITcpLayerManager.h"

class TcpLayer :
	public ILayer, public ITcpLayerManager
{
public:
	TcpLayer();
	~TcpLayer();
};

