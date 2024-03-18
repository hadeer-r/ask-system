#ifndef THREAD_HPP_
#define THREAD_HPP_

#include "question.hpp"
#include <vector>
#include <algorithm>

using std::vector;

class Thread {
private:
	Question parent_question;
	vector<Question> questions;


public:

	Thread( Question parent_question);

	void add_thread_question(const Question &question);
	void print_thread() const;
	void print_to_me(int to_id)const;
	void print_from_me(int from_id)const;
	bool answer(long question_id,string ans,bool parent);
	bool delete_question_from_thread(long question_id,int from_id);

	int get_parent_id()const {
		return parent_question.get_id();
	}
	int get_form_id_parent()const{return this->parent_question.get_from_id();}

	vector<pair<string, pair<string,string>>> thread_to_strings();

};

#endif /* THREAD_HPP_ */
