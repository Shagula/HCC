#pragma once
#include <iostream>
#include "node.hpp"
namespace hcc {
	class IfTrueToAOrB:public Node
	{
	public:
		IfTrueToAOrB(const std::string& tt, const std::string& ft, Node* _expr) :Node(NodeType::IF_TRUE_A_OR_B),expr(_expr),true_tag(tt),false_tag(ft) {}
		void emit_code()override;
	private:
		Node* expr;
		std::string true_tag;
		std::string false_tag;
	};
}