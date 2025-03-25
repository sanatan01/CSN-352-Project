#pragma once

#include <string>
#include <vector>
#include <fstream>

template<typename Base, typename T>
inline bool instanceof(const T*) {
   return std::is_base_of<Base, T>::value;
}

class Node {
    public:
        unsigned long long int id;
        int is_printed = 1;
        unsigned int line_num;
        unsigned int column;

        virtual void dotify() = 0;
        virtual void add_children(std::initializer_list<Node*> nodes);
        unsigned long long int get_id();
    protected:
        Node (unsigned int line_num = -1, unsigned int column = -1);
        virtual ~Node() {}
};;


class Terminal : public Node {
	public:
		std::string name;
		std::string value;
		Terminal(const char * name_, const char * value_,  unsigned int _line_num = -1, unsigned int _column = -1);
		void dotify();
		
};

class NonTerminal : public Node {
	public:
		std::string name;
		std::vector <Node *> children;
		

		NonTerminal(const char * name_);
        void add_children(std::initializer_list<Node*> nodes);
		void dotify();

};

unsigned long long int get_next_node_id();
Terminal * create_terminal(const char * name, const char * value, unsigned int line_num = -1, unsigned int column = -1);
NonTerminal * create_non_terminal (const char* name, std::initializer_list<Node*> nodes);

void file_writer(std::string s);