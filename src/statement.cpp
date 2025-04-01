#include <statement.hpp>
#include <expression.hpp>
#include <cassert>
#include "types.cpp"
// #include "y.tab.c"
// NOTE: append, create_new_goto, backpatch,create_new_label functions will be implemented in 3ac.cpp, it is defined in 3ac.hpp
//--------------Statement List Functions--------------------------///

Statement *create_statement_list(Statement *st1)
{
    if (st1 == nullptr)
    {
        return nullptr;
    }
    Statement *S = new Statement();
    S->name = "statement_list";
    // S->add_children( {st1} );
    append(S->nextlist, st1->nextlist);
    append(S->continuelist, st1->continuelist);
    append(S->breaklist, st1->breaklist);
    append(S->caselist, st1->caselist);
    append(S->returnlist, st1->returnlist);

    return S;
}

Statement *add_to_statement_list(Statement *stl = nullptr, StatementType *st1)
{
    if (st1 == nullptr)
    {
        return stl;
    }
    else if (stl == nullptr)
    {
        return create_statement_list(st1->s);
    }

    // stl->add_children( {st1} );
    stl->nextlist = st1->s->nextlist; //
    append(stl->continuelist, st1->s->continuelist);
    append(stl->breaklist, st1->s->breaklist);
    append(stl->caselist, st1->s->caselist);
    append(stl->returnlist, st1->s->returnlist);
    return stl;
}

Statement *create_selection_statement_if(Expression *ex, GoTo *_false, Label *l1, Statement *st1, GoTo *_goto, Label *l2, Statement *st2)
{
    SelectionStatement *S = new SelectionStatement();
    if (st2 == nullptr)
    {
        S->name = "IF";
        S->add_children({ex, st1});
        // backpatch( ex->truelist, l1 );
        // _false->set_res( ex->res );
        ex->falselist.push_back(_false);
        if (l2 != nullptr)
        {
            // backpatch( ex->falselist, l2 );
        }
        append(S->nextlist, ex->falselist);
        if (st1 != nullptr)
        {
            append(S->nextlist, st1->nextlist);
            append(S->breaklist, st1->breaklist);
            append(S->continuelist, st1->continuelist);
            append(S->caselist, st1->caselist);
            append(S->returnlist, st1->returnlist);
        }
        if (_goto != nullptr)
        {
            S->nextlist.push_back(_goto);
        }
    }
    else
    {
        assert(l2 != nullptr);
        assert(_goto != nullptr);

        S->name = "IF ELSE";
        S->add_children({ex, st1, st2});
        // backpatch(ex->truelist, l1);
        // _false->set_res(ex->res);
        ex->falselist.push_back(_false);
        // backpatch(ex->falselist, l2);

        if (st1 != nullptr)
        {
            append(S->nextlist, st1->nextlist);
            append(S->breaklist, st1->breaklist);
            append(S->continuelist, st1->continuelist);
            append(S->caselist, st1->caselist);
            append(S->returnlist, st1->returnlist);
        }
        S->nextlist.push_back(_goto);
        append(S->nextlist, st2->nextlist);
        append(S->breaklist, st2->breaklist);
        append(S->continuelist, st2->continuelist);
        append(S->caselist, st2->caselist);
        append(S->returnlist, st2->returnlist);
    }
    switch_temp = nullptr;
    return S;
}

void create_switch( Expression * ex ){
	Identifier * id = new Identifier(("switch:"+std::to_string(line_num)).c_str(), line_num, column);
	SymTabEntry * symbol = new SymTabEntry("switch:"+std::to_string(line_num), line_num, column  );
	symbol->type.standard_type = &type_specifiers[INT_T];
	size_t size = symbol->type.getSize();
	local_symbol_table.offset += WORD_SIZE;
	local_symbol_table.reqd_size = local_symbol_table.offset > local_symbol_table.reqd_size ? local_symbol_table.offset : local_symbol_table.reqd_size;
	local_symbol_table.add_to_table( symbol, id, false);
	// Address* t2 = new_3id(symbol);
	// Address * t1;
	// MEM_EMIT(ex,t1);
	// emit(t2,"=",t1,nullptr);
	// ex->res = t2;
}

