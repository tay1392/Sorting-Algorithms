#ifndef ARRAY_H
#define ARRAY_H
template <typename T>
class Array
{
	public:
		Array();
		Array(int length, int StartIndex = 0);
		Array(const Array & obj);
		~Array();
		Array<T> & operator=(const Array & rhs);
		T & operator[](int index);
		int GetStartIndex();
		int GetLength();
		void SetStartIndex(int start_index);
		void ChangeLength(Array & obj, int size);

	private:
		T * m_Data;
		int m_Length;
		int m_StartIndex;
};
#endif

#include <iostream>
using std::cout;
using std::endl;

template <class T>
Array<T>::Array()
	: m_Length(0), m_StartIndex(0), m_Data(nullptr)
{
	m_Data = new T[m_Length];
	//cout << "No arg Ctor called." << endl;
}

template <typename T>
Array<T>::~Array()
{
	delete [] m_Data;
	m_Data = nullptr;
	m_Length = 0;
	m_StartIndex = 0;
	//cout << "Array Dtor called." << endl;
}

template <typename T>
Array<T>::Array(int length, int StartIndex = 0)
	:m_Length(length), m_StartIndex(StartIndex)
{
	m_Data = new T[m_Length];
	//cout << "2 arg Ctor called" << endl;
}

template <typename T>
Array<T>::Array(const Array & rhs)
	:m_Length(rhs.m_Length), m_StartIndex(rhs.m_StartIndex)
{
	//cout << "Array copy Ctor called." << endl;
	m_Data = new T[rhs.m_Length];

	for(int i = 0; i < (m_Length + m_StartIndex); i++)
	{
		m_Data[i] = rhs.m_Data[i];
	}
}

template <typename T>
Array<T> & Array<T>::operator=(const Array & rhs)
{
	//cout << "Array assignment operator called." << endl;

	if(this != &rhs)
	{
		if(m_Length != rhs.m_Length)
		{
			delete [] m_Data;
			m_Data = new T[rhs.m_Length];
		}
		for(int i = 0; i < m_Length; i++)
			m_Data[i] = rhs.m_Data[i];
	}
	return * this;
}

template <typename T>
int Array<T>::GetLength()
{
	//cout << "Array length Getter called." << endl;
	return m_Length;
}

template <typename T>
int Array<T>::GetStartIndex()
{
	//cout << "Array Start index Getter called." << endl;
	return m_StartIndex;
}

template <typename T>
void Array<T>::SetStartIndex(int index)
{
	//cout << "Set Array index called." << endl;
	m_StartIndex = index;
}

template <typename T>
T & Array<T>::operator[](int indx)
{
	if(indx < m_StartIndex || indx >= (m_Length + m_StartIndex))
	{
		throw Exception("ERROR: Out of bounds of Array");
	}
	else
	{
		return m_Data[indx - m_StartIndex];
	}

	cout << "Overloaded [ ] operator called." << endl;
}

template <typename T>
void Array<T>::ChangeLength(Array & obj, int size)
{
	if (size < 0)
	{
		throw Exception("ERROR: Cannot have negative array length");
	}
	else
	{
		Array <T> temp(obj);
		obj.m_Length = size;

		delete [] obj.m_Data;

		obj.m_Data = new T[obj.m_Length];
		for(int i = obj.GetStartIndex(); i < (obj.GetStartIndex() + obj.GetLength()); i++)
		{
			obj.m_Data[i] = temp.m_Data[i];
		}
		for(int i = temp.GetLength(); i < obj.GetLength(); i++)
		{
			obj.m_Data[i] = T();
		}
	}
}