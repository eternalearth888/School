#pragma once

// code primarily from http://stackoverflow.com/questions/7122972/buffering-byte-data-in-c
// Edited by Windward Studios, Inc. (www.windward.net). No copyright claimed by Windward on changes.

using namespace System;
using namespace System::Collections;

namespace PlayerCPPAI
{
	public ref class FifoByteBuffer
	{
	private:
		initonly array<Byte> ^_buffer;
		int _endIndex;
		int _startIndex;

		array<Byte> ^_Read(int len, bool keepData);

	public:
		FifoByteBuffer(int capacity);

		property int Count
		{
			int get();
		}

		property Byte default[int]
		{
			Byte get(int index);
		}

		void Write(array<Byte> ^data);

		void Write(array<Byte> ^data, int offset, int length);

		array<Byte> ^Read(int len);

		array<Byte> ^Peek(int len);
	};
}
