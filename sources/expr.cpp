#include "../include/expr.hpp"
#include "../include/info.hpp"
#include "../include/literal.hpp"
#include "../include/variables.hpp"
namespace hcc
{
	extern std::vector<std::string> instructions;
	bool literal_or_variable(NodeType nt)
	{
		if (nt == NodeType::LITERAL || nt == NodeType::VAR)
			return true;
		return false;
	}
	BinOp::BinOp(Node* left_n, Token* t, Node* right_n,type::Type* ty):Node(NodeType::BIN_OP),left_node(left_n),right_node(right_n),op(t)
	{
		if (ty != nullptr)
			set_type(ty);
		else
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
			instructions.push_back("("+sign+" "+left_name + " " + right_name+")");
			return;
		}
		var_name = get_tmp_var_name(false);
		instructions.push_back("("+get_type()->to_string() + ' ' + var_name + " " + "("+sign+" "+left_name +" "+ right_name+"))");
	}	
	namespace analyse_expr
	{
		Node* create_expr()
		{
			return assign();
		}
		Node* assign()
		{
			Node* result = compare();
			while (_is_assign(token_stream.this_tag()))
			{
				Token* tok = token_stream.this_token();
				token_stream.next();
				result = new BinOp(result, tok, compare());
			}
			return result;
		}
		Node* compare(type::Type* ty)
		{
			Node* result = expr(ty);
			while (1) {
				auto tok = token_stream.this_token();
				switch (tok->get_tag())
				{
				case EQ:
				case NE:
				case LT:
				case LE:
				case GE:
				case GT:
					token_stream.next();
					result = new BinOp(result, tok, expr(), type::basic_type_map["int"]);
					break;
				default:
					return result;
				}			
			}
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
				return parse_id();
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

				std::string bool_to_int_str = std::to_string((int)(token_stream.this_tag() == TTRUE));
				token_stream.next();
				return new LiteralValue(bool_to_int_str, 0);
			}
			auto result = tag_state_map.find(token_stream.this_tag());
			if (result == tag_state_map.end()) 
				throw Error("unexpected token "+ token_stream.this_token()->to_string() );
			auto tok = token_stream.this_token();
			token_stream.next();
			return new LiteralValue(tok->to_string(), result->second);
		}
	}
}