#include <iostream>
#include <map>
#include <string>
// I merely don't want to utilize strange lambda skills to simplify the code.
// So generate those functions by programs is a wise choice I reckon.
// exclude the file from the build
enum InsTag :char {
	SADD = 0x01, SSUB, SMUL, SDIV,
	ADD, SUB, MUL, DIV,
	EQ, NE, GT, GE, LE, LT,
	AND, OR, W8, W16, W32, W64, WR128,
	// write from cache
	WT8, WT16, WT32, WT64, WT128,
	// sub_ins 
	/*
	0-> common
	1-> Expr
	*/
	ASSIGN,
};
std::string map_content = "std::map<int16_t,instruction_type> _bin_operator_ins_table={";
//=========================s系列附带赋值的如+= ,-= 这种不允许第一个操作数是右值
std::string func_template(std::string func_name, std::string cvt, std::string op, std::string off) {
	std::string ret = "void " + func_name + " (char *ins){\n"
		+ "\tmem.extract<" + cvt + ">(*(index_type*)(ins))" + op + " *(" + cvt + "*)(ins+"
		+ off + ");\n}\n";
	return ret;
}
std::string var_op_var_func_template(std::string func_name, std::string cvt, std::string op, std::string off) {
	std::string ret = "void " + func_name + " (char *ins){\n"
		+ "\tmem.extract<" + cvt + ">(*(index_type*)(ins))" + op + " mem.extract<" + cvt + ">(*(index_type*)(ins+sizeof(index_type)" +
		+"));\n}\n";
	return ret;
}

// common 系列
std::string common_bin_op_func_temp_vi(std::string func_name, std::string cvt, std::string op, std::string off) {
	std::string ret = "void " + func_name + " (char *ins){\n"
		+ "\tmy_memcpy(intern_result_buf,mem.extract<" + cvt + ">(*(index_type*)(ins))" + op + " *(" + cvt + "*)(ins+"
		+ off + "));\n}\n";
	return ret;
}
std::string common_bin_op_func_temp_vv(std::string func_name, std::string cvt, std::string op, std::string off) {
	std::string ret = "void " + func_name + " (char *ins){\n"
		+ "\tmy_memcpy(intern_result_buf,mem.extract<" + cvt + ">(*(index_type*)(ins))" + op + " mem.extract<" + cvt + ">(*(index_type*)(ins+sizeof(index_type)" +
		+")));\n}\n";
	return ret;
}

std::string common_bin_op_func_temp_iv(std::string func_name, std::string cvt, std::string op, std::string off) {
	std::string ret = "void " + func_name + " (char *ins){\n"
		+ "\tmy_memcpy(intern_result_buf,*(" + cvt + "*)(ins)" + op + "mem.extract<" + cvt + ">(*(index_type*)(ins+"
		+ off + ")));\n}\n";

	return ret;
}

std::string common_bin_op_func_temp_ii(std::string func_name, std::string cvt, std::string op, std::string off) {
	std::string ret = "void " + func_name + " (char *ins){\n"
		+ "\tmy_memcpy(intern_result_buf,*(" + cvt + "*)(ins)" + op + " *(" + cvt + "*)(ins+"
		+ off + "));\n}\n";

	return ret;
}

