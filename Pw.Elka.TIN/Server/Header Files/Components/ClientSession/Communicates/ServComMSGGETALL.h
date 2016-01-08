#pragma once
#include "Communicate.h"
#include "../../../Shared/MessageModel.h"
#include <vector>

//Server communicate - sending all message schemes
class ServComMSGGETALL :
	public Communicate
{
public:
	ServComMSGGETALL(vector <MessageModel> * vect);
	~ServComMSGGETALL();
};

