#pragma once
#include "Communicate.h"
#include "../../../Shared/MessageModel.h"

//Client communicate - sending one message scheme
class ServComMSGGETONE :
	public Communicate
{
public:
	ServComMSGGETONE(MessageModel *messageDB);
	~ServComMSGGETONE();
};

