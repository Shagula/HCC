#include "../include/error.hpp"
#include "../include/lexer.hpp"
namespace hcc {
	size_t get_line_no()
	{
		auto content = token_stream._get_content();
		auto pos = token_stream._get_pos();
		while (content[pos]->get_tag() != ENDL)
		{
			pos--;
		}
		return Endl::get_value(content[pos]);
	}

	LexerError::LexerError(const std::string& str) :Error(str)
	{
		line_no = Endl::current_line;
	}
	std::string LexerError::what()
	{
		return "<Lexer Error:Line " + std::to_string(line_no) + " " + ems + ">";
	}
	std::string Error::what()
	{
		const std::string error_msg = "<line " + std::to_string(get_line_no()) + ">" + ems + " current_word:" + token_stream.this_token()->to_string();
		return error_msg + "\n";
	}
}