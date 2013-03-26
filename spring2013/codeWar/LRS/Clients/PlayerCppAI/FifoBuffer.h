#ifndef FIFO_BUFFER_H
#define FIFO_BUFFER_H

// code primarily from http://stackoverflow.com/questions/7122972/buffering-byte-data-in-c

namespace PlayerCSharpAI
{
	class FifoByteBuffer
	{
	public:
		FifoByteBuffer(int capacity);
		~FifoByteBuffer();
		FifoByteBuffer(const FifoByteBuffer& f);

		int getCount();

		unsigned char operator [](int index);

		// copies data to the buffer.
		void Write(unsigned char data[]);
		// copies n bytes from data to the buffer, starting at data[offset].
		void Write(unsigned char data[], int offset, int length);

		// read len characters. they are removed from the buffer.
		// caller is responsible for deleting the returned byte array.
		unsigned char* Read(int len);

		// read len characters. they are not removed from the buffer.
		// caller is responsible for deleting the returned byte array.
		unsigned char* Peek(int len);

	private:
		// read len characters. they are removed from the buffer.
		// caller is responsible for deleting the returned byte array.
		unsigned char* m_Read(int len, bool keepData);

		unsigned char* m_buffer;
		// index of the first byte in _buffer
		int m_startIndex;
		// index after the last byte in _buffer (if 5, last byte is 4)
		int m_endIndex;
		int m_capacity;
	};
}

#endif
