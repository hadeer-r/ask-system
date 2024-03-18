#include "thread.hpp"

Thread::Thread(Question parent_question) :
		parent_question(parent_question) {
}

void Thread::add_thread_question(const Question &question) {
	this->questions.push_back(question);
}

void Thread::print_thread() const {
	int sz = (int) questions.size();

	if (sz == 0) {
		this->parent_question.print();
		return;
	}

	this->parent_question.print();
	cout << "{\n";
	for (int i = 0; i < sz; i++)
		this->questions[i].print();
	cout << "}\n\n";
}

bool Thread::answer(long question_id, string ans, bool parent) {
	if (parent == true) {
		this->parent_question.answer_question(ans);
		return true;
	}
	int sz = (int) questions.size();
	for (int i = 0; i < sz; i++) {
		if (this->questions[i].get_id() == question_id) {
			this->questions[i].answer_question(ans);
			return true;
		}
	}
	return false;
}

void Thread::print_from_me(int from_id) const {
	cout << this->parent_question.get_from_id() << "\n";
	if (this->parent_question.get_from_id() == from_id)
		this->parent_question.print(true);

	for (auto q : this->questions) {
		if (q.get_from_id() == from_id)
			q.print(true);
	}
	cout << "\n";
}

void Thread::print_to_me(int to_id) const {
	if (this->parent_question.get_to_id() == to_id)
		this->parent_question.print(false, true);
	for (auto q : this->questions) {
		if (q.get_to_id() == to_id)
			q.print(false, true);
	}
	cout << "\n";
}

vector<pair<string, pair<string, string>>> Thread::thread_to_strings() {
	vector<pair<string, pair<string, string>>> thread_strings;
	thread_strings.push_back(this->parent_question.to_string());
	for (auto q : this->questions) {
		thread_strings.push_back(q.to_string());
	}
	return thread_strings;
}

bool Thread::delete_question_from_thread(long question_id,int from_id) {

	for (auto it = this->questions.begin(); it != this->questions.end();) {
		if ((*it).get_from_id() == from_id && (*it).get_id() == question_id) {
			it = this->questions.erase(it);
			return true;
		} else
			++it;

	}
	return false;
}

