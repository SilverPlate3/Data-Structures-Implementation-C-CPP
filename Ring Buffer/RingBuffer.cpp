#include <iostream>
#include <optional>

template<typename T, unsigned int N>
class RingBuffer
{
public:

	std::optional<T> Read()
	{
		if (IsEmpty())
			return std::nullopt;

		std::optional<T> temp = std::nullopt;
		temp.swap(ring[consumer]);
		consumer = (consumer + 1) % N;
		return temp;
	}

	bool Write(T value)
	{
		if (IsFull())
			return false;

		ring[producer] = value;
		producer = (producer + 1) % N;
		return true;
	}

	std::optional<T> Front()
	{
		if (IsEmpty())
			return std::nullopt;

		return ring[consumer];
	}

	std::optional<T> Rear()
	{
		if (IsEmpty())
			return std::nullopt;

		int index = producer == 0 ? N - 1 : producer - 1;
		return ring[index];
	}

	bool IsEmpty()
	{
		return producer == consumer && !ring[producer].has_value();
	}

	bool IsFull()
	{
		return producer == consumer && ring[producer].has_value();
	}

private:
	std::array<std::optional<T>, N> ring;
	unsigned int producer = 0;
	unsigned int consumer = 0;
};

int main()
{
	RingBuffer<std::string, 4> rb;
	rb.Write("123");
}