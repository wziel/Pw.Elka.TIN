#ifndef I_CIPHER_MANAGER
#define I_CIPHER_MANAGER


class ILayer;


class ICipherManager
{
public:
	virtual ~ICipherManager() = 0;
	virtual void Initialize(ILayer &bottomLayer) = 0;
};

#endif