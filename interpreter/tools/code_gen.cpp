#include <iostream>
#include <map>
#include <string>
// I merely don't want to imply strange lambda skills to simplify the code.
// So generate those functions by programs is okay.
// exclude the file from build
enum InsTag :char {
	SADD = 0x01, SSUB, SMUL, SDIV,
	EQ, NE, GT, GE, LE, LT,
	AND, OR, W8, W16, W32, W64, WR128,
	JMP, CALL
};
std::string map_content = "std::map<int16_t,instruction_type> _bin_operator_ins_table={";
std::string func_template(std::string func_name, std::string cvt, std::string op, std::string off) {
	std::string ret = "void " + func_name + " (char *ins){\n"
		+ "\tmem.extract<" + cvt + ">(*(index_type*)(ins))" + op + "*(" + cvt + "*)(ins+"
		+ off + ");\n}\n";
	return ret;
}
std::string var_op_var_func_template(std::string func_name, std::string cvt, std::string op, std::string off) {
	std::string ret = "void " + func_name + " (char *ins){\n"
		+ "\tmem.extract<" + cvt + ">(*(index_type*)(ins))" + op + " mem.extract<" + cvt + ">(*(index_type*)(ins+sizeof(index_type)" +
		+"));\n}\n";
	return ret;
}
int cnt = 0;
std::string gen_code() {
	using namespace std;
	std::string integer_bype_name[]{
		"char","int16_t","int32_t","int64_t","float","double","long double"
	};
	std::map<std::string, std::string> op_name_map{
		{ "ssub","-=" },{ "sadd","+=" },{ "smul","*=" },{ "sdiv","/=" }
	};
	std::map<std::string, InsTag> op_tag_map{
		{ "ssub",SSUB },{ "sadd",SADD },{ "smul",SMUL },{ "sdiv",SDIV }
	};
	std::string ret;
	for (auto a : op_name_map)
	{
		for (int i = 0; i < 4; i++)
		{
			int byte = pow(2, i);
			std::string func_name = "i" + std::to_string(byte * 8) + "_" + a.first;


			int index = i;
			index = index | 1 << 5;
			index = index | op_tag_map[a.first] << 8;

			map_content += "{" + to_string(index) + "," + func_name + "_vi},";
			cnt++;
			if (cnt % 3 == 0) { map_content += "\n\t"; }
			index = index | 1 << 6;
			map_content += "{" + to_string(index) + "," + func_name + "_vv},";
			cnt++;
			if (cnt % 3 == 0) { map_content += "\n\t"; }
			ret += func_template(func_name + "_vi", integer_bype_name[i], a.second, std::to_string(byte));
			ret += var_op_var_func_template(func_name + "_vv", integer_bype_name[i], a.second, std::to_string(byte));
		}
		for (int i = 4; i < 7; i++)
		{
			int byte = pow(2, i - 2);
			std::string func_name = "r" + std::to_string(byte * 8) + "_" + a.first;

			int index = i;
			index = index | 1 << 5;
			index = index | op_tag_map[a.first] << 8;
			map_content += "{" + to_string(index) + "," + func_name + "_vi},";
			cnt++;
			if (cnt % 3 == 0) { map_content += "\n\t"; }
			index = index | 1 << 6;
			map_content += "{" + to_string(index) + "," + func_name + "_vv},";
			cnt++;
			if (cnt % 3 == 0) { map_content += "\n\t"; }

			ret += func_template(func_name + "_vi", integer_bype_name[i], a.second, std::to_string(byte));
			ret += var_op_var_func_template(func_name + "_vv", integer_bype_name[i], a.second, std::to_string(byte));
		}
	}
	return ret;
}
int deactived_main() {
	std::cout << gen_code();
	map_content.back() = '\n';
	map_content += "};";
	std::cout << map_content;
	std::cin.get();
	return 0;
}