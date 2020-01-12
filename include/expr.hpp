#include "node.hpp"
namespace hcc {
	// the statement doing nothing at all
	class NonOp :public Node {
	public:
		NonOp() :Node(NodeType::NON_OP) {}
	private:
	};
	class UnaryOp :public Node {
	public:
		UnaryOp(Token* t, Node* e):Node(NodeType::UNARY_OP),op(t), expr(e) {}
		void emit_code()override;

	private:
		Token* op;
		Node* expr;
	};
	// BinOp receive two arguments , for instance: a+b, a is the left v, b is the right v
	// '+' is op, BinOp generate gen or execute directly.
	class BinOp :public Node {
	public:
		BinOp(Node* left_n, Token* t, Node* right_n,type::Type* ty=nullptr);
		void emit_code()override;
		std::string to_string()override {
			return var_name;
		}
	private:
		std::string var_name;
		Node* left_node;
		Token* op;
		Node* right_node;
	};
	namespace analyse_expr {
		Node* create_expr();
		Node* assign();
		Node* compare(type::Type* ty=type::void_type);
		Node* expr(type::Type* ty=type::void_type);
		Node* term(type::Type* ty);
		Node* factor(type::Type* ty);
	}
}