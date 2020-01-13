#pragma once
#include <iostream>
#include "node.hpp"
namespace hcc {
	class Block :public Node {
	public:
		Block(const std::vector<Node*> &b) :Node(NodeType::BLOCK), block_content(b) {}
		void emit_code()override;
	private:
		std::vector<Node*> block_content;
	};
	class IfTrueToA:public Node
	{
	public:
		IfTrueToA(const std::string& ft, Node* _expr,Block* blo) :Node(NodeType::IF_TRUE_A_OR_B),condition(_expr),true_tag(ft) ,block(blo){}
		void emit_code()override;

	private:
		Block* block;
		Node* condition;
		std::string false_tag;
	};
	namespace Parser {
		Block* build_block();
		void build_do_while();
		void build_while();
		Node* build_if();
	}
}