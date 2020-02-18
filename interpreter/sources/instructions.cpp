#include "../include/instructions.hpp"
#include "../include/translator.hpp"
#include "../include/memory.hpp"
namespace vm
{
	//===================== def vars===============
	char intern_result_buf[20];
	std::vector<std::pair<instruction_type, char*>> glo_instructions;
	int pc;
	//=============================================
	void run()
	{
		while (pc < glo_instructions.size())
		{
			glo_instructions[pc].first(glo_instructions[pc].second);
			pc++;
		}
	}
	namespace write_ins {
		//write data from a position
		void write_p_8(char *ins) { mem.push(mem.extract<char>(*(index_type*)ins)); }
		void write_p_16(char *ins) { mem.push(mem.extract<int16_t>(*(index_type*)ins)); }
		void write_p_32(char *ins) { mem.push(mem.extract<int32_t>(*(index_type*)ins)); }
		void write_p_64(char *ins) { mem.push(mem.extract<int64_t>(*(index_type*)ins)); }
		// write imm data
		void write_8(char *ins) {
			mem.write(*ins,*(index_type*)(ins+1));
		}
		void write_16(char * ins) {
			mem.write(*(int16_t*)(ins), *(index_type*)(ins + 2));
		}
		void write_32(char *ins) {
			mem.write(*(int32_t*)ins, *(index_type*)(ins + 4));
		}
		void write_64(char *ins) {
			mem.write(*(int64_t*)ins, *(index_type*)(ins + 8));
		}
		// write from temp block
		void write_t_8(char *ins) {
			mem.write(*intern_result_buf,*(index_type*)ins);
		}
		void write_t_16(char * ins) {
			mem.write(*(int16_t*)intern_result_buf, *(index_type*)ins);
		}
		void write_t_32(char *ins) {
			mem.write(*(int32_t*)intern_result_buf, *(index_type*)ins);
		}
		void write_t_64(char *ins) {
			mem.write(*(int64_t*)intern_result_buf, *(index_type*)ins);
		}
	}
	// the following code is gened by program 
	template<typename _ty>
	void my_memcpy(void* _dst, _ty src)
	{
		memcpy(_dst, &src, sizeof(src));
	}
	// compare
	namespace {
		void i8_eq_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<char>(*(index_type*)(ins)) == *(char*)(ins + 1));
		}
		void i8_eq_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<char>(*(index_type*)(ins)) == mem.extract<char>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i16_eq_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int16_t>(*(index_type*)(ins)) == *(int16_t*)(ins + 2));
		}
		void i16_eq_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int16_t>(*(index_type*)(ins)) == mem.extract<int16_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i32_eq_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int32_t>(*(index_type*)(ins)) == *(int32_t*)(ins + 4));
		}
		void i32_eq_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int32_t>(*(index_type*)(ins)) == mem.extract<int32_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i64_eq_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int64_t>(*(index_type*)(ins)) == *(int64_t*)(ins + 8));
		}
		void i64_eq_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int64_t>(*(index_type*)(ins)) == mem.extract<int64_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r32_eq_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<float>(*(index_type*)(ins)) == *(float*)(ins + 4));
		}
		void r32_eq_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<float>(*(index_type*)(ins)) == mem.extract<float>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r64_eq_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<double>(*(index_type*)(ins)) == *(double*)(ins + 8));
		}
		void r64_eq_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<double>(*(index_type*)(ins)) == mem.extract<double>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r128_eq_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<long double>(*(index_type*)(ins)) == *(long double*)(ins + 16));
		}
		void r128_eq_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<long double>(*(index_type*)(ins)) == mem.extract<long double>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i8_ge_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<char>(*(index_type*)(ins)) >= *(char*)(ins + 1));
		}
		void i8_ge_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<char>(*(index_type*)(ins)) >= mem.extract<char>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i16_ge_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int16_t>(*(index_type*)(ins)) >= *(int16_t*)(ins + 2));
		}
		void i16_ge_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int16_t>(*(index_type*)(ins)) >= mem.extract<int16_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i32_ge_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int32_t>(*(index_type*)(ins)) >= *(int32_t*)(ins + 4));
		}
		void i32_ge_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int32_t>(*(index_type*)(ins)) >= mem.extract<int32_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i64_ge_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int64_t>(*(index_type*)(ins)) >= *(int64_t*)(ins + 8));
		}
		void i64_ge_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int64_t>(*(index_type*)(ins)) >= mem.extract<int64_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r32_ge_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<float>(*(index_type*)(ins)) >= *(float*)(ins + 4));
		}
		void r32_ge_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<float>(*(index_type*)(ins)) >= mem.extract<float>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r64_ge_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<double>(*(index_type*)(ins)) >= *(double*)(ins + 8));
		}
		void r64_ge_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<double>(*(index_type*)(ins)) >= mem.extract<double>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r128_ge_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<long double>(*(index_type*)(ins)) >= *(long double*)(ins + 16));
		}
		void r128_ge_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<long double>(*(index_type*)(ins)) >= mem.extract<long double>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i8_gt_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<char>(*(index_type*)(ins))> *(char*)(ins + 1));
		}
		void i8_gt_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<char>(*(index_type*)(ins))> mem.extract<char>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i16_gt_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int16_t>(*(index_type*)(ins))> *(int16_t*)(ins + 2));
		}
		void i16_gt_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int16_t>(*(index_type*)(ins))> mem.extract<int16_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i32_gt_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int32_t>(*(index_type*)(ins))> *(int32_t*)(ins + 4));
		}
		void i32_gt_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int32_t>(*(index_type*)(ins))> mem.extract<int32_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i64_gt_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int64_t>(*(index_type*)(ins))> *(int64_t*)(ins + 8));
		}
		void i64_gt_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int64_t>(*(index_type*)(ins))> mem.extract<int64_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r32_gt_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<float>(*(index_type*)(ins))> *(float*)(ins + 4));
		}
		void r32_gt_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<float>(*(index_type*)(ins))> mem.extract<float>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r64_gt_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<double>(*(index_type*)(ins))> *(double*)(ins + 8));
		}
		void r64_gt_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<double>(*(index_type*)(ins))> mem.extract<double>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r128_gt_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<long double>(*(index_type*)(ins))> *(long double*)(ins + 16));
		}
		void r128_gt_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<long double>(*(index_type*)(ins))> mem.extract<long double>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i8_le_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<char>(*(index_type*)(ins)) <= *(char*)(ins + 1));
		}
		void i8_le_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<char>(*(index_type*)(ins)) <= mem.extract<char>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i16_le_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int16_t>(*(index_type*)(ins)) <= *(int16_t*)(ins + 2));
		}
		void i16_le_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int16_t>(*(index_type*)(ins)) <= mem.extract<int16_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i32_le_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int32_t>(*(index_type*)(ins)) <= *(int32_t*)(ins + 4));
		}
		void i32_le_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int32_t>(*(index_type*)(ins)) <= mem.extract<int32_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i64_le_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int64_t>(*(index_type*)(ins)) <= *(int64_t*)(ins + 8));
		}
		void i64_le_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int64_t>(*(index_type*)(ins)) <= mem.extract<int64_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r32_le_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<float>(*(index_type*)(ins)) <= *(float*)(ins + 4));
		}
		void r32_le_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<float>(*(index_type*)(ins)) <= mem.extract<float>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r64_le_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<double>(*(index_type*)(ins)) <= *(double*)(ins + 8));
		}
		void r64_le_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<double>(*(index_type*)(ins)) <= mem.extract<double>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r128_le_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<long double>(*(index_type*)(ins)) <= *(long double*)(ins + 16));
		}
		void r128_le_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<long double>(*(index_type*)(ins)) <= mem.extract<long double>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i8_lt_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<char>(*(index_type*)(ins))< *(char*)(ins + 1));
		}
		void i8_lt_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<char>(*(index_type*)(ins))< mem.extract<char>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i16_lt_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int16_t>(*(index_type*)(ins))< *(int16_t*)(ins + 2));
		}
		void i16_lt_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int16_t>(*(index_type*)(ins))< mem.extract<int16_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i32_lt_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int32_t>(*(index_type*)(ins))< *(int32_t*)(ins + sizeof(index_type)));
		}
		void i32_lt_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int32_t>(*(index_type*)(ins))< mem.extract<int32_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i64_lt_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int64_t>(*(index_type*)(ins))< *(int64_t*)(ins + 8));
		}
		void i64_lt_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int64_t>(*(index_type*)(ins))< mem.extract<int64_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r32_lt_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<float>(*(index_type*)(ins))< *(float*)(ins + 4));
		}
		void r32_lt_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<float>(*(index_type*)(ins))< mem.extract<float>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r64_lt_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<double>(*(index_type*)(ins))< *(double*)(ins + 8));
		}
		void r64_lt_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<double>(*(index_type*)(ins))< mem.extract<double>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r128_lt_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<long double>(*(index_type*)(ins))< *(long double*)(ins + 16));
		}
		void r128_lt_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<long double>(*(index_type*)(ins))< mem.extract<long double>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i8_ne_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<char>(*(index_type*)(ins)) != *(char*)(ins + 1));
		}
		void i8_ne_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<char>(*(index_type*)(ins)) != mem.extract<char>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i16_ne_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int16_t>(*(index_type*)(ins)) != *(int16_t*)(ins + 2));
		}
		void i16_ne_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int16_t>(*(index_type*)(ins)) != mem.extract<int16_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i32_ne_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int32_t>(*(index_type*)(ins)) != *(int32_t*)(ins + 4));
		}
		void i32_ne_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int32_t>(*(index_type*)(ins)) != mem.extract<int32_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i64_ne_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int64_t>(*(index_type*)(ins)) != *(int64_t*)(ins + 8));
		}
		void i64_ne_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int64_t>(*(index_type*)(ins)) != mem.extract<int64_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r32_ne_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<float>(*(index_type*)(ins)) != *(float*)(ins + 4));
		}
		void r32_ne_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<float>(*(index_type*)(ins)) != mem.extract<float>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r64_ne_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<double>(*(index_type*)(ins)) != *(double*)(ins + 8));
		}
		void r64_ne_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<double>(*(index_type*)(ins)) != mem.extract<double>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r128_ne_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<long double>(*(index_type*)(ins)) != *(long double*)(ins + 16));
		}
		void r128_ne_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<long double>(*(index_type*)(ins)) != mem.extract<long double>(*(index_type*)(ins + sizeof(index_type))));
		}

		void i8_eq_iv(char *ins) {
			my_memcpy(intern_result_buf, *(char*)(ins) == mem.extract<char>(*(index_type*)(ins + 1)));
		}
		void i8_eq_ii(char *ins) {
			my_memcpy(intern_result_buf, *(char*)(ins) == *(char*)(ins + 1));
		}
		void i16_eq_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int16_t*)(ins) == mem.extract<int16_t>(*(index_type*)(ins + 2)));
		}
		void i16_eq_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int16_t*)(ins) == *(int16_t*)(ins + 2));
		}
		void i32_eq_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int32_t*)(ins) == mem.extract<int32_t>(*(index_type*)(ins + 4)));
		}
		void i32_eq_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int32_t*)(ins) == *(int32_t*)(ins + 4));
		}
		void i64_eq_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int64_t*)(ins) == mem.extract<int64_t>(*(index_type*)(ins + 8)));
		}
		void i64_eq_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int64_t*)(ins) == *(int64_t*)(ins + 8));
		}
		void r32_eq_iv(char *ins) {
			my_memcpy(intern_result_buf, *(float*)(ins) == mem.extract<float>(*(index_type*)(ins + 4)));
		}
		void r32_eq_ii(char *ins) {
			my_memcpy(intern_result_buf, *(float*)(ins) == *(float*)(ins + 4));
		}
		void r64_eq_iv(char *ins) {
			my_memcpy(intern_result_buf, *(double*)(ins) == mem.extract<double>(*(index_type*)(ins + 8)));
		}
		void r64_eq_ii(char *ins) {
			my_memcpy(intern_result_buf, *(double*)(ins) == *(double*)(ins + 8));
		}
		void r128_eq_iv(char *ins) {
			my_memcpy(intern_result_buf, *(long double*)(ins) == mem.extract<long double>(*(index_type*)(ins + 16)));
		}
		void r128_eq_ii(char *ins) {
			my_memcpy(intern_result_buf, *(long double*)(ins) == *(long double*)(ins + 16));
		}
		void i8_ge_iv(char *ins) {
			my_memcpy(intern_result_buf, *(char*)(ins) >= mem.extract<char>(*(index_type*)(ins + 1)));
		}
		void i8_ge_ii(char *ins) {
			my_memcpy(intern_result_buf, *(char*)(ins) >= *(char*)(ins + 1));
		}
		void i16_ge_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int16_t*)(ins) >= mem.extract<int16_t>(*(index_type*)(ins + 2)));
		}
		void i16_ge_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int16_t*)(ins) >= *(int16_t*)(ins + 2));
		}
		void i32_ge_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int32_t*)(ins) >= mem.extract<int32_t>(*(index_type*)(ins + 4)));
		}
		void i32_ge_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int32_t*)(ins) >= *(int32_t*)(ins + 4));
		}
		void i64_ge_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int64_t*)(ins) >= mem.extract<int64_t>(*(index_type*)(ins + 8)));
		}
		void i64_ge_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int64_t*)(ins) >= *(int64_t*)(ins + 8));
		}
		void r32_ge_iv(char *ins) {
			my_memcpy(intern_result_buf, *(float*)(ins) >= mem.extract<float>(*(index_type*)(ins + 4)));
		}
		void r32_ge_ii(char *ins) {
			my_memcpy(intern_result_buf, *(float*)(ins) >= *(float*)(ins + 4));
		}
		void r64_ge_iv(char *ins) {
			my_memcpy(intern_result_buf, *(double*)(ins) >= mem.extract<double>(*(index_type*)(ins + 8)));
		}
		void r64_ge_ii(char *ins) {
			my_memcpy(intern_result_buf, *(double*)(ins) >= *(double*)(ins + 8));
		}
		void r128_ge_iv(char *ins) {
			my_memcpy(intern_result_buf, *(long double*)(ins) >= mem.extract<long double>(*(index_type*)(ins + 16)));
		}
		void r128_ge_ii(char *ins) {
			my_memcpy(intern_result_buf, *(long double*)(ins) >= *(long double*)(ins + 16));
		}
		void i8_gt_iv(char *ins) {
			my_memcpy(intern_result_buf, *(char*)(ins) > mem.extract<char>(*(index_type*)(ins + 1)));
		}
		void i8_gt_ii(char *ins) {
			my_memcpy(intern_result_buf, *(char*)(ins) > *(char*)(ins + 1));
		}
		void i16_gt_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int16_t*)(ins) > mem.extract<int16_t>(*(index_type*)(ins + 2)));
		}
		void i16_gt_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int16_t*)(ins) > *(int16_t*)(ins + 2));
		}
		void i32_gt_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int32_t*)(ins) > mem.extract<int32_t>(*(index_type*)(ins + 4)));
		}
		void i32_gt_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int32_t*)(ins) > *(int32_t*)(ins + 4));
		}
		void i64_gt_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int64_t*)(ins) > mem.extract<int64_t>(*(index_type*)(ins + 8)));
		}
		void i64_gt_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int64_t*)(ins) > *(int64_t*)(ins + 8));
		}
		void r32_gt_iv(char *ins) {
			my_memcpy(intern_result_buf, *(float*)(ins) > mem.extract<float>(*(index_type*)(ins + 4)));
		}
		void r32_gt_ii(char *ins) {
			my_memcpy(intern_result_buf, *(float*)(ins) > *(float*)(ins + 4));
		}
		void r64_gt_iv(char *ins) {
			my_memcpy(intern_result_buf, *(double*)(ins) > mem.extract<double>(*(index_type*)(ins + 8)));
		}
		void r64_gt_ii(char *ins) {
			my_memcpy(intern_result_buf, *(double*)(ins) > *(double*)(ins + 8));
		}
		void r128_gt_iv(char *ins) {
			my_memcpy(intern_result_buf, *(long double*)(ins) > mem.extract<long double>(*(index_type*)(ins + 16)));
		}
		void r128_gt_ii(char *ins) {
			my_memcpy(intern_result_buf, *(long double*)(ins) > *(long double*)(ins + 16));
		}
		void i8_le_iv(char *ins) {
			my_memcpy(intern_result_buf, *(char*)(ins) <= mem.extract<char>(*(index_type*)(ins + 1)));
		}
		void i8_le_ii(char *ins) {
			my_memcpy(intern_result_buf, *(char*)(ins) <= *(char*)(ins + 1));
		}
		void i16_le_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int16_t*)(ins) <= mem.extract<int16_t>(*(index_type*)(ins + 2)));
		}
		void i16_le_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int16_t*)(ins) <= *(int16_t*)(ins + 2));
		}
		void i32_le_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int32_t*)(ins) <= mem.extract<int32_t>(*(index_type*)(ins + 4)));
		}
		void i32_le_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int32_t*)(ins) <= *(int32_t*)(ins + 4));
		}
		void i64_le_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int64_t*)(ins) <= mem.extract<int64_t>(*(index_type*)(ins + 8)));
		}
		void i64_le_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int64_t*)(ins) <= *(int64_t*)(ins + 8));
		}
		void r32_le_iv(char *ins) {
			my_memcpy(intern_result_buf, *(float*)(ins) <= mem.extract<float>(*(index_type*)(ins + 4)));
		}
		void r32_le_ii(char *ins) {
			my_memcpy(intern_result_buf, *(float*)(ins) <= *(float*)(ins + 4));
		}
		void r64_le_iv(char *ins) {
			my_memcpy(intern_result_buf, *(double*)(ins) <= mem.extract<double>(*(index_type*)(ins + 8)));
		}
		void r64_le_ii(char *ins) {
			my_memcpy(intern_result_buf, *(double*)(ins) <= *(double*)(ins + 8));
		}
		void r128_le_iv(char *ins) {
			my_memcpy(intern_result_buf, *(long double*)(ins) <= mem.extract<long double>(*(index_type*)(ins + 16)));
		}
		void r128_le_ii(char *ins) {
			my_memcpy(intern_result_buf, *(long double*)(ins) <= *(long double*)(ins + 16));
		}
		void i8_lt_iv(char *ins) {
			my_memcpy(intern_result_buf, *(char*)(ins) < mem.extract<char>(*(index_type*)(ins + 1)));
		}
		void i8_lt_ii(char *ins) {
			my_memcpy(intern_result_buf, *(char*)(ins) < *(char*)(ins + 1));
		}
		void i16_lt_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int16_t*)(ins) < mem.extract<int16_t>(*(index_type*)(ins + 2)));
		}
		void i16_lt_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int16_t*)(ins) < *(int16_t*)(ins + 2));
		}
		void i32_lt_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int32_t*)(ins) < mem.extract<int32_t>(*(index_type*)(ins + 4)));
		}
		void i32_lt_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int32_t*)(ins) < *(int32_t*)(ins + 4));
		}
		void i64_lt_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int64_t*)(ins) < mem.extract<int64_t>(*(index_type*)(ins + 8)));
		}
		void i64_lt_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int64_t*)(ins) < *(int64_t*)(ins + 8));
		}
		void r32_lt_iv(char *ins) {
			my_memcpy(intern_result_buf, *(float*)(ins) < mem.extract<float>(*(index_type*)(ins + 4)));
		}
		void r32_lt_ii(char *ins) {
			my_memcpy(intern_result_buf, *(float*)(ins) < *(float*)(ins + 4));
		}
		void r64_lt_iv(char *ins) {
			my_memcpy(intern_result_buf, *(double*)(ins) < mem.extract<double>(*(index_type*)(ins + 8)));
		}
		void r64_lt_ii(char *ins) {
			my_memcpy(intern_result_buf, *(double*)(ins) < *(double*)(ins + 8));
		}
		void r128_lt_iv(char *ins) {
			my_memcpy(intern_result_buf, *(long double*)(ins) < mem.extract<long double>(*(index_type*)(ins + 16)));
		}
		void r128_lt_ii(char *ins) {
			my_memcpy(intern_result_buf, *(long double*)(ins) < *(long double*)(ins + 16));
		}
		void i8_ne_iv(char *ins) {
			my_memcpy(intern_result_buf, *(char*)(ins) != mem.extract<char>(*(index_type*)(ins + 1)));
		}
		void i8_ne_ii(char *ins) {
			my_memcpy(intern_result_buf, *(char*)(ins) != *(char*)(ins + 1));
		}
		void i16_ne_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int16_t*)(ins) != mem.extract<int16_t>(*(index_type*)(ins + 2)));
		}
		void i16_ne_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int16_t*)(ins) != *(int16_t*)(ins + 2));
		}
		void i32_ne_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int32_t*)(ins) != mem.extract<int32_t>(*(index_type*)(ins + 4)));
		}
		void i32_ne_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int32_t*)(ins) != *(int32_t*)(ins + 4));
		}
		void i64_ne_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int64_t*)(ins) != mem.extract<int64_t>(*(index_type*)(ins + 8)));
		}
		void i64_ne_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int64_t*)(ins) != *(int64_t*)(ins + 8));
		}
		void r32_ne_iv(char *ins) {
			my_memcpy(intern_result_buf, *(float*)(ins) != mem.extract<float>(*(index_type*)(ins + 4)));
		}
		void r32_ne_ii(char *ins) {
			my_memcpy(intern_result_buf, *(float*)(ins) != *(float*)(ins + 4));
		}
		void r64_ne_iv(char *ins) {
			my_memcpy(intern_result_buf, *(double*)(ins) != mem.extract<double>(*(index_type*)(ins + 8)));
		}
		void r64_ne_ii(char *ins) {
			my_memcpy(intern_result_buf, *(double*)(ins) != *(double*)(ins + 8));
		}
		void r128_ne_iv(char *ins) {
			my_memcpy(intern_result_buf, *(long double*)(ins) != mem.extract<long double>(*(index_type*)(ins + 16)));
		}
		void r128_ne_ii(char *ins) {
			my_memcpy(intern_result_buf, *(long double*)(ins) != *(long double*)(ins + 16));
		}
	}
	// variable convert
	namespace {
		void i8_to_i16(char *ins) {
			my_memcpy(intern_result_buf, (int16_t)mem.extract<char>(*(index_type*)(ins)));
		}
		void i8_to_i32(char *ins) {
			my_memcpy(intern_result_buf, (int32_t)mem.extract<char>(*(index_type*)(ins)));
		}
		void i8_to_i64(char *ins) {
			my_memcpy(intern_result_buf, (int64_t)mem.extract<char>(*(index_type*)(ins)));
		}
		void i8_to_r32(char *ins) {
			my_memcpy(intern_result_buf, (float)mem.extract<char>(*(index_type*)(ins)));
		}
		void i8_to_r64(char *ins) {
			my_memcpy(intern_result_buf, (double)mem.extract<char>(*(index_type*)(ins)));
		}
		void i8_to_r128(char *ins) {
			my_memcpy(intern_result_buf, (long double)mem.extract<char>(*(index_type*)(ins)));
		}
		void i16_to_i8(char *ins) {
			my_memcpy(intern_result_buf, (char)mem.extract<int16_t>(*(index_type*)(ins)));
		}
		void i16_to_i32(char *ins) {
			my_memcpy(intern_result_buf, (int32_t)mem.extract<int16_t>(*(index_type*)(ins)));
		}
		void i16_to_i64(char *ins) {
			my_memcpy(intern_result_buf, (int64_t)mem.extract<int16_t>(*(index_type*)(ins)));
		}
		void i16_to_r32(char *ins) {
			my_memcpy(intern_result_buf, (float)mem.extract<int16_t>(*(index_type*)(ins)));
		}
		void i16_to_r64(char *ins) {
			my_memcpy(intern_result_buf, (double)mem.extract<int16_t>(*(index_type*)(ins)));
		}
		void i16_to_r128(char *ins) {
			my_memcpy(intern_result_buf, (long double)mem.extract<int16_t>(*(index_type*)(ins)));
		}
		void i32_to_i8(char *ins) {
			my_memcpy(intern_result_buf, (char)mem.extract<int32_t>(*(index_type*)(ins)));
		}
		void i32_to_i16(char *ins) {
			my_memcpy(intern_result_buf, (int16_t)mem.extract<int32_t>(*(index_type*)(ins)));
		}
		void i32_to_i64(char *ins) {
			my_memcpy(intern_result_buf, (int64_t)mem.extract<int32_t>(*(index_type*)(ins)));
		}
		void i32_to_r32(char *ins) {
			my_memcpy(intern_result_buf, (float)mem.extract<int32_t>(*(index_type*)(ins)));
		}
		void i32_to_r64(char *ins) {
			my_memcpy(intern_result_buf, (double)mem.extract<int32_t>(*(index_type*)(ins)));
		}
		void i32_to_r128(char *ins) {
			my_memcpy(intern_result_buf, (long double)mem.extract<int32_t>(*(index_type*)(ins)));
		}
		void i64_to_i8(char *ins) {
			my_memcpy(intern_result_buf, (char)mem.extract<int64_t>(*(index_type*)(ins)));
		}
		void i64_to_i16(char *ins) {
			my_memcpy(intern_result_buf, (int16_t)mem.extract<int64_t>(*(index_type*)(ins)));
		}
		void i64_to_i32(char *ins) {
			my_memcpy(intern_result_buf, (int32_t)mem.extract<int64_t>(*(index_type*)(ins)));
		}
		void i64_to_r32(char *ins) {
			my_memcpy(intern_result_buf, (float)mem.extract<int64_t>(*(index_type*)(ins)));
		}
		void i64_to_r64(char *ins) {
			my_memcpy(intern_result_buf, (double)mem.extract<int64_t>(*(index_type*)(ins)));
		}
		void i64_to_r128(char *ins) {
			my_memcpy(intern_result_buf, (long double)mem.extract<int64_t>(*(index_type*)(ins)));
		}
		void r32_to_i8(char *ins) {
			my_memcpy(intern_result_buf, (char)mem.extract<float>(*(index_type*)(ins)));
		}
		void r32_to_i16(char *ins) {
			my_memcpy(intern_result_buf, (int16_t)mem.extract<float>(*(index_type*)(ins)));
		}
		void r32_to_i32(char *ins) {
			my_memcpy(intern_result_buf, (int32_t)mem.extract<float>(*(index_type*)(ins)));
		}
		void r32_to_i64(char *ins) {
			my_memcpy(intern_result_buf, (int64_t)mem.extract<float>(*(index_type*)(ins)));
		}
		void r32_to_r64(char *ins) {
			my_memcpy(intern_result_buf, (double)mem.extract<float>(*(index_type*)(ins)));
		}
		void r32_to_r128(char *ins) {
			my_memcpy(intern_result_buf, (long double)mem.extract<float>(*(index_type*)(ins)));
		}
		void r64_to_i8(char *ins) {
			my_memcpy(intern_result_buf, (char)mem.extract<double>(*(index_type*)(ins)));
		}
		void r64_to_i16(char *ins) {
			my_memcpy(intern_result_buf, (int16_t)mem.extract<double>(*(index_type*)(ins)));
		}
		void r64_to_i32(char *ins) {
			my_memcpy(intern_result_buf, (int32_t)mem.extract<double>(*(index_type*)(ins)));
		}
		void r64_to_i64(char *ins) {
			my_memcpy(intern_result_buf, (int64_t)mem.extract<double>(*(index_type*)(ins)));
		}
		void r64_to_r32(char *ins) {
			my_memcpy(intern_result_buf, (float)mem.extract<double>(*(index_type*)(ins)));
		}
		void r64_to_r128(char *ins) {
			my_memcpy(intern_result_buf, (long double)mem.extract<double>(*(index_type*)(ins)));
		}
		void r128_to_i8(char *ins) {
			my_memcpy(intern_result_buf, (char)mem.extract<long double>(*(index_type*)(ins)));
		}
		void r128_to_i16(char *ins) {
			my_memcpy(intern_result_buf, (int16_t)mem.extract<long double>(*(index_type*)(ins)));
		}
		void r128_to_i32(char *ins) {
			my_memcpy(intern_result_buf, (int32_t)mem.extract<long double>(*(index_type*)(ins)));
		}
		void r128_to_i64(char *ins) {
			my_memcpy(intern_result_buf, (int64_t)mem.extract<long double>(*(index_type*)(ins)));
		}
		void r128_to_r32(char *ins) {
			my_memcpy(intern_result_buf, (float)mem.extract<long double>(*(index_type*)(ins)));
		}
		void r128_to_r64(char *ins) {
			my_memcpy(intern_result_buf, (double)mem.extract<long double>(*(index_type*)(ins)));
		}
		std::map<int16_t, instruction_type> _conv_operator_ins_table = {
			{ 0, write_ins::write_p_8},{34,write_ins::write_p_32},
			{ 1,i8_to_i16 },{ 2,i8_to_i32 },
			{ 3,i8_to_i64 },{ 4,i8_to_r32 },{ 5,i8_to_r64 },
			{ 6,i8_to_r128 },{ 16,i16_to_i8 },{ 18,i16_to_i32 },
			{ 19,i16_to_i64 },{ 20,i16_to_r32 },{ 21,i16_to_r64 },
			{ 22,i16_to_r128 },{ 32,i32_to_i8 },{ 33,i32_to_i16 },
			{ 35,i32_to_i64 },{ 36,i32_to_r32 },{ 37,i32_to_r64 },
			{ 38,i32_to_r128 },{ 48,i64_to_i8 },{ 49,i64_to_i16 },
			{ 50,i64_to_i32 },{ 52,i64_to_r32 },{ 53,i64_to_r64 },
			{ 54,i64_to_r128 },{ 64,r32_to_i8 },{ 65,r32_to_i16 },
			{ 66,r32_to_i32 },{ 67,r32_to_i64 },{ 69,r32_to_r64 },
			{ 70,r32_to_r128 },{ 80,r64_to_i8 },{ 81,r64_to_i16 },
			{ 82,r64_to_i32 },{ 83,r64_to_i64 },{ 84,r64_to_r32 },
			{ 86,r64_to_r128 },{ 96,r128_to_i8 },{ 97,r128_to_i16 },
			{ 98,r128_to_i32 },{ 99,r128_to_i64 },{ 100,r128_to_r32 },
			{ 101,r128_to_r64 }
		};
	}
	// + ,- ,*,/
	namespace {
		void i8_add_iv(char *ins) {
			my_memcpy(intern_result_buf, *(char*)(ins)+mem.extract<char>(*(index_type*)(ins + 1)));
		}
		void i8_add_ii(char *ins) {
			my_memcpy(intern_result_buf, *(char*)(ins)+*(char*)(ins + 1));
		}
		void i16_add_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int16_t*)(ins)+mem.extract<int16_t>(*(index_type*)(ins + 2)));
		}
		void i16_add_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int16_t*)(ins)+*(int16_t*)(ins + 2));
		}
		void i32_add_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int32_t*)(ins)+mem.extract<int32_t>(*(index_type*)(ins + 4)));
		}
		void i32_add_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int32_t*)(ins)+*(int32_t*)(ins + 4));
		}
		void i64_add_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int64_t*)(ins)+mem.extract<int64_t>(*(index_type*)(ins + 8)));
		}
		void i64_add_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int64_t*)(ins)+*(int64_t*)(ins + 8));
		}
		void r32_add_iv(char *ins) {
			my_memcpy(intern_result_buf, *(float*)(ins)+mem.extract<float>(*(index_type*)(ins + 4)));
		}
		void r32_add_ii(char *ins) {
			my_memcpy(intern_result_buf, *(float*)(ins)+*(float*)(ins + 4));
		}
		void r64_add_iv(char *ins) {
			my_memcpy(intern_result_buf, *(double*)(ins)+mem.extract<double>(*(index_type*)(ins + 8)));
		}
		void r64_add_ii(char *ins) {
			my_memcpy(intern_result_buf, *(double*)(ins)+*(double*)(ins + 8));
		}
		void r128_add_iv(char *ins) {
			my_memcpy(intern_result_buf, *(long double*)(ins)+mem.extract<long double>(*(index_type*)(ins + 16)));
		}
		void r128_add_ii(char *ins) {
			my_memcpy(intern_result_buf, *(long double*)(ins)+*(long double*)(ins + 16));
		}
		void i8_div_iv(char *ins) {
			my_memcpy(intern_result_buf, *(char*)(ins) / mem.extract<char>(*(index_type*)(ins + 1)));
		}
		void i8_div_ii(char *ins) {
			my_memcpy(intern_result_buf, *(char*)(ins) / *(char*)(ins + 1));
		}
		void i16_div_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int16_t*)(ins) / mem.extract<int16_t>(*(index_type*)(ins + 2)));
		}
		void i16_div_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int16_t*)(ins) / *(int16_t*)(ins + 2));
		}
		void i32_div_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int32_t*)(ins) / mem.extract<int32_t>(*(index_type*)(ins + 4)));
		}
		void i32_div_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int32_t*)(ins) / *(int32_t*)(ins + 4));
		}
		void i64_div_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int64_t*)(ins) / mem.extract<int64_t>(*(index_type*)(ins + 8)));
		}
		void i64_div_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int64_t*)(ins) / *(int64_t*)(ins + 8));
		}
		void r32_div_iv(char *ins) {
			my_memcpy(intern_result_buf, *(float*)(ins) / mem.extract<float>(*(index_type*)(ins + 4)));
		}
		void r32_div_ii(char *ins) {
			my_memcpy(intern_result_buf, *(float*)(ins) / *(float*)(ins + 4));
		}
		void r64_div_iv(char *ins) {
			my_memcpy(intern_result_buf, *(double*)(ins) / mem.extract<double>(*(index_type*)(ins + 8)));
		}
		void r64_div_ii(char *ins) {
			my_memcpy(intern_result_buf, *(double*)(ins) / *(double*)(ins + 8));
		}
		void r128_div_iv(char *ins) {
			my_memcpy(intern_result_buf, *(long double*)(ins) / mem.extract<long double>(*(index_type*)(ins + 16)));
		}
		void r128_div_ii(char *ins) {
			my_memcpy(intern_result_buf, *(long double*)(ins) / *(long double*)(ins + 16));
		}
		void i8_mul_iv(char *ins) {
			my_memcpy(intern_result_buf, *(char*)(ins)*mem.extract<char>(*(index_type*)(ins + 1)));
		}
		void i8_mul_ii(char *ins) {
			my_memcpy(intern_result_buf, *(char*)(ins)* *(char*)(ins + 1));
		}
		void i16_mul_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int16_t*)(ins)*mem.extract<int16_t>(*(index_type*)(ins + 2)));
		}
		void i16_mul_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int16_t*)(ins)* *(int16_t*)(ins + 2));
		}
		void i32_mul_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int32_t*)(ins)*mem.extract<int32_t>(*(index_type*)(ins + 4)));
		}
		void i32_mul_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int32_t*)(ins)* *(int32_t*)(ins + 4));
		}
		void i64_mul_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int64_t*)(ins)*mem.extract<int64_t>(*(index_type*)(ins + 8)));
		}
		void i64_mul_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int64_t*)(ins)* *(int64_t*)(ins + 8));
		}
		void r32_mul_iv(char *ins) {
			my_memcpy(intern_result_buf, *(float*)(ins)*mem.extract<float>(*(index_type*)(ins + 4)));
		}
		void r32_mul_ii(char *ins) {
			my_memcpy(intern_result_buf, *(float*)(ins)* *(float*)(ins + 4));
		}
		void r64_mul_iv(char *ins) {
			my_memcpy(intern_result_buf, *(double*)(ins)*mem.extract<double>(*(index_type*)(ins + 8)));
		}
		void r64_mul_ii(char *ins) {
			my_memcpy(intern_result_buf, *(double*)(ins)* *(double*)(ins + 8));
		}
		void r128_mul_iv(char *ins) {
			my_memcpy(intern_result_buf, *(long double*)(ins)*mem.extract<long double>(*(index_type*)(ins + 16)));
		}
		void r128_mul_ii(char *ins) {
			my_memcpy(intern_result_buf, *(long double*)(ins)* *(long double*)(ins + 16));
		}
		void i8_sub_iv(char *ins) {
			my_memcpy(intern_result_buf, *(char*)(ins)-mem.extract<char>(*(index_type*)(ins + 1)));
		}
		void i8_sub_ii(char *ins) {
			my_memcpy(intern_result_buf, *(char*)(ins)-*(char*)(ins + 1));
		}
		void i16_sub_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int16_t*)(ins)-mem.extract<int16_t>(*(index_type*)(ins + 2)));
		}
		void i16_sub_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int16_t*)(ins)-*(int16_t*)(ins + 2));
		}
		void i32_sub_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int32_t*)(ins)-mem.extract<int32_t>(*(index_type*)(ins + 4)));
		}
		void i32_sub_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int32_t*)(ins)-*(int32_t*)(ins + 4));
		}
		void i64_sub_iv(char *ins) {
			my_memcpy(intern_result_buf, *(int64_t*)(ins)-mem.extract<int64_t>(*(index_type*)(ins + 8)));
		}
		void i64_sub_ii(char *ins) {
			my_memcpy(intern_result_buf, *(int64_t*)(ins)-*(int64_t*)(ins + 8));
		}
		void r32_sub_iv(char *ins) {
			my_memcpy(intern_result_buf, *(float*)(ins)-mem.extract<float>(*(index_type*)(ins + 4)));
		}
		void r32_sub_ii(char *ins) {
			my_memcpy(intern_result_buf, *(float*)(ins)-*(float*)(ins + 4));
		}
		void r64_sub_iv(char *ins) {
			my_memcpy(intern_result_buf, *(double*)(ins)-mem.extract<double>(*(index_type*)(ins + 8)));
		}
		void r64_sub_ii(char *ins) {
			my_memcpy(intern_result_buf, *(double*)(ins)-*(double*)(ins + 8));
		}
		void r128_sub_iv(char *ins) {
			my_memcpy(intern_result_buf, *(long double*)(ins)-mem.extract<long double>(*(index_type*)(ins + 16)));
		}
		void r128_sub_ii(char *ins) {
			my_memcpy(intern_result_buf, *(long double*)(ins)-*(long double*)(ins + 16));
		}
		//================
		void i8_add_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<char>(*(index_type*)(ins)) + *(char*)(ins + 1));
		}
		void i8_add_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<char>(*(index_type*)(ins)) + mem.extract<char>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i16_add_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int16_t>(*(index_type*)(ins)) + *(int16_t*)(ins + 2));
		}
		void i16_add_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int16_t>(*(index_type*)(ins)) + mem.extract<int16_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i32_add_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int32_t>(*(index_type*)(ins)) + *(int32_t*)(ins + 4));
		}
		void i32_add_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int32_t>(*(index_type*)(ins)) + mem.extract<int32_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i64_add_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int64_t>(*(index_type*)(ins)) + *(int64_t*)(ins + 8));
		}
		void i64_add_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int64_t>(*(index_type*)(ins)) + mem.extract<int64_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r32_add_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<float>(*(index_type*)(ins)) + *(float*)(ins + 4));
		}
		void r32_add_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<float>(*(index_type*)(ins)) + mem.extract<float>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r64_add_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<double>(*(index_type*)(ins)) + *(double*)(ins + 8));
		}
		void r64_add_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<double>(*(index_type*)(ins)) + mem.extract<double>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r128_add_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<long double>(*(index_type*)(ins)) + *(long double*)(ins + 16));
		}
		void r128_add_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<long double>(*(index_type*)(ins)) + mem.extract<long double>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i8_div_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<char>(*(index_type*)(ins)) / *(char*)(ins + 1));
		}
		void i8_div_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<char>(*(index_type*)(ins)) / mem.extract<char>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i16_div_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int16_t>(*(index_type*)(ins)) / *(int16_t*)(ins + 2));
		}
		void i16_div_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int16_t>(*(index_type*)(ins)) / mem.extract<int16_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i32_div_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int32_t>(*(index_type*)(ins)) / *(int32_t*)(ins + 4));
		}
		void i32_div_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int32_t>(*(index_type*)(ins)) / mem.extract<int32_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i64_div_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int64_t>(*(index_type*)(ins)) / *(int64_t*)(ins + 8));
		}
		void i64_div_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int64_t>(*(index_type*)(ins)) / mem.extract<int64_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r32_div_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<float>(*(index_type*)(ins)) / *(float*)(ins + 4));
		}
		void r32_div_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<float>(*(index_type*)(ins)) / mem.extract<float>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r64_div_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<double>(*(index_type*)(ins)) / *(double*)(ins + 8));
		}
		void r64_div_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<double>(*(index_type*)(ins)) / mem.extract<double>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r128_div_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<long double>(*(index_type*)(ins)) / *(long double*)(ins + 16));
		}
		void r128_div_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<long double>(*(index_type*)(ins)) / mem.extract<long double>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i8_mul_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<char>(*(index_type*)(ins))* *(char*)(ins + 1));
		}
		void i8_mul_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<char>(*(index_type*)(ins))* mem.extract<char>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i16_mul_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int16_t>(*(index_type*)(ins))* *(int16_t*)(ins + 2));
		}
		void i16_mul_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int16_t>(*(index_type*)(ins))* mem.extract<int16_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i32_mul_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int32_t>(*(index_type*)(ins))* *(int32_t*)(ins + 4));
		}
		void i32_mul_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int32_t>(*(index_type*)(ins))* mem.extract<int32_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i64_mul_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int64_t>(*(index_type*)(ins))* *(int64_t*)(ins + 8));
		}
		void i64_mul_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int64_t>(*(index_type*)(ins))* mem.extract<int64_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r32_mul_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<float>(*(index_type*)(ins))* *(float*)(ins + 4));
		}
		void r32_mul_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<float>(*(index_type*)(ins))* mem.extract<float>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r64_mul_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<double>(*(index_type*)(ins))* *(double*)(ins + 8));
		}
		void r64_mul_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<double>(*(index_type*)(ins))* mem.extract<double>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r128_mul_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<long double>(*(index_type*)(ins))* *(long double*)(ins + 16));
		}
		void r128_mul_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<long double>(*(index_type*)(ins))* mem.extract<long double>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i8_sub_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<char>(*(index_type*)(ins)) - *(char*)(ins + 1));
		}
		void i8_sub_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<char>(*(index_type*)(ins)) - mem.extract<char>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i16_sub_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int16_t>(*(index_type*)(ins)) - *(int16_t*)(ins + 2));
		}
		void i16_sub_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int16_t>(*(index_type*)(ins)) - mem.extract<int16_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i32_sub_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int32_t>(*(index_type*)(ins)) - *(int32_t*)(ins + 4));
		}
		void i32_sub_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int32_t>(*(index_type*)(ins)) - mem.extract<int32_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void i64_sub_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int64_t>(*(index_type*)(ins)) - *(int64_t*)(ins + 8));
		}
		void i64_sub_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<int64_t>(*(index_type*)(ins)) - mem.extract<int64_t>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r32_sub_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<float>(*(index_type*)(ins)) - *(float*)(ins + 4));
		}
		void r32_sub_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<float>(*(index_type*)(ins)) - mem.extract<float>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r64_sub_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<double>(*(index_type*)(ins)) - *(double*)(ins + 8));
		}
		void r64_sub_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<double>(*(index_type*)(ins)) - mem.extract<double>(*(index_type*)(ins + sizeof(index_type))));
		}
		void r128_sub_vi(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<long double>(*(index_type*)(ins)) - *(long double*)(ins + 16));
		}
		void r128_sub_vv(char *ins) {
			my_memcpy(intern_result_buf, mem.extract<long double>(*(index_type*)(ins)) - mem.extract<long double>(*(index_type*)(ins + sizeof(index_type))));
		}
	}
	// the following code is gened by program 
	namespace {
		void i8_assign_vi(char *ins) {
			mem.extract<char>(*(index_type*)(ins)) = *(char*)(ins + 1);
		}
		void i8_assign_vv(char *ins) {
			mem.extract<char>(*(index_type*)(ins)) = mem.extract<char>(*(index_type*)(ins + sizeof(index_type)));
		}
		void i16_assign_vi(char *ins) {
			mem.extract<int16_t>(*(index_type*)(ins)) = *(int16_t*)(ins + 2);
		}
		void i16_assign_vv(char *ins) {
			mem.extract<int16_t>(*(index_type*)(ins)) = mem.extract<int16_t>(*(index_type*)(ins + sizeof(index_type)));
		}
		void i32_assign_vi(char *ins) {
			mem.extract<int32_t>(*(index_type*)(ins)) = *(int32_t*)(ins + 4);
		}
		void i32_assign_vv(char *ins) {
			mem.extract<int32_t>(*(index_type*)(ins)) = mem.extract<int32_t>(*(index_type*)(ins + sizeof(index_type)));
		}
		void i64_assign_vi(char *ins) {
			mem.extract<int64_t>(*(index_type*)(ins)) = *(int64_t*)(ins + 8);
		}
		void i64_assign_vv(char *ins) {
			mem.extract<int64_t>(*(index_type*)(ins)) = mem.extract<int64_t>(*(index_type*)(ins + sizeof(index_type)));
		}
		void r32_assign_vi(char *ins) {
			mem.extract<float>(*(index_type*)(ins)) = *(float*)(ins + 4);
		}
		void r32_assign_vv(char *ins) {
			mem.extract<float>(*(index_type*)(ins)) = mem.extract<float>(*(index_type*)(ins + sizeof(index_type)));
		}
		void r64_assign_vi(char *ins) {
			mem.extract<double>(*(index_type*)(ins)) = *(double*)(ins + 8);
		}
		void r64_assign_vv(char *ins) {
			mem.extract<double>(*(index_type*)(ins)) = mem.extract<double>(*(index_type*)(ins + sizeof(index_type)));
		}
		void r128_assign_vi(char *ins) {
			mem.extract<long double>(*(index_type*)(ins)) = *(long double*)(ins + 16);
		}
		void r128_assign_vv(char *ins) {
			mem.extract<long double>(*(index_type*)(ins)) = mem.extract<long double>(*(index_type*)(ins + sizeof(index_type)));
		}
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
		std::map<int16_t, instruction_type> _bin_operator_ins_table = {
			{ 6944,i8_assign_vi },{ 6960,i8_assign_vv },{ 6945,i16_assign_vi },
			{ 6961,i16_assign_vv },{ 6946,i32_assign_vi },{ 6962,i32_assign_vv },
			{ 6947,i64_assign_vi },{ 6963,i64_assign_vv },{ 6948,r32_assign_vi },
			{ 7012,r32_assign_vv },{ 6949,r64_assign_vi },{ 7013,r64_assign_vv },
			{ 6950,r128_assign_vi },{ 7014,r128_assign_vv },{ 288,i8_sadd_vi },
			{ 304,i8_sadd_vv },{ 289,i16_sadd_vi },{ 305,i16_sadd_vv },
			{ 290,i32_sadd_vi },{ 306,i32_sadd_vv },{ 291,i64_sadd_vi },
			{ 307,i64_sadd_vv },{ 292,r32_sadd_vi },{ 356,r32_sadd_vv },
			{ 293,r64_sadd_vi },{ 357,r64_sadd_vv },{ 294,r128_sadd_vi },
			{ 358,r128_sadd_vv },{ 1056,i8_sdiv_vi },{ 1072,i8_sdiv_vv },
			{ 1057,i16_sdiv_vi },{ 1073,i16_sdiv_vv },{ 1058,i32_sdiv_vi },
			{ 1074,i32_sdiv_vv },{ 1059,i64_sdiv_vi },{ 1075,i64_sdiv_vv },
			{ 1060,r32_sdiv_vi },{ 1124,r32_sdiv_vv },{ 1061,r64_sdiv_vi },
			{ 1125,r64_sdiv_vv },{ 1062,r128_sdiv_vi },{ 1126,r128_sdiv_vv },
			{ 800,i8_smul_vi },{ 816,i8_smul_vv },{ 801,i16_smul_vi },
			{ 817,i16_smul_vv },{ 802,i32_smul_vi },{ 818,i32_smul_vv },
			{ 803,i64_smul_vi },{ 819,i64_smul_vv },{ 804,r32_smul_vi },
			{ 868,r32_smul_vv },{ 805,r64_smul_vi },{ 869,r64_smul_vv },
			{ 806,r128_smul_vi },{ 870,r128_smul_vv },{ 544,i8_ssub_vi },
			{ 560,i8_ssub_vv },{ 545,i16_ssub_vi },{ 561,i16_ssub_vv },
			{ 546,i32_ssub_vi },{ 562,i32_ssub_vv },{ 547,i64_ssub_vi },
			{ 563,i64_ssub_vv },{ 548,r32_ssub_vi },{ 612,r32_ssub_vv },
			{ 549,r64_ssub_vi },{ 613,r64_ssub_vv },{ 550,r128_ssub_vi },
			{ 614,r128_ssub_vv },

			{ 1312,i8_add_vi },{ 1328,i8_add_vv },{ 1313,i16_add_vi },
			{ 1329,i16_add_vv },{ 1314,i32_add_vi },{ 1330,i32_add_vv },
			{ 1315,i64_add_vi },{ 1331,i64_add_vv },{ 1316,r32_add_vi },
			{ 1380,r32_add_vv },{ 1317,r64_add_vi },{ 1381,r64_add_vv },
			{ 1318,r128_add_vi },{ 1382,r128_add_vv },{ 2080,i8_div_vi },
			{ 2096,i8_div_vv },{ 2081,i16_div_vi },{ 2097,i16_div_vv },
			{ 2082,i32_div_vi },{ 2098,i32_div_vv },{ 2083,i64_div_vi },
			{ 2099,i64_div_vv },{ 2084,r32_div_vi },{ 2148,r32_div_vv },
			{ 2085,r64_div_vi },{ 2149,r64_div_vv },{ 2086,r128_div_vi },
			{ 2150,r128_div_vv },{ 1824,i8_mul_vi },{ 1840,i8_mul_vv },
			{ 1825,i16_mul_vi },{ 1841,i16_mul_vv },{ 1826,i32_mul_vi },
			{ 1842,i32_mul_vv },{ 1827,i64_mul_vi },{ 1843,i64_mul_vv },
			{ 1828,r32_mul_vi },{ 1892,r32_mul_vv },{ 1829,r64_mul_vi },
			{ 1893,r64_mul_vv },{ 1830,r128_mul_vi },{ 1894,r128_mul_vv },
			{ 1568,i8_sub_vi },{ 1584,i8_sub_vv },{ 1569,i16_sub_vi },
			{ 1585,i16_sub_vv },{ 1570,i32_sub_vi },{ 1586,i32_sub_vv },
			{ 1571,i64_sub_vi },{ 1587,i64_sub_vv },{ 1572,r32_sub_vi },
			{ 1636,r32_sub_vv },{ 1573,r64_sub_vi },{ 1637,r64_sub_vv },
			{ 1574,r128_sub_vi },{ 1638,r128_sub_vv },

			{ 1296,i8_add_iv },{ 1280,i8_add_ii },{ 1297,i16_add_iv },
			{ 1281,i16_add_ii },{ 1298,i32_add_iv },{ 1282,i32_add_ii },
			{ 1299,i64_add_iv },{ 1283,i64_add_ii },{ 1300,r32_add_iv },
			{ 1284,r32_add_ii },{ 1301,r64_add_iv },{ 1285,r64_add_ii },
			{ 1302,r128_add_iv },{ 1286,r128_add_ii },{ 2064,i8_div_iv },
			{ 2048,i8_div_ii },{ 2065,i16_div_iv },{ 2049,i16_div_ii },
			{ 2066,i32_div_iv },{ 2050,i32_div_ii },{ 2067,i64_div_iv },
			{ 2051,i64_div_ii },{ 2068,r32_div_iv },{ 2052,r32_div_ii },
			{ 2069,r64_div_iv },{ 2053,r64_div_ii },{ 2070,r128_div_iv },
			{ 2054,r128_div_ii },{ 1808,i8_mul_iv },{ 1792,i8_mul_ii },
			{ 1809,i16_mul_iv },{ 1793,i16_mul_ii },{ 1810,i32_mul_iv },
			{ 1794,i32_mul_ii },{ 1811,i64_mul_iv },{ 1795,i64_mul_ii },
			{ 1812,r32_mul_iv },{ 1796,r32_mul_ii },{ 1813,r64_mul_iv },
			{ 1797,r64_mul_ii },{ 1814,r128_mul_iv },{ 1798,r128_mul_ii },
			{ 1552,i8_sub_iv },{ 1536,i8_sub_ii },{ 1553,i16_sub_iv },
			{ 1537,i16_sub_ii },{ 1554,i32_sub_iv },{ 1538,i32_sub_ii },
			{ 1555,i64_sub_iv },{ 1539,i64_sub_ii },{ 1556,r32_sub_iv },
			{ 1540,r32_sub_ii },{ 1557,r64_sub_iv },{ 1541,r64_sub_ii },
			{ 1558,r128_sub_iv },{ 1542,r128_sub_ii },

			{ 2320,i8_eq_iv},{ 2304,i8_eq_ii },{ 2321,i16_eq_iv },
			{ 2305,i16_eq_ii },{ 2322,i32_eq_iv },{ 2306,i32_eq_ii },
			{ 2323,i64_eq_iv },{ 2307,i64_eq_ii },{ 2324,r32_eq_iv },
			{ 2308,r32_eq_ii },{ 2325,r64_eq_iv },{ 2309,r64_eq_ii },
			{ 2326,r128_eq_iv },{ 2310,r128_eq_ii },{ 3088,i8_ge_iv },
			{ 3072,i8_ge_ii },{ 3089,i16_ge_iv },{ 3073,i16_ge_ii },
			{ 3090,i32_ge_iv },{ 3074,i32_ge_ii },{ 3091,i64_ge_iv },
			{ 3075,i64_ge_ii },{ 3092,r32_ge_iv },{ 3076,r32_ge_ii },
			{ 3093,r64_ge_iv },{ 3077,r64_ge_ii },{ 3094,r128_ge_iv },
			{ 3078,r128_ge_ii },{ 2832,i8_gt_iv },{ 2816,i8_gt_ii },
			{ 2833,i16_gt_iv },{ 2817,i16_gt_ii },{ 2834,i32_gt_iv },
			{ 2818,i32_gt_ii },{ 2835,i64_gt_iv },{ 2819,i64_gt_ii },
			{ 2836,r32_gt_iv },{ 2820,r32_gt_ii },{ 2837,r64_gt_iv },
			{ 2821,r64_gt_ii },{ 2838,r128_gt_iv },{ 2822,r128_gt_ii },
			{ 3344,i8_le_iv },{ 3328,i8_le_ii },{ 3345,i16_le_iv },
			{ 3329,i16_le_ii },{ 3346,i32_le_iv },{ 3330,i32_le_ii },
			{ 3347,i64_le_iv },{ 3331,i64_le_ii },{ 3348,r32_le_iv },
			{ 3332,r32_le_ii },{ 3349,r64_le_iv },{ 3333,r64_le_ii },
			{ 3350,r128_le_iv },{ 3334,r128_le_ii },{ 3600,i8_lt_iv },
			{ 3584,i8_lt_ii },{ 3601,i16_lt_iv },{ 3585,i16_lt_ii },
			{ 3602,i32_lt_iv },{ 3586,i32_lt_ii },{ 3603,i64_lt_iv },
			{ 3587,i64_lt_ii },{ 3604,r32_lt_iv },{ 3588,r32_lt_ii },
			{ 3605,r64_lt_iv },{ 3589,r64_lt_ii },{ 3606,r128_lt_iv },
			{ 3590,r128_lt_ii },{ 2576,i8_ne_iv },{ 2560,i8_ne_ii },
			{ 2577,i16_ne_iv },{ 2561,i16_ne_ii },{ 2578,i32_ne_iv },
			{ 2562,i32_ne_ii },{ 2579,i64_ne_iv },{ 2563,i64_ne_ii },
			{ 2580,r32_ne_iv },{ 2564,r32_ne_ii },{ 2581,r64_ne_iv },
			{ 2565,r64_ne_ii },{ 2582,r128_ne_iv },{ 2566,r128_ne_ii },
			{ 2336,i8_eq_vi },{ 2352,i8_eq_vv },{ 2337,i16_eq_vi },
			{ 2353,i16_eq_vv },{ 2338,i32_eq_vi },{ 2354,i32_eq_vv },
			{ 2339,i64_eq_vi },{ 2355,i64_eq_vv },{ 2340,r32_eq_vi },
			{ 2404,r32_eq_vv },{ 2341,r64_eq_vi },{ 2405,r64_eq_vv },
			{ 2342,r128_eq_vi },{ 2406,r128_eq_vv },{ 3104,i8_ge_vi },
			{ 3120,i8_ge_vv },{ 3105,i16_ge_vi },{ 3121,i16_ge_vv },
			{ 3106,i32_ge_vi },{ 3122,i32_ge_vv },{ 3107,i64_ge_vi },
			{ 3123,i64_ge_vv },{ 3108,r32_ge_vi },{ 3172,r32_ge_vv },
			{ 3109,r64_ge_vi },{ 3173,r64_ge_vv },{ 3110,r128_ge_vi },
			{ 3174,r128_ge_vv },{ 2848,i8_gt_vi },{ 2864,i8_gt_vv },
			{ 2849,i16_gt_vi },{ 2865,i16_gt_vv },{ 2850,i32_gt_vi },
			{ 2866,i32_gt_vv },{ 2851,i64_gt_vi },{ 2867,i64_gt_vv },
			{ 2852,r32_gt_vi },{ 2916,r32_gt_vv },{ 2853,r64_gt_vi },
			{ 2917,r64_gt_vv },{ 2854,r128_gt_vi },{ 2918,r128_gt_vv },
			{ 3360,i8_le_vi },{ 3376,i8_le_vv },{ 3361,i16_le_vi },
			{ 3377,i16_le_vv },{ 3362,i32_le_vi },{ 3378,i32_le_vv },
			{ 3363,i64_le_vi },{ 3379,i64_le_vv },{ 3364,r32_le_vi },
			{ 3428,r32_le_vv },{ 3365,r64_le_vi },{ 3429,r64_le_vv },
			{ 3366,r128_le_vi },{ 3430,r128_le_vv },{ 3616,i8_lt_vi },
			{ 3632,i8_lt_vv },{ 3617,i16_lt_vi },{ 3633,i16_lt_vv },
			{ 3618,i32_lt_vi },{ 3634,i32_lt_vv },{ 3619,i64_lt_vi },
			{ 3635,i64_lt_vv },{ 3620,r32_lt_vi },{ 3684,r32_lt_vv },
			{ 3621,r64_lt_vi },{ 3685,r64_lt_vv },{ 3622,r128_lt_vi },
			{ 3686,r128_lt_vv },{ 2592,i8_ne_vi },{ 2608,i8_ne_vv },
			{ 2593,i16_ne_vi },{ 2609,i16_ne_vv },{ 2594,i32_ne_vi },
			{ 2610,i32_ne_vv },{ 2595,i64_ne_vi },{ 2611,i64_ne_vv },
			{ 2596,r32_ne_vi },{ 2660,r32_ne_vv },{ 2597,r64_ne_vi },
			{ 2661,r64_ne_vv },{ 2598,r128_ne_vi },{ 2662,r128_ne_vv }
		};



	}
	namespace print_ins {
		void print_str(char *ins) {
			printf("%s", ins);
		}
		void print_int_var(char *ins) {
			std::cout << mem.extract<int32_t>(*(index_type*)ins);
		}
	}
	// control
	namespace  control_ins{
		void jmp(char *ins) {
			pc = *(int*)ins;
		}
		void iffalse(char *ins) {
			if (!mem.extract<int32_t>(*(index_type*)ins))
			{
				pc = *(int*)(ins + sizeof(index_type));
			}
		}
	}
	instruction_type gen_covert_op(char t1, char t2)
	{
		int16_t ins_index = (int16_t)t1 << 4 | t2;
		if (_conv_operator_ins_table.find(ins_index) == _conv_operator_ins_table.end())
			throw Error("intern error! code: " + std::to_string(ins_index) + " E4");
		return _conv_operator_ins_table[ins_index];
	}
	instruction_type gen_bin_op(char _ty, char op)
	{   //|op  |mod|type|
		// vv->mod->11
		// vi->mod->10
		int16_t ins_index = (int16_t)(_ty) | (op << 8);
		if (_bin_operator_ins_table.find(ins_index) == _bin_operator_ins_table.end())
			throw Error("intern error! E5 error info:"+std::to_string(ins_index));
		return _bin_operator_ins_table[ins_index];
	}
}