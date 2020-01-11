#pragma once
#include <string>
namespace hcc {
	size_t get_line_no();
	class Error
	{
	public:
		Error(const std::string& str) :ems(str) {}
		virtual std::string what();
	protected:
		std::string ems;
	};
	class LexerError :public Error
	{
	public:
		LexerError(const std::string& str);
		std::string what()override;
	private:
		int line_no = 0;
	};
}