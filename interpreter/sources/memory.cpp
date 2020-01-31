#include "../include/memory.hpp"
namespace vm
{
	Memory mem;
	Memory::Memory(int sz)
	{
		content = new char(2 * sz);
		ins_block = content;
		capacity=2 * sz;
	}
	void Memory::write_ins(const char * ins, int sz)
	{
		for (int i = 0; i < sz; i++) {
			*content = ins[i];
			content++;
			if (2*(content - ins_block) > capacity)
				realloc();
		}
	}
	void Memory::realloc()
	{
		char *tmp = new char[capacity * 2];
		memcpy(tmp, ins_block, capacity);
		int length = content - ins_block;
		delete content;
		content = tmp + length;
		ins_block = tmp;
		capacity *= 2;
	}
	void Memory::check()
	{
		while (pos * 2 > capacity)
			realloc();
	}
}