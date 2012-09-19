
#include <string>
#include <list>
#include <memory>
#include <libusbpp.h>

class Heracles : private LibUSB::Device
{

public:

	/// Constructor
	Heracles(std::shared_ptr<LibUSB::DeviceImpl> pInit);
	
	/// Destructor
	virtual ~Heracles();

	/// Configuration Mode

protected:

	/// Notification of a completed transfer
	/// \warning This function can be called from other threads when using asynchronous transfers!
	virtual void TransferEventNotification(std::shared_ptr<LibUSB::Transfer> pCompletedTransfer);
		

	


	/// Keepalive generator

private:

	/// 

	
};

