#ifndef ASK_HPP_
#define ASK_HPP_

#include "thread.hpp"
#include "user.hpp"
#include <fstream>

class Ask {
private:
	vector<User> users;
	vector<Thread> threads;

public:
	Ask() = default;

	int log_in(string name,string password);
	int sign_up(string name,string email,string password,bool allowing_anonymous);

	void ask(int from_id, int to_id, string question,long thread_id,bool anonymous);
	bool delete_quesion(long question_id,int index_user);
	bool answer_question(long quesion_id,string ans);

	void list_users();
	void feed();

	void question_to_user(int user_id)const;
	void question_from_user(int user_id)const;
	void edit_information(int user_id);
	int find_user(int to_id);
	int get_user_id(int index)const{return this->users[index].get_id();}
	bool get_allowing_anonymous(int user_id)const {return this->users[user_id].get_anonymous();}
	void write_users_in_file();
	void read_users_from_file();
	int is_parent(int parent_id)const;
	void write_question();
	void read_question();
	int static get_next_question_id(){return Question::get_next_id();}




};

#endif /* ASK_HPP_ */
