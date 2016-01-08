#include "../../../../Header Files/Components/ClientSession/Communicates/CliComSEND.h"



CliComSEND::CliComSEND(unsigned char* communicateBuffer) : Communicate(communicateBuffer)
{
	unsigned char* myBuffer = communicateBuffer + 1;
	unsigned char** localBuffer = &myBuffer;
	parseShort(localBuffer); //ignore, always should be 4 (for int)
	grpId = parseInt(localBuffer);
	parseShort(localBuffer); //ignore, always should be 4 (for int)
	msgId = parseInt(localBuffer);
	short fieldsNumber = parseShort(localBuffer);

	for (short i = 0; i < fieldsNumber; ++i)
	{
		fields.push_back(parseString(localBuffer));
	}
}


CliComSEND::~CliComSEND()
{
}

vector<string> CliComSEND::getFields()
{
	return fields;
}

int CliComSEND::getGrpId()
{
	return grpId;
}
int CliComSEND::getMsgId()
{
	return msgId;
}