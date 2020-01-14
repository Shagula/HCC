#pragma once
#include <iostream>
#include "node.hpp"
#include <deque>
namespace hcc {
	class Jmp :public Node {
	public:
		Jmp(std::string _tag_name) :Node(NodeType::JMP), tag_name(_tag_name) {}
		void emit_code()override;
	private:
		std::string tag_name;
	};

	/*
		goto dest
		...
		dest: t++;
		// dest is a JmpTag
	*/
	class JmpTag :public Node {
	public:
		JmpTag(std::string _tag_name) :Node(NodeType::JMP_TAG),tag_name(_tag_name){}
		void emit_code()override;
	private:
		std::string tag_name;
	};
	class IfFalseToA:public Node
	{
	public:
		IfFalseToA(const std::string& ft, Node* _expr) :Node(NodeType::IF_FALSE_TO_A), condition(_expr), false_tag(ft) {}
		void emit_code()override;

	private:
		Node* condition;
		std::string false_tag;
	};
	namespace Parser {
		void build_block();
		void build_do_while();
		void build_while();
		void build_if();
	}
}