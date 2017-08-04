#ifndef EXCEPTIONS
#define EXCEPTIONS
#include <iostream>
using std::ostream;
class Exception
{

	public:
		Exception();
		Exception(char * msg);
		Exception(const Exception & obj);
		~Exception();
		Exception & operator=(const Exception & rhs);
		const char * GetMessage();
		void SetMessage(char * msg);
		friend ostream & operator<<(ostream & os, const Exception & obj);
	private:
		char * m_Message;
};
#endif