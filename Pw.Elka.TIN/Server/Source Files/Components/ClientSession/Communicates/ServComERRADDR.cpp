#include "../../../../Header Files/Components/ClientSession/Communicates/ServComERRADDR.h"


ServComERRADDR::ServComERRADDR()
{
	size = 1;
	communicateBuffer = new unsigned char;
	communicateBuffer[0] = _SERVCOMERRADDR;
}


ServComERRADDR::~ServComERRADDR()
{
	delete communicateBuffer;
}
