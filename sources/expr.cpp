#include "../include/expr.hpp"
#include "../include/info.hpp"
#include "../include/literal.hpp"
#include "../include/variables.hpp"
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
			right_name = type_convert(right_node->get_type(), get_type(), right_node);
		std::string sign = tag_to_sign(op->get_tag());
		if (_is_assign(op->get_tag()))
		{
			instructions.push_back(left_name + sign + right_name);
			return;
		}
		var_name = get_tmp_var_name(false);
		instructions.push_back(get_type()->to_string() + ' ' + var_name + "=" + "("+sign+" "+left_name +" "+ right_name+")");
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
		Node* expr(type::Type* ty)
		{
			Node* result = term(ty);
			while (token_stream.this_tag() == PLUS || token_stream.this_tag() == MINUS)
			{
				Token* tok = token_stream.this_token();
				token_stream.next();
				result = new BinOp(result, tok, term(ty));
			}
			return result;
		}
		Node* term(type::Type* ty)
		{
			Node* result = factor(ty);
			while (token_stream.this_tag() == MUL || token_stream.this_tag() == DIV)
			{
				Token* tok = token_stream.this_token();
				token_stream.next();
				result = new BinOp(result, tok, factor(ty));
			}
			return result;
		}
		Node* factor(type::Type* ty) {
			int s = 0;
			switch (token_stream.this_tag())
			{
			case LPAREN: {
				token_stream.match(LPAREN);
				auto ret = expr(ty);
				token_stream.match(RPAREN);
				return ret; 
			}
			case ID:
				return parse_id(ty);
			default:
				break;
			}
			// literal 
			std::map<Tag, int> tag_state_map{
				{INTEGER,0},{UINTEGER,1},{LONG_INTEGER,2},
				{ULONG_INTEGER,3},{UNSIGNED_CHAR_LIT,4},{CHAR_LIT,5},
				{FLOAT,6},{REAL,7},{LONG_REAL,8}
			};
			if (token_stream.this_tag()==TTRUE||token_stream.this_tag()==TFALSE)
			{
				token_stream.next();
				return new LiteralValue(std::to_string((int)(token_stream.this_tag() == TTRUE)), 0);
			}
			auto result = tag_state_map.find(token_stream.this_tag());
			if (result == tag_state_map.end()) 
				throw Error("unknown token!");
			auto tok = token_stream.this_token();
			token_stream.next();
			return new LiteralValue(tok->to_string(), result->second);
		}
	}
}