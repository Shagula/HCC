#include "../include/instructions.hpp"
#include "../include/translator.hpp"
#include "../include/memory.hpp"
namespace vm
{
	std::vector<std::pair<instruction_type, char*>> glo_instructions;
	int pc;
	void run()
	{
		while (pc < glo_instructions.size())
		{
			glo_instructions[pc].first(glo_instructions[pc].second);
			pc++;
		}
	}
	namespace write_ins {
		void write_8(char *ins) {
			mem.push(*ins);
		}
		void write_16(char * ins) {
			mem.push(*(int16_t*)ins);
		}
		void write_32(char *ins) {
			mem.push(*(int32_t*)ins);
		}
		void write_64(char *ins) {
			mem.push(*(int64_t*)ins);
		}
	}
	// the following code is gened by program 
	namespace {
		void i8_sadd_vi(char *ins) {
			mem.extract<char>(*(index_type*)(ins)) += *(char*)(ins + 1);
		}
		void i8_sadd_vv(char *ins) {
			mem.extract<char>(*(index_type*)(ins)) += mem.extract<char>(*(index_type*)(ins + sizeof(index_type)));
		}
		void i16_sadd_vi(char *ins) {
			mem.extract<int16_t>(*(index_type*)(ins)) += *(int16_t*)(ins + 2);
		}
		void i16_sadd_vv(char *ins) {
			mem.extract<int16_t>(*(index_type*)(ins)) += mem.extract<int16_t>(*(index_type*)(ins + sizeof(index_type)));
		}
		void i32_sadd_vi(char *ins) {

			mem.extract<int32_t>(*(index_type*)(ins)) += *(int32_t*)(ins + 4);
		}
		void i32_sadd_vv(char *ins) {
			mem.extract<int32_t>(*(index_type*)(ins)) += mem.extract<int32_t>(*(index_type*)(ins + sizeof(index_type)));
		}
		void i64_sadd_vi(char *ins) {
			mem.extract<int64_t>(*(index_type*)(ins)) += *(int64_t*)(ins + 8);
		}
		void i64_sadd_vv(char *ins) {
			mem.extract<int64_t>(*(index_type*)(ins)) += mem.extract<int64_t>(*(index_type*)(ins + sizeof(index_type)));
		}
		void r32_sadd_vi(char *ins) {
			mem.extract<float>(*(index_type*)(ins)) += *(float*)(ins + 4);
		}
		void r32_sadd_vv(char *ins) {
			mem.extract<float>(*(index_type*)(ins)) += mem.extract<float>(*(index_type*)(ins + sizeof(index_type)));
		}
		void r64_sadd_vi(char *ins) {
			mem.extract<double>(*(index_type*)(ins)) += *(double*)(ins + 8);
		}
		void r64_sadd_vv(char *ins) {
			mem.extract<double>(*(index_type*)(ins)) += mem.extract<double>(*(index_type*)(ins + sizeof(index_type)));
		}
		void r128_sadd_vi(char *ins) {
			mem.extract<long double>(*(index_type*)(ins)) += *(long double*)(ins + 16);
		}
		void r128_sadd_vv(char *ins) {
			mem.extract<long double>(*(index_type*)(ins)) += mem.extract<long double>(*(index_type*)(ins + sizeof(index_type)));
		}
		void i8_sdiv_vi(char *ins) {
			mem.extract<char>(*(index_type*)(ins)) /= *(char*)(ins + 1);
		}
		void i8_sdiv_vv(char *ins) {
			mem.extract<char>(*(index_type*)(ins)) /= mem.extract<char>(*(index_type*)(ins + sizeof(index_type)));
		}
		void i16_sdiv_vi(char *ins) {
			mem.extract<int16_t>(*(index_type*)(ins)) /= *(int16_t*)(ins + 2);
		}
		void i16_sdiv_vv(char *ins) {
			mem.extract<int16_t>(*(index_type*)(ins)) /= mem.extract<int16_t>(*(index_type*)(ins + sizeof(index_type)));
		}
		void i32_sdiv_vi(char *ins) {
			mem.extract<int32_t>(*(index_type*)(ins)) /= *(int32_t*)(ins + 4);
		}
		void i32_sdiv_vv(char *ins) {
			mem.extract<int32_t>(*(index_type*)(ins)) /= mem.extract<int32_t>(*(index_type*)(ins + sizeof(index_type)));
		}
		void i64_sdiv_vi(char *ins) {
			mem.extract<int64_t>(*(index_type*)(ins)) /= *(int64_t*)(ins + 8);
		}
		void i64_sdiv_vv(char *ins) {
			mem.extract<int64_t>(*(index_type*)(ins)) /= mem.extract<int64_t>(*(index_type*)(ins + sizeof(index_type)));
		}
		void r32_sdiv_vi(char *ins) {
			mem.extract<float>(*(index_type*)(ins)) /= *(float*)(ins + 4);
		}
		void r32_sdiv_vv(char *ins) {
			mem.extract<float>(*(index_type*)(ins)) /= mem.extract<float>(*(index_type*)(ins + sizeof(index_type)));
		}
		void r64_sdiv_vi(char *ins) {
			mem.extract<double>(*(index_type*)(ins)) /= *(double*)(ins + 8);
		}
		void r64_sdiv_vv(char *ins) {
			mem.extract<double>(*(index_type*)(ins)) /= mem.extract<double>(*(index_type*)(ins + sizeof(index_type)));
		}
		void r128_sdiv_vi(char *ins) {
			mem.extract<long double>(*(index_type*)(ins)) /= *(long double*)(ins + 16);
		}
		void r128_sdiv_vv(char *ins) {
			mem.extract<long double>(*(index_type*)(ins)) /= mem.extract<long double>(*(index_type*)(ins + sizeof(index_type)));
		}
		void i8_smul_vi(char *ins) {
			mem.extract<char>(*(index_type*)(ins)) *= *(char*)(ins + 1);
		}
		void i8_smul_vv(char *ins) {
			mem.extract<char>(*(index_type*)(ins)) *= mem.extract<char>(*(index_type*)(ins + sizeof(index_type)));
		}
		void i16_smul_vi(char *ins) {
			mem.extract<int16_t>(*(index_type*)(ins)) *= *(int16_t*)(ins + 2);
		}
		void i16_smul_vv(char *ins) {
			mem.extract<int16_t>(*(index_type*)(ins)) *= mem.extract<int16_t>(*(index_type*)(ins + sizeof(index_type)));
		}
		void i32_smul_vi(char *ins) {
			mem.extract<int32_t>(*(index_type*)(ins)) *= *(int32_t*)(ins + 4);
		}
		void i32_smul_vv(char *ins) {
			mem.extract<int32_t>(*(index_type*)(ins)) *= mem.extract<int32_t>(*(index_type*)(ins + sizeof(index_type)));
		}
		void i64_smul_vi(char *ins) {
			mem.extract<int64_t>(*(index_type*)(ins)) *= *(int64_t*)(ins + 8);
		}
		void i64_smul_vv(char *ins) {
			mem.extract<int64_t>(*(index_type*)(ins)) *= mem.extract<int64_t>(*(index_type*)(ins + sizeof(index_type)));
		}
		void r32_smul_vi(char *ins) {
			mem.extract<float>(*(index_type*)(ins)) *= *(float*)(ins + 4);
		}
		void r32_smul_vv(char *ins) {
			mem.extract<float>(*(index_type*)(ins)) *= mem.extract<float>(*(index_type*)(ins + sizeof(index_type)));
		}
		void r64_smul_vi(char *ins) {
			mem.extract<double>(*(index_type*)(ins)) *= *(double*)(ins + 8);
		}
		void r64_smul_vv(char *ins) {
			mem.extract<double>(*(index_type*)(ins)) *= mem.extract<double>(*(index_type*)(ins + sizeof(index_type)));
		}
		void r128_smul_vi(char *ins) {
			mem.extract<long double>(*(index_type*)(ins)) *= *(long double*)(ins + 16);
		}
		void r128_smul_vv(char *ins) {
			mem.extract<long double>(*(index_type*)(ins)) *= mem.extract<long double>(*(index_type*)(ins + sizeof(index_type)));
		}
		void i8_ssub_vi(char *ins) {
			mem.extract<char>(*(index_type*)(ins)) -= *(char*)(ins + 1);
		}
		void i8_ssub_vv(char *ins) {
			mem.extract<char>(*(index_type*)(ins)) -= mem.extract<char>(*(index_type*)(ins + sizeof(index_type)));
		}
		void i16_ssub_vi(char *ins) {
			mem.extract<int16_t>(*(index_type*)(ins)) -= *(int16_t*)(ins + 2);
		}
		void i16_ssub_vv(char *ins) {
			mem.extract<int16_t>(*(index_type*)(ins)) -= mem.extract<int16_t>(*(index_type*)(ins + sizeof(index_type)));
		}
		void i32_ssub_vi(char *ins) {
			mem.extract<int32_t>(*(index_type*)(ins)) -= *(int32_t*)(ins + 4);
		}
		void i32_ssub_vv(char *ins) {
			mem.extract<int32_t>(*(index_type*)(ins)) -= mem.extract<int32_t>(*(index_type*)(ins + sizeof(index_type)));
		}
		void i64_ssub_vi(char *ins) {
			mem.extract<int64_t>(*(index_type*)(ins)) -= *(int64_t*)(ins + 8);
		}
		void i64_ssub_vv(char *ins) {
			mem.extract<int64_t>(*(index_type*)(ins)) -= mem.extract<int64_t>(*(index_type*)(ins + sizeof(index_type)));
		}
		void r32_ssub_vi(char *ins) {
			mem.extract<float>(*(index_type*)(ins)) -= *(float*)(ins + 4);
		}
		void r32_ssub_vv(char *ins) {
			mem.extract<float>(*(index_type*)(ins)) -= mem.extract<float>(*(index_type*)(ins + sizeof(index_type)));
		}
		void r64_ssub_vi(char *ins) {
			mem.extract<double>(*(index_type*)(ins)) -= *(double*)(ins + 8);
		}
		void r64_ssub_vv(char *ins) {
			mem.extract<double>(*(index_type*)(ins)) -= mem.extract<double>(*(index_type*)(ins + sizeof(index_type)));
		}
		void r128_ssub_vi(char *ins) {
			mem.extract<long double>(*(index_type*)(ins)) -= *(long double*)(ins + 16);
		}
		void r128_ssub_vv(char *ins) {
			mem.extract<long double>(*(index_type*)(ins)) -= mem.extract<long double>(*(index_type*)(ins + sizeof(index_type)));
		}
		std::map<int16_t, instruction_type> _bin_operator_ins_table = { { 288,i8_sadd_vi },{ 304,i8_sadd_vv },{ 289,i16_sadd_vi },
			{ 305,i16_sadd_vv },{ 290,i32_sadd_vi },{ 306,i32_sadd_vv },
			{ 291,i64_sadd_vi },{ 307,i64_sadd_vv },{ 292,r32_sadd_vi },
			{ 356,r32_sadd_vv },{ 293,r64_sadd_vi },{ 357,r64_sadd_vv },
			{ 294,r128_sadd_vi },{ 358,r128_sadd_vv },{ 1056,i8_sdiv_vi },
			{ 1072,i8_sdiv_vv },{ 1057,i16_sdiv_vi },{ 1073,i16_sdiv_vv },
			{ 1058,i32_sdiv_vi },{ 1074,i32_sdiv_vv },{ 1059,i64_sdiv_vi },
			{ 1075,i64_sdiv_vv },{ 1060,r32_sdiv_vi },{ 1124,r32_sdiv_vv },
			{ 1061,r64_sdiv_vi },{ 1125,r64_sdiv_vv },{ 1062,r128_sdiv_vi },
			{ 1126,r128_sdiv_vv },{ 800,i8_smul_vi },{ 816,i8_smul_vv },
			{ 801,i16_smul_vi },{ 817,i16_smul_vv },{ 802,i32_smul_vi },
			{ 818,i32_smul_vv },{ 803,i64_smul_vi },{ 819,i64_smul_vv },
			{ 804,r32_smul_vi },{ 868,r32_smul_vv },{ 805,r64_smul_vi },
			{ 869,r64_smul_vv },{ 806,r128_smul_vi },{ 870,r128_smul_vv },
			{ 544,i8_ssub_vi },{ 560,i8_ssub_vv },{ 545,i16_ssub_vi },
			{ 561,i16_ssub_vv },{ 546,i32_ssub_vi },{ 562,i32_ssub_vv },
			{ 547,i64_ssub_vi },{ 563,i64_ssub_vv },{ 548,r32_ssub_vi },
			{ 612,r32_ssub_vv },{ 549,r64_ssub_vi },{ 613,r64_ssub_vv },
			{ 550,r128_ssub_vi },{ 614,r128_ssub_vv }
		};



	}
	instruction_type gen_bin_op(char _ty, char op)
	{   //|op  |mod|type|
		// vv->mod->11
		// vi->mod->10
		int16_t ins_index = (int16_t)(_ty) | (op << 8);
		if (_bin_operator_ins_table.find(ins_index) == _bin_operator_ins_table.end())
			throw Error("intern error!");
		return _bin_operator_ins_table[ins_index];
	}
}