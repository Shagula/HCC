#include "../include/instructions.hpp"
namespace vm
{
	std::vector<std::pair<instruction_type, char*>> glo_instructions;
	int pc;
	void run()
	{
		while (pc < glo_instructions.size())
			glo_instructions[pc].first(glo_instructions[pc].second);
	}
	/*instruction_type gen_bin_op(char _ty, int op)
	{
		int type = _ty&(0x0F);
		int mod = _ty&(0xF0) << 4;
		int bit = 0;
	
		switch (type) {
		case 0:
		case 1:
		case 2:
		case 3:
			bit = pow(2, type);
			switch (mod) {
				// 0 0 
			case 0:
				return [](char *content) {
					(int *)(content)
				}
			case 1:
			case 3:
			case 4:
			}
		case 4:
		case 5:
		case 6:
		}
		auto ret=[](char* content){
			// TODO a little bit hard, or we can make the repeat code... 
		};
		return ret;
	}*/
}