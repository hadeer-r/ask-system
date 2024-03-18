#ifndef QUESTION_HPP_
#define QUESTION_HPP_

#include <iostream>
#include <sstream>
using namespace std;


class Question {
private:
	long static next_id;
	int from_id{};
	int to_id{};
	string question;
	string answer;
	long id { };
	long thread_id{};
	bool anonymous=false;


	void set_question(string question);
	void set_answer(string answer);

public:
	Question()=default;
	Question(int from_id, int to_id, string question,long thread_id,bool anonymous);

	void answer_question(string answer);
	void print(bool is_me=false,bool to_me=false)const;
	long get_id()const{return id;}
	int get_to_id()const{return to_id;}
	int get_from_id()const{return from_id;}
	int static get_next_id(){return next_id;}
	pair<string, pair<string,string>> to_string();
	void from_string(pair<string, pair<string,string>> ques);
	void static set_next_id(int id){next_id=id;};


};

#endif /* QUESTION_HPP_ */
