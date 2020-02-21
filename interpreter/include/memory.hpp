#include <iostream>
#include <vector>
namespace vm {
	const int DEFAULT_MEM_SIZE = 4096;
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

		int get_pos() { return pos; }
		int pc = 0;
		// they will call during parsing
		void new_block() { block_info.push_back(pc); }
		void end_block() { pc = block_info.back(); block_info.pop_back(); }
		// they will call during the runtime
		void new_func() { /*TO DO*/ }
		void end_func() {   /*TO DO*/ }
	private:
		std::vector<size_t> block_info;
		std::vector<size_t> call_stack;
		void realloc();
		void check();
		char *content;
		int pos = 0;
		int capacity;
	};
	extern Memory mem;
}