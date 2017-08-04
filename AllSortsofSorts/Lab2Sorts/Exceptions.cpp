#include "Exceptions.h"
#include <iostream>
using std::endl;
using std::cout;

Exception::Exception():m_Message('\0')
{
	cout << "No arg Exception Ctor called." << endl;
}

Exception::Exception(char * msg)
{
	cout << "1 arg exception Ctor called." << endl;
	m_Message = new char[strlen(msg) + 1];
	strcpy(m_Message, msg);
	//remember to deallocate
}
Exception::Exception(const Exception & obj)
{
	cout << "Exception copy Ctor called." << endl;

	m_Message = new char [strlen (obj.m_Message) + 1];
	strcpy(m_Message, obj.m_Message);
}

Exception::~Exception()
{
	delete [] m_Message;
	cout << "Exception Dtor called" << endl;
}

Exception & Exception::operator=(const Exception & rhs)
{
	cout << "Exception assignment operator called." << endl;

	if(this != & rhs)
	{
		if(strlen(rhs.m_Message) != strlen(m_Message))
		{
			delete [] m_Message;
			m_Message = new char[strlen(rhs.m_Message) + 1];
		}
		strcpy(m_Message, rhs.m_Message);
	}
	return * this;
}

const char * Exception::GetMessage()
{
	cout << "Exception Getter called." << endl;
	return m_Message;
}

void Exception::SetMessage(char * msg)
{
	cout << "Exception Setter called." << endl;
	if(strlen(m_Message) != strlen(msg))
	{
		delete [] m_Message;
		m_Message = new char[strlen(msg) + 1];
	}
	strcpy(m_Message, msg);
}

ostream & operator<<(ostream & os, const Exception & obj)
{
	cout << "Overloaded << called." << endl;
	os << obj.m_Message << endl;
	return os;
}