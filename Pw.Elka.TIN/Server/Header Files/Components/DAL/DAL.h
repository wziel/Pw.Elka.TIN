#pragma once
#include "../../Interfaces/IDAL.h"
#include "../../Interfaces/IAdminDAL.h"
#include "../../Interfaces/IClientDAL.h"
class DAL :
	public IClientDAL, public IAdminDAL, public IDAL
{
public:
	DAL();
	~DAL();
/*********************/
/*Ceated for testing!*/
/*********************/
//IClientDAL.h 
	string GetHashOfPassword(string username);
/*********************/
};

