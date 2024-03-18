#include "ask.hpp"

int Ask::log_in(string name, string password) {
	int sz = (int) users.size();
	for (int i = 0; i < sz; i++) {
		if (users[i].get_name() == name
				&& users[i].get_password() == password) {
			return i;
		}
	}
	return -1;
}

int Ask::sign_up(string name, string email, string password,
		bool allowing_anonymous) {
	User new_user(name, email, password, allowing_anonymous);
	this->users.push_back(new_user);
	return (int) this->users.size() - 1;
}

void Ask::edit_information(int user_id) {
	cout << "\n";
	this->users[user_id].view_information();
	cout
			<< "press to edit:\n\t1.name\n\t2.email\n\t3.password\n\t4.your status for allowing anonymous question\n\t5.go back\n\n";

	int choice { };
	do {
		cin >> choice;
		if (choice == 5)
			return;
		if (choice <= 4 && choice >= 1) {
			switch (choice) {
			case 1: {
				cout << "Enter updated name: ";
				string name;
				cin.ignore();
				getline(cin, name);
				cout << "\nyour name is update :)\n\n";
				users[user_id].update_information(choice, name);
				break;
			}
			case 2: {
				cout << "Enter updated email: ";
				string email;
				cin.ignore();
				getline(cin, email);
				cout << "\nyour email is update :)\n\n";
				users[user_id].update_information(choice, email);
				break;
			}
			case 3: {
				cout << "Enter updated password: ";
				string password;
				cin.ignore();
				getline(cin, password);
				cout << "\nyour password is update :)\n\n";
				users[user_id].update_information(choice, password);
				break;
			}
			case 4: {
				cout << "Enter (y/n) ";
				bool allowing_anonymous;
				string a;
				do {
					cin >> a;
					if (a == "n" || a == "N") {
						allowing_anonymous = false;
						break;
					} else if (a == "y" || a == "Y") {
						allowing_anonymous = true;
						break;
					}
					cout << "\nWrong choice please try again:  ";
				} while (!(a == "y" || a == "Y" || a == "n" || a == "N"));
				users[user_id].update_information(choice, allowing_anonymous);
				break;
			}
			}
			break;
		}
		cout << "Invalid choice..!try again: ";
	} while (!(choice <= 4 && choice >= 1));
	users[user_id].view_information();

}

void Ask::ask(int from_id, int to_id, string question, long thread_id,
		bool anonymous) {
	Question q(from_id, to_id, question, thread_id, anonymous);
	if (thread_id == -1) {
		Thread th(q);
		threads.push_back(th);
		return;
	}
	int sz = (int) threads.size();
	for (int i = 0; i < sz; i++) {
		if (thread_id == threads[i].get_parent_id()) {
			threads[i].add_thread_question(q);
			return;
		}
	}
}

int Ask::find_user(int to_id) {
	int sz = (int) users.size();
	for (int i = 0; i < sz; i++) {
		if (users[i].get_id() == to_id) {
			return i;

		}
	}
	return -1;
}

void Ask::question_to_user(int user_id) const {
	for (auto th : this->threads) {

		th.print_to_me(this->users[user_id].get_id());
	}
}
void Ask::question_from_user(int user_id) const {
	for (auto th : this->threads) {
		th.print_from_me(users[user_id].get_id());
	}
}
void Ask::list_users() {
	for (auto u : users) {
		u.print_user();
	}
	cout << "\n\n";
}

void Ask::feed() {
	for (auto th : this->threads) {
		th.print_thread();
	}
}

void Ask::write_users_in_file() {
	string file = "../src/users.txt";
	ofstream file_users(file);
	if (file_users.fail()) {
		cout << "\ncan't open file\n";
		return;
	}
	int sz = (int) this->users.size();
	file_users << sz << "\n\n";
	for (auto u : users) {
		string str = u.to_string();
		file_users << str << "\n";
	}
	file_users.close();
}

void Ask::read_users_from_file() {
	string file = "../src/users.txt";
	ifstream file_users(file);
	if (file_users.fail()) {
		cout << "\ncan't open file\n";
		return;
	}
	int sz;
	file_users >> sz;
	string str { "" };
	string line { "" };
	getline(file_users, line);
	getline(file_users, line);
	for (int i = 0; i < sz; i++) {

		getline(file_users, str);

		User user;
		user.from_string(str);
		this->users.push_back(user);
		if (i == sz - 1) {
			User::set_next_id(user.get_id());
		}
	}

	file_users.close();
}

int Ask::is_parent(int parent_id) const {
	int sz=(int)this->threads.size();
	for (int i=0;i<sz;i++) {
		if (this->threads[i].get_parent_id() == parent_id) {
			return i;
		}
	}
	return -1;
}

bool Ask::answer_question(long question_id,string ans){
	int parent=this->is_parent(question_id);
	if(parent!=-1){
		this->threads[parent].answer(question_id,ans,true);
		return true;
	}

	else if(parent==-1)
	{
		for(auto &th:this->threads){
			if(th.answer(question_id,ans,false))
				return true;
		}
	}
	return false;

}


bool Ask::delete_quesion(long question_id,int index_user){
	int from_id=this->users[index_user].get_id();
	int parent=this->is_parent(question_id);
	if(parent==-1){
		for(auto &th:this->threads){
			if(th.delete_question_from_thread(question_id,from_id)){
				return true;
			}
		}
		return false;
	}
	for (auto it = this->threads.begin(); it != this->threads.end();) {

			if ((*it).get_parent_id() == question_id && (*it).get_form_id_parent() == from_id) {
				it = this->threads.erase(it);
				return true;
			} else
				++it;
		}
		return false;
}


void Ask::write_question() {
	string file="../src/questions.txt";
	ofstream file_ques(file);
	if (file_ques.fail()) {
		cout << "\ncan't open file\n";
		return;
	}
	file_ques << Ask::get_next_question_id() << "\n\n";
	file_ques << (int) this->threads.size() << "\n\n";

	vector<pair<string, pair<string, string>>> th_str;

	for (auto th : this->threads) {

		th_str = th.thread_to_strings();
		int sz_questions = (int) th_str.size();

		for (int i = 0; i < sz_questions; i++) {
			if (!i)
				file_ques << sz_questions - 1 << "\n";
			file_ques << th_str[i].first << "\n" << th_str[i].second.first
					<< "\n" << th_str[i].second.second << "\n\n";
		}
	}
	file_ques.close();
}

void Ask::read_question() {
	string file="../src/questions.txt";
	ifstream file_ques(file);
	int next_id;
	file_ques >> next_id;
	Question::set_next_id(next_id);
	string line { "" };
	getline(file_ques, line);
	getline(file_ques, line);

	string ids { "" };
	string ques { "" };
	string ans { "" };

	int sz_thread;
	file_ques >> sz_thread;

	for (int i = 0; i < sz_thread; i++) {

		getline(file_ques, line);

		int sz_questions;
		file_ques >> sz_questions;

		Question parent;
		getline(file_ques, line);
		getline(file_ques, ids);
		getline(file_ques, ques);
		getline(file_ques, ans);
		parent.from_string( { ids, { ques, ans } });

		Thread new_thread(parent);


		for (int j = 0; j < sz_questions; j++) {
			getline(file_ques, line);

			getline(file_ques, ids);
			getline(file_ques, ques);
			getline(file_ques, ans);

			Question thread_question;
			thread_question.from_string( { ids, { ques, ans } });
			new_thread.add_thread_question(thread_question);

		}
		this->threads.push_back(new_thread);
	}

}

