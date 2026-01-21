#include "../spec/node.hpp"
#include "../spec/types.hpp"
#include "../spec/error.hpp"
#include <charconv>
#include <format>
#include <limits>
#include <string>
#include <system_error>
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

    auto return_sym = this->currentScope->getSymbol(node->return_type);

    if (return_sym) 
    {
        if (return_sym->kind == CtTypes::Kind::Container)
        {
            info->return_type = static_cast<CtTypes::ContainerInfo*>(return_sym);
        }
        else
        {   
            CtError::raise(
            CtError::ErrorType::NameError, 
            std::format("Non-Container type returned: {}", node->return_type)
            );
        }
      
    }
    else
    {
        CtError::raise(
            CtError::ErrorType::NameError, 
            std::format("Unknown type returned: {}", node->return_type)
        ); 
    }

    

    for (auto param: node->parameters)
    {
        this->handleDeclaration(param);
        // This will guarantee the following:
        auto* sym = this->currentScope->getSymbol(param->name);
        info->parameters.push_back(static_cast<CtTypes::ContainerInfo*>(sym));
        
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
            std::format("Undefined type: {}", node->type_id)
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
            std::format("Non-Container type: {}", node->type_id)
        ); 
    }  
    
    this->walk(node->val);
}


void CtResolver::handleIf(CtNode::If *node)
{
    this->walk(node->condition);
    this->walk(node->then_block);

    if (node->else_stmt)
    {
        this->walk(node->else_stmt);
    }
}


void CtResolver::handleLoop(CtNode::Loop *node)
{
    this->walk(node->block);
}


void CtResolver::handleWhile(CtNode::While *node)
{
    this->walk(node->condition);
    this->walk(node->block);
}


void CtResolver::handleFor(CtNode::For *node)
{
    this->walk(node->init);
    this->walk(node->condition);
    this->walk(node->step);
    this->walk(node->block);
}


void CtResolver::handleOut(CtNode::Out *node)
{

}

void CtResolver::handleEscape(CtNode::Escape *node)
{

}


inline bool convertInt(CtNode::Int* node)
{
    auto result = std::from_chars(
        node->raw.data(), 
        node->raw.data() + node->raw.size(), 
        node->val.i64
    );

    if (result.ec == std::errc{} && result.ptr == node->raw.data() + node->raw.size())
    {
        node->info = CtTypes::primitives["int"];
        return true;
    }

    result = std::from_chars(
        node->raw.data(), 
        node->raw.data() + node->raw.size(), 
        node->val.u64
    );

    if (result.ec == std::errc{} && result.ptr == node->raw.data() + node->raw.size())
    {
        node->info = CtTypes::primitives["uint"];
        return true;
    }

    return false;
}


void CtResolver::handleInt(CtNode::Int *node)
{
    if (!convertInt(node))
    {
        CtError::raise(
            CtError::ErrorType::NameError, 
            std::format("Out of range Int type: {}", node->raw)
        ); 
    }
}

void CtResolver::handleFloat(CtNode::Float *node)
{
    node->val.f64 = std::stod(node->raw);
    node->info = CtTypes::primitives["float"];
}

void CtResolver::handleBool(CtNode::Bool *node)
{
    node->info = CtTypes::primitives["bool"];
}

void CtResolver::handleBinaryOp(CtNode::BinaryOp *node)
{
    this->walk(node->left);
    this->walk(node->right);
}

void CtResolver::handleIdentifier(CtNode::Identifier *node)
{
    auto sym = this->currentScope->getSymbol(node->val);

    if (sym == nullptr)
    {
        CtError::raise(
            CtError::ErrorType::NameError, 
            std::format("Undefined identifier: {}", node->val)
        ); 
    }

    if (sym->kind == CtTypes::Kind::Variable)
    {
        node->info = static_cast<CtTypes::ContainerInfo*>(sym);
    }
    else
    {
        CtError::raise(
            CtError::ErrorType::NameError, 
            std::format("Unexpected identifier: {}", node->val)
        ); 
    } 

}

void CtResolver::handleFunctionCall(CtNode::FunctionCall *node)
{

}

void CtResolver::handleAssignment(CtNode::Assignment *node)
{
    this->walk(node->name);
    this->walk(node->value);
}

void CtResolver::handleTypeCast(CtNode::TypeCast *node)
{

}


void CtResolver::resolve(CtNode::RootProgram *root)
{
    CtTypes::initPrimitives();
    this->handleRoot(root);
}