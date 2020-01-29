#include "../include/memory.hpp"
namespace vm
{
	Memory mem;
	Memory::Memory(int sz)
	{
		content = new char(2 * sz);
		capacity=2 * sz;
	}
	void Memory::realloc()
	{
		char *tmp = new char[capacity * 2];
		memcpy(tmp, content, capacity);
		delete content;
		content = tmp;
		capacity *= 2;
	}
	void Memory::check()
	{
		while (pos * 2 > capacity)
			realloc();
	}
}