Statement *create_selection_statement_switch(Expression *ex1, GoTo *_test, Statement *st1, GoTo *_goto){
	SelectionStatement *S = new SelectionStatement();
	S->name = "SWITCH";
	S->add_children({ex1, st1});
	GlobalType expType = ex1->type;
	if (!type_specifiers[INT_T].isEqual(*expType.standard_type))
	{
		error_msg("Invalid Type " + expType.getType() + " in Switch Case",line_num);
	}

	S->nextlist.push_back(_goto);

	// Address *t1, *t2;
	// MEM_EMIT(ex1,t1);
	// t2= new_temp();
	// backpatch(_test, create_new_label());
	Label * default_label = nullptr;
    for(auto i:switch_label){
		if (i.first == "" ) {
			default_label = i.second;
			continue;
		}
		// Address * con = new_3const(0, INT3);
		// con->name=i.first;
		// emit( t2 , "==",t1,con );
		// GoTo *_goto=create_new_goto_cond(t2,true);
		// backpatch(_goto, i.second);
	}
	if ( default_label != nullptr ) {
		create_new_goto(default_label);
	}
	switch_label.clear();
	switch_type=nullptr; 
	append(S->nextlist,st1->breaklist);
	append(S->nextlist,st1->nextlist);
	append(S->continuelist,st1->continuelist);
	append(S->caselist,st1->caselist);
	append(S->returnlist,st1->returnlist);
	switch_temp=nullptr;
	return S;
	
}

// ------------------------------------------Iteration Statements------------------------------------------
Statement* create_iteration_statement_while(Label * l1, Expression *e1, GoTo * _false, Label * l2, Statement *s1 ){
	IterationStatement * S = new IterationStatement();
	S->add_children({e1,s1});
	S->name = "WHILE";

	// backpatch(e1->truelist,l2);
	// _false->set_res( e1->res ); 
	e1->falselist.push_back(_false);
	append(S->nextlist,e1->falselist);
	if ( s1 != nullptr ) {
		// backpatch(s1->nextlist,l1);
		// backpatch(s1->continuelist,l1);
		append(S->nextlist,s1->breaklist);
		append(S->returnlist,s1->returnlist);
	}
	GoTo * _goto = create_new_goto(l1);

	return S;
	
}

Statement* create_iteration_statement_do_while(Label *l1,Statement *s1,  Label *l2,Expression *e1, GoTo * _false ){
	IterationStatement *S=new IterationStatement();
	S->add_children({e1,s1});
	S->name="DO WHILE";
	
	// backpatch(e1->truelist,l1);
	// _false->set_res( e1->res ); 
	e1->falselist.push_back(_false);
	append(S->nextlist,e1->falselist);
	if ( s1 != nullptr ) {
		// backpatch(s1->nextlist,l2);
		// backpatch(s1->continuelist,l2);
		append(S->nextlist,s1->breaklist);
		append(S->returnlist,s1->returnlist);
	}
	GoTo * _goto = create_new_goto(l1);
	return S;
}

Statement* create_iteration_statement_for( Expression * ex1, Label * l1,  Expression * ex2, Label * l2, Statement*s1 ){
    IterationStatement *S=new IterationStatement();
	S->add_children({ex1,ex2,s1});
	S->name = "FOR";
	if ( ex2 != nullptr ) {
		// backpatch( ex2->truelist, l2 );
		append(S->nextlist, ex2->falselist);
	}
	if ( s1 != nullptr ) {
		// backpatch(st1->nextlist,l1);
		// backpatch(st1->continuelist,l1);
		append(S->nextlist, s1->breaklist);
		append(S->returnlist,s1->returnlist);
	}
	GoTo * _goto = create_new_goto(l1);
	return S;
}

Statement* create_iteration_statement_for( Expression * ex1, Label * l1, Expression * ex2, GoTo * _goto1, Label * l2, Expression * ex3, GoTo * _goto2 , Label * l3, Statement*s1 ){
    IterationStatement *S=new IterationStatement();
	S->add_children({ex1,ex2,ex3,s1});
	S->name = "FOR";

	if ( ex2 != nullptr ) {
		// backpatch( ex2->truelist, l3 );
		append(S->nextlist, ex2->falselist);
	}
	// backpatch(_goto1, l3);
	// backpatch(_goto2, l1);

	if ( s1 != nullptr ) {
		// backpatch(st1->nextlist,l2);
		// backpatch(st1->continuelist,l2);
		append(S->nextlist, s1->breaklist);
		append(S->caselist, s1->caselist);
		append(S->returnlist,s1->returnlist);
	}
	GoTo * _goto = create_new_goto(l2);
	return S;
}

// ------------------------------------------Jump Statements------------------------------------------
Statement* create_jump_statement_go_to(Identifier* id){
	JumpStatement *S=new JumpStatement();
	S->add_children({id});
	S->name = "GOTO";
	auto it = label_iden.find(id->value);
	if ( it == label_iden.end() ) {
		auto it = goto_iden.find(id->value);
		if(it == goto_iden.end()){
			GoTo * _goto = create_new_goto();
			std::vector<GoTo * > & vec = * new std::vector<GoTo * >;
			vec.push_back(_goto);
			goto_iden.insert({id->value, vec });
		}
		else{
			std::vector<GoTo *> & vec = it->second;
			GoTo * _goto = create_new_goto();
			vec.push_back(_goto);
		}
	}
	else {
		GoTo * _goto = create_new_goto( it->second );
	}
	return S;

}

