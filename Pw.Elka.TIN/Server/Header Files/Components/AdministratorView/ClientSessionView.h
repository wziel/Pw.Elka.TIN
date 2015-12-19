#pragma once

#include "../RootManager/Enums.h"
#include<string>

struct ClientSessionView {
public:
	unsigned connectionId;
	ClientSessionState state;
	std::string clientName;
};
