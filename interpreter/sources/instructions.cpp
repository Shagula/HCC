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
		void write_t_8(char *ins) {
			mem.push(*intern_result_buf);
		}
		void write_t_16(char * ins) {
			mem.push(*(int16_t*)intern_result_buf);
		}
		void write_t_32(char *ins) {
			mem.push(*(int32_t*)intern_result_buf);
		}
		void write_t_64(char *ins) {
			mem.push(*(int64_t*)intern_result_buf);
		}
	}
	// the following code is gened by program 
	template<typename _ty>
	void my_memcpy(void* _dst, _ty src)
	{
		memcpy(_dst, &src, sizeof(src));
	}
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
			{ 550,r128_ssub_vi },{ 614,r128_ssub_vv },

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
			{ 1558,r128_sub_iv },{ 1542,r128_sub_ii }
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
		//return ret;
	}
}