#include "question.hpp"

long Question::next_id = 2000;

Question::Question(int from_id, int to_id, string question, long thread_id,
		bool anonymous) :
		from_id(from_id), to_id(to_id), thread_id(thread_id), anonymous(
				anonymous) {
	set_question(question);
	set_answer("");
	this->id = ++next_id;
}

void Question::set_answer(string answer) {
	this->answer = answer;
}

void Question::set_question(string question) {
	this->question = question;
}

void Question::answer_question(string answer) {

	if (this->answer != ""){
		print();
		cout << "your answer is updated :>\n\n";
	}

	set_answer(answer);
	print();
}

void Question::print(bool is_me /*false*/, bool to_me/*false*/) const {
	if (this->thread_id != -1) {
		cout << "Parent question id: " << this->thread_id << " -> ";
	}
	cout << "\tQuestion id " << this->id;
	if (!anonymous && is_me == false) {
		cout << " from user id: " << this->from_id;
	}
	if (to_me == false)
		cout << " to user id: " << this->to_id;
	cout << ": ( " << this->question << " )\n";
	if (this->answer != "") {
		cout << "\tAnswer : ( " << this->answer << " )\n";
	}
	cout << "\n";
}

pair<string, pair<string,string>> Question::to_string() {
	ostringstream ques;
	ques << this->from_id;
	ques << " ";
	ques << this->to_id;
	ques << " ";
	ques << this->id;
	ques << " ";
	ques << this->thread_id;
	ques << " ";
	ques << this->anonymous;
	if (this->answer == "") {
		this->set_answer("not answered yet");
	}
	pair<string, string> ques_str { ques.str(), this->answer };
	return { ques.str(), {this->question,this->answer} };
}

void Question::from_string(pair<string, pair<string,string>> ques) {
	if (ques.second.second != "not answered yet")
		this->set_answer(ques.second.second);
	this->set_question(ques.second.first);
	istringstream str(ques.first);
	str >> this->from_id;
	str >> this->to_id;
	str >> this->id;
	str >> this->thread_id;
	str >> this->anonymous;

}
















