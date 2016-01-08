#pragma once
#include "Communicate.h"
#include "../../../Shared/GroupModel.h"
#include<vector>

//Server communicate - sending all groups
class ServComGRPGETALL :
	public Communicate
{
public:
	ServComGRPGETALL(vector <GroupModel> * vect);
	~ServComGRPGETALL();
};

