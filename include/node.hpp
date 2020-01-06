#pragma once
/*
	AST Node 

*/
#include "type.hpp"
#include "lexer.hpp"
namespace hcc {
	 enum class NodeType{
		EXPR=1,VAR_DECL,
		NON_OP,UNARY_OP
	};
	class Node {
	public:
		Node(NodeType nt) :node_type(nt) {}
		NodeType get_node_type() { return node_type; }
		virtual std::string emit_code() { return ""; }
		virtual type::Type* get_type() { return type::basic_type_map["void"]; }
		virtual ~Node() {}
		virtual std::string debug() { return "<empty-node>"; }
	private:
		NodeType node_type;
	};
}