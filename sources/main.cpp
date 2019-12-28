#include "../include/lexer.hpp"
#include "../include/error.hpp"

#include <fstream>
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
		token_stream.print();
	}
	catch (hcc::Error & e) {
		std::cout << e.what();
	}
}
int main() {
	double a2= 1.2e4;
	const char const * cstr = "HELLO";
	const char const const const *const b = cstr;
	const char *const * const a = &b;
	std::cout << *a;

	while(true)std::cin.get();
	return 0;
}