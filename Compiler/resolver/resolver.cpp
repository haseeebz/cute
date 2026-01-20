#include "../spec/node.hpp"
#include "../spec/types.hpp"
#include "../spec/error.hpp"
#include <format>

#include "resolver.hpp"



void CtResolver::handleRoot(CtNode::RootProgram *node)
{
    node->scope = new CtScope(nullptr);
    this->currentScope = node->scope;
    
    for (auto type: CtTypes::primitives)
    {
        node->scope->symbols[type.first] = type.second; 
    };

    this->handleSource(node->src);
}


void CtResolver::handleSource(CtNode::Source *node)
{   
    node->scope = new CtScope(this->currentScope);
    this->currentScope = node->scope;

    for (auto func: node->functions)
    {
        this->handleFunction(func.second);
    }

    this->currentScope = node->scope->parent;
}


void CtResolver::handleFunction(CtNode::Function *node)
{
    auto* info = new CtTypes::FunctionInfo();
    this->currentScope->addSymbol(node->name, info);

    auto sym = this->currentScope->getSymbol(node->return_type);

    if (!sym) 
    {
        CtError::raise(
            CtError::ErrorType::NameError, 
            "Unknown return type!"
        );
    }

    if (sym->kind == CtTypes::Kind::Container)
    {
        info->return_type = static_cast<CtTypes::ContainerInfo*>(sym);
    }

    for (auto param: node->parameters)
    {
        this->handleDeclaration(param);
        auto* sym = this->currentScope->getSymbol(param->name);

        if (sym->kind == CtTypes::Kind::Container)
        {
            info->parameters.push_back(static_cast<CtTypes::ContainerInfo*>(sym));
        }
    }   
    
    this->handleStmtBlock(node->block);
}


void CtResolver::handleContainer(CtNode::Container *node)
{

}

void CtResolver::handleStmtBlock(CtNode::StmtBlock *node)
{
    node->scope = new CtScope(this->currentScope);
    this->currentScope = node->scope;

    for (auto stmt: node->stmts)
    {
        this->walk(stmt);
    }

    this->currentScope = node->scope->parent;
}


void CtResolver::handleDeclaration(CtNode::Declaration *node)
{
    auto sym = this->currentScope->getSymbol(node->type_id);

    if (sym == nullptr)
    {
        CtError::raise(
            CtError::ErrorType::NameError, 
            std::format("Unknown type! {}", node->type_id)
        ); 
    }

    if (sym->kind == CtTypes::Kind::Container)
    {
        node->info = static_cast<CtTypes::ContainerInfo*>(sym);

        auto* variable_info = new CtTypes::VariableInfo();
        variable_info->type = node->info;
        this->currentScope->addSymbol(node->name, variable_info);
    }
    else
    {
        CtError::raise(
            CtError::ErrorType::NameError, 
            "Type is not a container!"
        ); 
    }   
}

void CtResolver::handleIf(CtNode::If *node)
{

}

void CtResolver::handleLoop(CtNode::Loop *node)
{

}

void CtResolver::handleWhile(CtNode::While *node)
{

}

void CtResolver::handleFor(CtNode::For *node)
{

}

void CtResolver::handleOut(CtNode::Out *node)
{

}

void CtResolver::handleEscape(CtNode::Escape *node)
{

}

void CtResolver::handleInt(CtNode::Int *node)
{

}

void CtResolver::handleFloat(CtNode::Float *node)
{

}

void CtResolver::handleBool(CtNode::Bool *node)
{

}

void CtResolver::handleBinaryOp(CtNode::BinaryOp *node)
{

}

void CtResolver::handleIdentifier(CtNode::Identifier *node)
{

}

void CtResolver::handleFunctionCall(CtNode::FunctionCall *node)
{

}

void CtResolver::handleAssignment(CtNode::Assignment *node)
{

}

void CtResolver::handleTypeCast(CtNode::TypeCast *node)
{

}


void CtResolver::resolve(CtNode::RootProgram *root)
{
    CtTypes::initPrimitives();
    this->handleRoot(root);
}