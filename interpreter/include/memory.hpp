#include <iostream>
#include <vector>
namespace vm {
	const int DEFAULT_MEM_SIZE = 4096;
	using index_type = int;
	class Memory {
	public:
		Memory(int sz= DEFAULT_MEM_SIZE);
		template<typename _Ty>
		_Ty& extract(int p) {
			return *(_Ty*)(content + p);
		}
		template<typename _Ty>
		void write(_Ty value, int p) {
			*(_Ty*)(content + p) = value;
		}
		int get_pos()const { return pos; }
		template<typename _Ty>
		int push(_Ty value)
		{
			check();
			write(value, pos);
			pos += sizeof(_Ty);
			return pos - sizeof(_Ty);
		}
		void pop(int sz) { pos -= sz; }
		char *operator[](void *ptr) {
			return content+(*(index_type*)ptr);
		}
		int get_pos() { return pos; }
		int pc = 0;
		// they will call during parsing
		void new_block() { block_info.push_back(pc); }
		void end_block() { pc = block_info.back(); block_info.pop_back(); }
		// they will call during the runtime
		void new_func(int off) { call_stack.push_back(off); content += off; }
		void end_func() { content -= call_stack.back(); call_stack.pop_back(); }
	private:
		std::vector<size_t> block_info;
		std::vector<int> call_stack;
		void realloc();
		void check();
		char *content;
		int pos = 0;
		int capacity;
	};
	extern Memory mem;
}