Statement* create_jump_statement( int type_ ){
    JumpStatement *S = new JumpStatement();
    // token enums from "y.tab.c"
	if (type_ == CONTINUE){
		GoTo * _goto = create_new_goto();
		S->name="continue";
		S->continuelist.push_back(_goto);
	}
	else if(type_ == BREAK){
		GoTo * _goto = create_new_goto();
		S->name="break";
		S->breaklist.push_back(_goto);
	}
	else if (type_ == RETURN ) {
		S->name="return";
		// create_new_return(nullptr);
		GoTo * _goto = create_new_goto();
		S->returnlist.push_back(_goto);
	}
	return S;
}

Statement* create_jump_statement_exp(Expression* ex){
    JumpStatement *S = new JumpStatement();
	S->name="return expression";
	S->add_children({ex});
	if ( ex->type.invalid_type == nullptr && !local_symbol_table.return_type.isEqual(ex->type) ) {
		error_msg("Function expects return type of " + local_symbol_table.return_type.getType() + ". Got " + ex->type.getType(),line_num);
	}
	// create_new_return(ex->res);
	GoTo * _goto = create_new_goto();
	S->returnlist.push_back(_goto);
	return S;
}

// ------------------------------------------Labeled Statements------------------------------------------
Statement* create_labeled_statement_iden( Identifier *id, Label* l1, Statement* s1 ){
	LabeledStatement *S = new LabeledStatement();
	S->add_children({id, s1});
	S->name = "GOTO";
	auto it = label_iden.find( id->value );
	if (it == label_iden.end()){
		label_iden.insert({id->value, l1 });
	}
	else{
		error_msg("duplicate label " + id->value, id->line_num, id->column);
		return S;
	}
	auto it2 = goto_iden.find(id->value);
	if ( it2 != goto_iden.end() ) {
		// backpatch(it2->second,l1);
		it2->second.clear();
		goto_iden.erase(id->value);
	}
	return S;
}


Statement* create_labeled_statement_case(Constant *con,Label* l1,Statement* s1){
	IterationStatement *S = new IterationStatement();
	S->add_children({con, s1});
	S->name = "CASE";
	if (!type_specifiers[INT_T].isEqual(*con->constant_type.standard_type)) {
		error_msg("Case label not an integer constant.",con->line_num,con->column);
	}
	if (switch_type==NULL)
		{switch_type=&(con->constant_type);}
	std::string s="";
	if (type_specifiers[U_INT_T].isEqual(*con->constant_type.standard_type) && type_specifiers[INT_T].isEqual(*con->constant_type.standard_type)){
		s=con->value;
	}
	else if (type_specifiers[INT_T].isEqual(*con->constant_type.standard_type)){
		s=con->value;
	}
	auto it=switch_label.find(s);
	if (it!=switch_label.end()){
		error_msg("Duplicate case value",con->line_num,con->column);
	}
	else{
		switch_label.insert({s,l1});
	}
	//switch_temp=l;
	append(S->breaklist, s1->breaklist);
	append(S->nextlist,s1->nextlist);
	append(S->caselist, s1->caselist);
	append(S->returnlist,s1->returnlist);
	return S;
}

Statement* create_labeled_statement_def(Label* l1, Statement* s1){
	if(switch_temp!=NULL){
		// backpatch(s1->nextlist,switch_temp);
	}
	IterationStatement *S = new IterationStatement();
	S->add_children({s1});
	S->name = "DEFAULT";
	switch_label.insert({"",l1});
	append(S->nextlist, s1->breaklist);
	append(S->caselist, s1->caselist);
	//error_msg("case",s1->line_num);
	switch_temp=l1;
	append(S->breaklist, s1->breaklist);
	append(S->nextlist,s1->nextlist);
	append(S->caselist, s1->caselist);
	append(S->returnlist,s1->returnlist);
	return S;
} 


// ------------------------------------------Compound Statements------------------------------------------
Statement* create_compound_statement(std::string st, Statement* sl1 = nullptr, DeclarationList* dl1 = nullptr){
    // Unimplemented in reference file
	CompoundStatement *S = new CompoundStatement();
	S->add_children({sl1, dl1});
	S->name = "COMPOUND";
	return S;
}

void backpatch_fn( Statement * s ) {
	Label * l = create_new_label();
	// backpatch(s->returnlist,l);
	// backpatch(s->nextlist,l);
}