#include <algorithm>
#include <iostream>
#include "PlayerCppAIException.h"
#include "FifoBuffer.h"

using std::copy;
using std::cout;
using std::endl;

namespace PlayerCSharpAI
{

	FifoByteBuffer::FifoByteBuffer(int capacity) : m_capacity(capacity), m_buffer(new unsigned char[capacity])
	{
		m_startIndex = 0;
		m_endIndex = 0;
	}

	FifoByteBuffer::~FifoByteBuffer()
	{
		delete [] m_buffer;
	}

	FifoByteBuffer::FifoByteBuffer(const FifoByteBuffer& f)
	{
		m_capacity = f.m_capacity;
		copy(f.m_buffer, f.m_buffer + m_capacity, m_buffer);
		m_startIndex = f.m_startIndex;
		m_endIndex = f.m_endIndex;
	}

	int FifoByteBuffer::getCount()
	{
		if (m_endIndex > m_startIndex)
			return m_endIndex - m_startIndex;
		if (m_endIndex < m_startIndex)
			return (m_capacity - m_startIndex) + m_endIndex;
		return 0;
	}

	unsigned char FifoByteBuffer::operator [](int index)
	{
		if (index >= getCount())
			throw PlayerCppAIException("Array index out of bounds.");
		return m_buffer[(m_startIndex + index) % m_capacity];
	}

	void FifoByteBuffer::Write(unsigned char data[])
	{
		Write(data, 0, sizeof(data) / sizeof(unsigned char));
	}

	void FifoByteBuffer::Write(unsigned char data[], int offset, int length)
	{

		if (getCount() + length >= m_capacity)
			throw PlayerCppAIException("buffer overflow");
		if (m_endIndex + length >= m_capacity)
		{
			int endLen = m_capacity - m_endIndex;
			int remainingLen = length - endLen;

			copy(data + offset, data + offset + endLen, m_buffer + m_endIndex);
			copy(data + offset + endLen, data + offset + endLen + remainingLen, m_buffer);
			m_endIndex = remainingLen;
		}
		else
		{
			copy(data + offset, data + offset + length, m_buffer + m_endIndex);
			m_endIndex += length;
		}
	}

	unsigned char* FifoByteBuffer::Read(int len)
	{
		return m_Read(len, false);
	}

	unsigned char* FifoByteBuffer::Peek(int len)
	{
		return m_Read(len, true);
	}

	unsigned char* FifoByteBuffer::m_Read(int len, bool keepData)
	{
		if (len > getCount())
			throw PlayerCppAIException("not enough data in buffer");

		unsigned char* result = new unsigned char[len];

		if (m_startIndex + len < m_capacity)
		{
			copy(m_buffer + m_startIndex, m_buffer + m_startIndex + len, result);
			if (!keepData)
				m_startIndex += len;
			return result;
		}

		int endLen = m_capacity - m_startIndex;
		int remainingLen = len - endLen;
		copy(m_buffer + m_startIndex, m_buffer + m_startIndex + endLen, result);
		copy(m_buffer, m_buffer + remainingLen, result + endLen);
		if (!keepData)
			m_startIndex = remainingLen;

		return result;
	}
}
