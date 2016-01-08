#pragma once
#include "Communicate.h"
#include "../../../Shared/GroupModel.h"

//Server communicate - sending one group
class ServComGRPGETONE :
	public Communicate
{
public:
	ServComGRPGETONE(GroupModel *groupDB);
	~ServComGRPGETONE();
};

