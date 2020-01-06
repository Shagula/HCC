#include "node.hpp"
namespace hcc {
	// the statement doing nothing at all
	class NonOp :public Node {
	public:
		NonOp() :Node(NodeType::NON_OP) {}
		std::string emit_code()override { return ""; }
	private:
	};
	class UnaryOp :public Node {
	public:
		UnaryOp(Token* t, Node* e):Node(NodeType::UNARY_OP),op(t), expr(e) {}
		std::string emit_code()override;

	private:
		Token* op;
		Node* expr;
	};
}