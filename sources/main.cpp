#include "../include/error.hpp"
#include "../include/info.hpp"
#include "../include/parser.hpp"
#include "../interpreter/include/memory.hpp"
#include <fstream>
// last update 2020 2-1 21:38, By Htto.
std::string get_file_content(const std::string& filename)
{
	using namespace std;
	ifstream ifs(filename);
	if (!ifs)
	{
		throw std::runtime_error("invalid file");
	}
	std::string file_content((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
	return file_content;
}
void run_hcc() {
	try {
		auto file_content = get_file_content("test.c");
		using namespace hcc;
		build_token_stream(file_content);
		hcc::Parser::build_program();

		for (auto a : abstract_instruction_table) {
			a->emit_code();
		}
		for (auto a : instructions) {
			std::cout << a << std::endl;
		}
	}
	catch (hcc::Error & e) {
		std::cout << e.what();
	}
}
void test_memory() {
	using namespace vm;
	mem.push(123);
	int p=mem.push(23.34);
	std::cout << mem.extract<double>(p);
}
int main() {
	run_hcc();
	while(true)std::cin.get();
	return 0;
}