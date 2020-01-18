#pragma once
/*
	AST Node

*/
#include "type.hpp"
#include "lexer.hpp"
namespace hcc {
	extern std::vector<std::string> instructions;
	enum class NodeType {
		BEGIN_BLOCK, END_BLOCK,
		EXPR = 1, LOCAL_VAR_DECL, GLO_VAR_DECL,
		LITERAL, VAR,
		FUNC_DEF,FUNC_CALL,RETURN,
		IF_FALSE_TO_A, IFAELSEB, JMP, JMP_TAG,
		NON_OP, UNARY_OP, BIN_OP,
		BLOCK,
	};
	class Node {
	public:
		Node(NodeType nt) :node_type(nt) {}
		NodeType get_node_type() { return node_type; }
		virtual void emit_code() {}
		type::Type* get_type() { return type; }
		void set_type(type::Type* ty) {
			type = ty;
		}
		virtual ~Node() {}
		virtual std::string to_string() { return ""; }
		virtual std::string debug() { return "<empty-node>"; }
	private:
		type::Type* type = nullptr;
		NodeType node_type = NodeType::NON_OP;
	};
	std::string type_convert(type::Type* s, type::Type* dest, Node* n);
	class FixedInstruction :public Node {
	public:
		FixedInstruction(NodeType nt, const std::string &_content) :Node(nt), content(_content) {}
		void emit_code()override { instructions.push_back("(" + content + ")"); }
	private:
		std::string content;
	};
}