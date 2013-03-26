#include "stdafx.h"
#include "FifoBuffer.h"

using namespace System;
using namespace System::Collections;
namespace PlayerCPPAI
{

	FifoByteBuffer::FifoByteBuffer(int capacity)
	{
		_buffer = gcnew array<Byte>(capacity);
	}

	int FifoByteBuffer::Count::get()
	{
		if (_endIndex > _startIndex)
			return _endIndex - _startIndex;
		if (_endIndex < _startIndex)
			return (_buffer->Length - _startIndex) + _endIndex;
		return 0;
	}

	Byte FifoByteBuffer::default::get(int index)
	{
		if (index >= Count)
			throw gcnew ArgumentOutOfRangeException();
		return _buffer[(_startIndex + index) % _buffer->Length];
	}

	void FifoByteBuffer::Write(array<Byte> ^data)
	{
		Write(data, 0, data->Length);
	}

	void FifoByteBuffer::Write(array<Byte> ^data, int offset, int length)
	{

		if (Count + length >= _buffer->Length)
			throw gcnew Exception("buffer overflow");
		if (_endIndex + length >= _buffer->Length)
		{
			int endLen = _buffer->Length - _endIndex;
			int remainingLen = length - endLen;

			Array::Copy(data, offset, _buffer, _endIndex, endLen);
			Array::Copy(data, offset + endLen, _buffer, 0, remainingLen);
			_endIndex = remainingLen;
		}
		else
		{
			Array::Copy(data, offset, _buffer, _endIndex, length);
			_endIndex += length;
		}
	}

	array<Byte> ^FifoByteBuffer::Read(int len)
	{
		return _Read(len, false);
	}

	array<Byte> ^FifoByteBuffer::Peek(int len)
	{
		return _Read(len, true);
	}

	array<Byte> ^FifoByteBuffer::_Read(int len, bool keepData)
	{
		if (len > Count)
			throw gcnew Exception("not enough data in buffer");
		array<Byte> ^result = gcnew array<Byte>(len);
		if (_startIndex + len < _buffer->Length)
		{
			Array::Copy(_buffer, _startIndex, result, 0, len);
			if (!keepData)
				_startIndex += len;
			return result;
		}
		int endLen = _buffer->Length - _startIndex;
		int remainingLen = len - endLen;
		Array::Copy(_buffer, _startIndex, result, 0, endLen);
		Array::Copy(_buffer, 0, result, endLen, remainingLen);
		if (!keepData)
			_startIndex = remainingLen;
		return result;
	}
}
