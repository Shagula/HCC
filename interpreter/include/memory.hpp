#include <iostream>
#include <vector>
namespace vm {
	const int DEFAULT_MEM_SIZE = 4096;
	class Memory {
	public:
		Memory(int sz= DEFAULT_MEM_SIZE);
		template<typename _Ty>
		_Ty extract(int p) {
			return *(_Ty*)(content + p);
		}
		template<typename _Ty>
		void write(_Ty value, int p) {
			*(_Ty*)(content + p) = value;
		}

		template<typename _Ty>
		int push(_Ty value)
		{
			write(value, pos);
			pos += sizeof(_Ty);
			return pos - sizeof(_Ty);
		}
		void pop(int sz) { pos -= sz; }
	private:
		void realloc();
		void check();
		char *content;
		int pos=0;
		int capacity;
	};
	extern Memory mem;
}