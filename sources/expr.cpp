#include "../include/expr.hpp"
#include "../include/info.hpp"
namespace hcc
{
	extern std::vector<std::string> instructions;
	BinOp::BinOp(Node* left_n, Token* t, Node* right_n):Node(NodeType::BIN_OP),left_node(left_n),right_node(right_n),op(t)
	{
		set_type(left_n->get_type());
		if (get_type() == nullptr) {
			throw Error("type error!");
		}
	}
	void BinOp::emit_code()
	{
		// type not matched
		if (!left_node->get_type()->convertible(right_node->get_type()))
			throw Error("type not matched from " + left_node->get_type()->to_string() + " to " + right_node->get_type()->to_string());
		left_node->emit_code();
		right_node->emit_code();
		std::string right_name = right_node->to_string();
		std::string left_name = left_node->to_string();
		// if left_node's type isn't match with expr type; convert it 
		if (get_type() != right_node->get_type())
			left_name = type_convert(right_node->get_type(), get_type(), right_node);
		std::string sign = tag_to_sign(op->get_tag());
		if (_is_assign(op->get_tag()))
		{
			instructions.push_back(left_name + sign + right_name);
			return;
		}
		var_name = get_tmp_var_name(false);
		instructions.push_back(get_type()->to_string() + ' ' + var_name + "=" + left_name + sign + right_name);
	}	
	namespace analyse_expr
	{
		Node* create_expr()
		{
			return assign();
		}
		Node* assign()
		{
			Node* result = expr();
			while (_is_assign(token_stream.this_tag()))
			{
				Token* tok = token_stream.this_token();
				token_stream.next();
				result = new BinOp(result, tok, expr());
			}
			return result;
		}
		Node* expr()
		{
			Node* result = term();
			while (token_stream.this_tag() == PLUS || token_stream.this_tag() == MINUS)
			{
				Token* tok = token_stream.this_token();
				token_stream.next();
				result = new BinOp(result, tok, term());
			}
			return result;
		}
		Node* term()
		{
			Node* result = factor();
			while (token_stream.this_tag() == MUL || token_stream.this_tag() == DIV)
			{
				Token* tok = token_stream.this_token();
				token_stream.next();
				result = new BinOp(result, tok, factor());
			}
			return result;
		}
	}
}