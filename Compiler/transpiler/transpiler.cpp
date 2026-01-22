#include "../spec/node.hpp"
#include "../codegen/node.hpp"

#include "transpiler.hpp"


CtGenNode::Root* 
CtTranspiler::handleRoot(CtNode::RootProgram *node)
{
    auto* root = new CtGenNode::Root();

    root->src = this->handleSource(node->src);
    return root;
}


CtGenNode::Source* 
CtTranspiler::handleSource(CtNode::Source *node)
{
    auto* src = new CtGenNode::Source();
    
    for (auto func: node->functions)
    {
        src->objects.push_back(this->handleFunction(func.second));
    }

    for (auto con: node->containers)
    {
        src->objects.push_back(this->handleContainer(con.second));
    }

    return src;
}

CtGenNode::Function* 
CtTranspiler::handleFunction(CtNode::Function *node)
{
    auto* func = new CtGenNode::Function();

    func->name = node->name;
    func->return_type = node->return_type;

    for (auto decl: node->parameters)
    {
        func->parameters.push_back(this->handleDeclaration(decl));
    }

    func->body = this->handleStmtBlock(node->block);
    
    return func;
}

CtGenNode::Struct* 
CtTranspiler::handleContainer(CtNode::Container *node)
{
    return nullptr;
}

CtGenNode::StmtBlock* 
CtTranspiler::handleStmtBlock(CtNode::StmtBlock *node)
{
    auto* block = new CtGenNode::StmtBlock();

    for (auto s: node->stmts)
    {
        block->body.push_back(static_cast<CtGenNode::Statement*>(this->walk(s)));
    }

    return block;
}

CtGenNode::Declaration* 
CtTranspiler::handleDeclaration(CtNode::Declaration *node)
{
    auto* decl = new CtGenNode::Declaration();
    decl->var = node->name;
    decl->type = node->info->repr;
    if (node->val)
    {
        decl->val = static_cast<CtGenNode::Expression*>(this->walk(node->val));
    }

    return decl;
};

CtGenNode::If* 
CtTranspiler::handleIf(CtNode::If *node)
{
    return nullptr;
};

CtGenNode::While* 
CtTranspiler::handleLoop(CtNode::Loop *node)
{
    return nullptr;
};

CtGenNode::While* 
CtTranspiler::handleWhile(CtNode::While *node)
{
    return nullptr;
};

CtGenNode::For* 
CtTranspiler::handleFor(CtNode::For *node)
{
    return nullptr;
};

CtGenNode::Call* 
CtTranspiler::handleOut(CtNode::Out *node)
{
    return nullptr;
};

CtGenNode::StmtBlock* 
CtTranspiler::handleEscape(CtNode::Escape *node)
{
    return nullptr;
};

CtGenNode::Literal* 
CtTranspiler::handleInt(CtNode::Int *node)
{
    auto* literal = new CtGenNode::Literal();
    literal->val = node->raw;
    return literal;
};

CtGenNode::Literal* 
CtTranspiler::handleFloat(CtNode::Float *node)
{
    auto* literal = new CtGenNode::Literal();
    literal->val = node->raw;
    return literal;
};

CtGenNode::Literal* 
CtTranspiler::handleBool(CtNode::Bool *node)
{
    auto* literal = new CtGenNode::Literal();
    literal->val = node->val ? "true" : "false";
    return literal;
};


using CtLang::BinaryOpType;

const char* binaryop_to_char(BinaryOpType op)
{
    switch (op)
    {
        case BinaryOpType::Add:            return "+";
        case BinaryOpType::Sub:            return "-";
        case BinaryOpType::Mul:            return "*";
        case BinaryOpType::Div:            return "/";
        case BinaryOpType::Mod:            return "%";

        case BinaryOpType::Equal:          return "==";
        case BinaryOpType::NotEqual:       return "!=";
        case BinaryOpType::Lesser:         return "<";
        case BinaryOpType::LesserEqual:    return "<=";
        case BinaryOpType::Greater:        return ">";
        case BinaryOpType::GreaterEqual:   return ">=";

        case BinaryOpType::BitShiftLeft:   return "<<";
        case BinaryOpType::BitShiftRight:  return ">>";
        case BinaryOpType::BitAnd:         return "&";
        case BinaryOpType::BitOr:          return "|";
        case BinaryOpType::BitXor:         return "^";

        case BinaryOpType::LogicAnd:       return "&&";
        case BinaryOpType::LogicOr:        return "||";
    }

    // Because the compiler isn’t psychic and you will forget to update this.
    return "<unknown-op>";
}


CtGenNode::BinaryOp* 
CtTranspiler::handleBinaryOp(CtNode::BinaryOp *node)
{
    auto* op = new CtGenNode::BinaryOp();
    op->op = binaryop_to_char(node->op);
    op->lhs = static_cast<CtGenNode::Expression*>(this->walk(node->left));
    op->rhs = static_cast<CtGenNode::Expression*>(this->walk(node->right));
    return op;
};


using CtLang::UnaryOpType;
const char* unaryop_to_char(UnaryOpType op)
{
    switch (op)
    {
        case UnaryOpType::LogicNot:   return "!";
        case UnaryOpType::BitNot:     return "~";
        case UnaryOpType::Negation:   return "-";
        case UnaryOpType::Increment: return "++";
        case UnaryOpType::Decrement: return "--";
    }

    return "<unknown-op>";
}


CtGenNode::UnaryOp* 
CtTranspiler::handleUnaryOp(CtNode::UnaryOp *node)
{
    auto* op = new CtGenNode::UnaryOp();
    op->op = unaryop_to_char(node->op);
    op->expr = static_cast<CtGenNode::Expression*>(this->walk(node->operand));
    return op;
};

CtGenNode::Identifier* 
CtTranspiler::handleIdentifier(CtNode::Identifier *node)
{
    auto* identifier = new CtGenNode::Identifier();
    identifier->val = node->val;
};

CtGenNode::Call* 
CtTranspiler::handleFunctionCall(CtNode::FunctionCall *node)
{
    auto* func_call = new CtGenNode::Call();
    func_call->caller = node->name;

    for (auto a: node->args)
    {
        func_call->args.push_back(static_cast<CtGenNode::Expression*>(this->walk(a)));
    }

    return func_call;
}

CtGenNode::Assignment* 
CtTranspiler::handleAssignment(CtNode::Assignment *node)
{
    auto* assign = new CtGenNode::Assignment();
    assign->var = node->name->val;
    assign->val = static_cast<CtGenNode::Expression*>(this->walk(node->value));
   
    return assign;
}


CtGenNode::Root* 
CtTranspiler::transpile(CtNode::RootProgram* root)
{
    CtGenNode::Root* genroot = this->handleRoot(root);
    return genroot;
}
