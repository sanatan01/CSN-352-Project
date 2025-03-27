#include <ast.hpp>
#include<assert.h>
#include<string>
#include<iostream>
#include<sstream>

static unsigned long long int id_count = 0;

unsigned long long int get_next_node_id() {
	return id_count++;
}

// Constructors

Node::Node(unsigned int line_num, unsigned int column) {
    this->line_num = line_num;
    this->column = column;
    this->id = get_next_node_id();
}

Terminal::Terminal(const char * name_, const char * value_, unsigned int _line_num=0, unsigned int _column=0) : Node(_line_num, _column) {
    this->name = name_;
    this->value = value_;
}

NonTerminal::NonTerminal(const char * name_) {
    this->name = name_;
}


// Methods

void Node::add_children(std::initializer_list<Node*> nodes) {
    assert(0);
}

void Terminal::dotify() {
	if(is_printed){
		is_printed = 0;
		std::stringstream ss;
		ss << "\t" << id << " [label=\"" << name << " : " << value << "\"];\n";
		file_writer(ss.str());
	}
}
void NonTerminal::dotify() {
	if(is_printed){
		is_printed = 0;
		std::stringstream ss;
		ss << "\t" << id << " [label=\"" << name << "\"];\n";
		for (auto it = children.begin(); it != children.end(); it++) {
			ss << "\t" << id << " -> " << (*it)->id << ";\n";
		}
		file_writer(ss.str());

		for(auto it = children.begin(); it != children.end(); it++){
			(*it)->dotify();
		}
	}
}

void NonTerminal::add_children(std::initializer_list<Node*> nodes) {
    for (auto node : nodes) {
        this->children.push_back(node);
    }
}

// Creation of nodes

Terminal * create_terminal(const char * name, const char * value, unsigned int line_num=0, unsigned int column=0) {
    Terminal * newTerminal = new Terminal(name, value, line_num, column);
    return newTerminal;
}

Node * create_non_terminal(const char * name, std::initializer_list<Node*> nodes) {
    NonTerminal * newNonTerminal = new NonTerminal(name);
    newNonTerminal->add_children(nodes);
    if(nodes.size() == 0) {
        delete newNonTerminal;
        return nullptr;
    }
    return newNonTerminal;
}