int cnt = 0;
// sbinop
std::string gen_code() {
	using namespace std;
	std::string integer_bype_name[]{
		"char","int16_t","int32_t","int64_t","float","double","long double"
	};
	std::map<std::string, std::string> op_name_map{
		{ "ssub","-=" },{ "sadd","+=" },{ "smul","*=" },{ "sdiv","/=" },{ "assign","=" }
	};
	std::map<std::string, InsTag> op_tag_map{
		{ "ssub",SSUB },{ "sadd",SADD },{ "smul",SMUL },{ "sdiv",SDIV },{ "assign",ASSIGN }
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
			index = index | (int)op_tag_map[a.first] << 8;

			map_content += "{" + to_string(index) + "," + func_name + "_vi},";
			cnt++;
			if (cnt % 3 == 0) { map_content += "\n\t"; }
			index = index | 1 << 4;
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
// common binop
std::string gen_code2() {
	using namespace std;
	std::string integer_bype_name[]{
		"char","int16_t","int32_t","int64_t","float","double","long double"
	};
	std::map<std::string, std::string> op_name_map{
		{ "sub","-" },{ "add","+" },{ "mul","*" },{ "div","/" }
	};
	std::map<std::string, InsTag> op_tag_map{
		{ "sub",SUB },{ "add",ADD },{ "mul",MUL },{ "div",DIV }
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
			index = index | (int)op_tag_map[a.first] << 8;

			map_content += "{" + to_string(index) + "," + func_name + "_vi},";
			cnt++;
			if (cnt % 3 == 0) { map_content += "\n\t"; }
			index = index | 1 << 4;
			map_content += "{" + to_string(index) + "," + func_name + "_vv},";
			cnt++;
			if (cnt % 3 == 0) { map_content += "\n\t"; }
			ret += common_bin_op_func_temp_vi(func_name + "_vi", integer_bype_name[i], a.second, std::to_string(byte));
			ret += common_bin_op_func_temp_vv(func_name + "_vv", integer_bype_name[i], a.second, std::to_string(byte));
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

			ret += common_bin_op_func_temp_vi(func_name + "_vi", integer_bype_name[i], a.second, std::to_string(byte));
			ret += common_bin_op_func_temp_vv(func_name + "_vv", integer_bype_name[i], a.second, std::to_string(byte));
		}
	}
	return ret;
}
std::string gen_code3() {
	using namespace std;
	std::string integer_bype_name[]{
		"char","int16_t","int32_t","int64_t","float","double","long double"
	};
	std::map<std::string, std::string> op_name_map{
		{ "sub","-" },{ "add","+" },{ "mul","*" },{ "div","/" }
	};
	std::map<std::string, InsTag> op_tag_map{
		{ "sub",SUB },{ "add",ADD },{ "mul",MUL },{ "div",DIV }
	};
	std::string ret;
	for (auto a : op_name_map)
	{
		for (int i = 0; i < 4; i++)
		{
			int byte = pow(2, i);
			std::string func_name = "i" + std::to_string(byte * 8) + "_" + a.first;


			int16_t index = i;
			index = index | 1 << 4;
			index = index | (int)op_tag_map[a.first] << 8;

			map_content += "{" + to_string(index) + "," + func_name + "_iv},";
			cnt++;
			if (cnt % 3 == 0) { map_content += "\n\t"; }
			index &= 0xFF0F;
			map_content += "{" + to_string(index) + "," + func_name + "_ii},";
			cnt++;
			if (cnt % 3 == 0) { map_content += "\n\t"; }
			ret += common_bin_op_func_temp_iv(func_name + "_iv", integer_bype_name[i], a.second, std::to_string(byte));
			ret += common_bin_op_func_temp_ii(func_name + "_ii", integer_bype_name[i], a.second, std::to_string(byte));
		}
		for (int i = 4; i < 7; i++)
		{
			int byte = pow(2, i - 2);
			std::string func_name = "r" + std::to_string(byte * 8) + "_" + a.first;

			int16_t index = i;
			index = index | 1 << 4;
			index = index | (int)op_tag_map[a.first] << 8;

			map_content += "{" + to_string(index) + "," + func_name + "_iv},";
			cnt++;
			if (cnt % 3 == 0) { map_content += "\n\t"; }
			index &= 0xFF0F;
			map_content += "{" + to_string(index) + "," + func_name + "_ii},";
			cnt++;
			if (cnt % 3 == 0) { map_content += "\n\t"; }
			ret += common_bin_op_func_temp_iv(func_name + "_iv", integer_bype_name[i], a.second, std::to_string(byte));
			ret += common_bin_op_func_temp_ii(func_name + "_ii", integer_bype_name[i], a.second, std::to_string(byte));
		}
	}
	return ret;
}
int driver() {
	std::cout << gen_code();
	map_content.back() = '\n';
	map_content += "};";
	std::cout << map_content;
	std::cin.get();
	return 0;
}
template<typename _ty>
void my_memcpy(void* _dst, _ty src)
{
	memcpy(_dst, &src, sizeof(src));
}
int main() {
	driver();
	std::cin.get();
	return 0;
}