#include <libusb/libusb.h>
#include <string>
#include <list>
#include <memory>

using namespace std::tr1;

class Heracles
{

public:

	/// Constructor
	Heracles();
	
	/// Destructor
	virtual ~Heracles();

protected:

	virtual void Open();

	virtual void Close();

		


private:

	


// Utility methods

	std::wstring libusbTranslateResult(int LibusbResult);

// Static members

	libusb_context* getContext()const;
	
	
	/// Global libusb context
	static libusb_context* libusbContext;

	// Number of libusb devices using this context.
	static unsigned int deviceCount;
};

