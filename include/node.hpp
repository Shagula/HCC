#pragma once
/*
	AST Node 

*/
#include "type.hpp"
#include "lexer.hpp"
namespace hcc {
	 enum class NodeType{
		EXPR=1,VAR_DECL,
		LITERAL,VAR,
		NON_OP,UNARY_OP,BIN_OP
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
		type::Type* type;
		NodeType node_type;
	};
	std::string type_convert(type::Type* s, type::Type* dest, Node* n);
}