#pragma once
#include "../../Interfaces/ISmtpLayer.h"

class SmtpLayer :
	public ISmtpLayer
{
public:
	SmtpLayer();
	SmtpLayer(MessagesQueue &queue);
	~SmtpLayer();

	//ISmtpLayer
	void Start();

};

