#include "system.hpp"

bool Y_Or_N() {
	bool result = true;
	string a;
	do {
		cin >> a;
		if (a == "n" || a == "N") {
			return false;
			break;
		} else if (a == "y" || a == "Y") {
			return true;
			break;
		}
		cout << "\nWrong choice please try again:  ";
	} while (!(a == "y" || a == "Y" || a == "n" || a == "N"));
	return result;
}

int entry_menu() {
	cout
			<< "\t-------------Hello in our program!.. We are happy to see you ^-^-------------\n\n";
	cout << "press:\n1.log in\n2.sign up\n";

	int choice { };
	do {
		cin >> choice;
		if (choice == 1 || choice == 2)
			return choice;
		cout << "\nWrong choice please try again:  ";
	} while (!(choice == 1 || choice == 2));
	return choice;

}

int sign_up(Ask &Ask_) {
	cin.ignore();
	string name, email, password;
	bool allowing_anonymous = true;
	cout << "Enter your name: ";
	getline(cin, name);
	cout << "\nEnter your email: ";
	getline(cin, email);
	cout << "\nEnter password: ";
	getline(cin, password);
	cout << "do you want to request anonymous question? (y/n) ";
	string a;
	allowing_anonymous = Y_Or_N();

	cout << "\n\n";
	int user_id = Ask_.sign_up(name, email, password, allowing_anonymous);

	return user_id;
}
int log_in(Ask &Ask_) {
	string name, pass;
	cin.ignore();
	int user_id { };
	int cnt { };
	do {

		cout << "enter your name: ";
		getline(cin, name);
		cout << "\nenter your password";
		getline(cin, pass);

		user_id = Ask_.log_in(name, pass);
		cnt++;
		if (user_id != -1) {
			cout << "\t\t^^^^^you're logged in ^^^^^\n\n";
			break;
		}

		cout << "\n\ninvalid username or password...! please try again\n\n";

	} while (cnt < 5);
	if (user_id == -1) {
		cout
				<< "you have exceed the limit of trying..:(,\npress: 1.to sign_up\n2.to exit\n ";
		int ch { };
		cin >> ch;
		if (ch == 2) {
			return -1;
		}
		return sign_up(Ask_);
	}
	return user_id;

}

int user_menu() {
	cout << "______________________MENU______________________\n\n";
	cout
			<< "1.Edit information\n2.Print questions to me\n3.Print questions from me\n4.Ask question"
			<< "\n5.Answer question\n6.Delete question\n7.List All Users\n8.Print Feed\n9.log out\n10.exit\n\n";

	int choice { };
	do {
		cin >> choice;
		if (choice >= 1 && choice <= 10)
			return choice;
		cout << "\n\nInvalid choice..try again: ";

	} while (!(choice >= 1 && choice <= 10));
	return choice;

}

void ask_question(Ask &Ask_, int user_id) {
	int from_id = Ask_.get_user_id(user_id);
	int to_id { };
	string question;
	long thread_id { };

	int to_index { };
	do {
		cout << "\nEnter user id or -1 to cancel: ";
		cin >> to_id;
		if (to_id == -1)
			return;
		to_index = Ask_.find_user(to_id);
		if (to_index == -1) {
			cout << "\ninvalid user!..please try again or enter -1 to cancel\n";
		}

	} while (to_index == -1 && to_id != -1);

	cout << "do you want to ask question as anonymous (y/n) ";
	bool ask_unknown = Y_Or_N();

	if (Ask_.get_allowing_anonymous(to_index) == false && ask_unknown == true) {
		cout
				<< "this person donsen't allow anonymous quesion:\npress -1 to cancel or 1 to continue ";
		int con { };
		cin >> con;
		if (con == -1)

			return;
		ask_unknown = false;
	}

	cout << "\nEnter -1 for new question, or id of parent question of third";
	do {
		cin >> thread_id;
		int parent=Ask_.is_parent(thread_id);
		if (thread_id != -1 && parent==-1) {
			cout
					<< "\ninvalid parent's id! please try again or press -1 to cancel or 1 to try another id: \n";
			int ch;
			cin >> ch;
			if (ch == -1)
				return;
			else
				continue;
		}
		break;

	} while (true);

	cout << "Enter question: ";
	cin.ignore();
	getline(cin, question);
	cout << "\n";
	Ask_.ask(from_id, to_id, question, thread_id, ask_unknown);
}

void answer_question(Ask& Ask_){
	cout<<"Enter question id: ";
	int question_id{};
	cin>>question_id;
	string ans;
	cout<<"\nEnter your answer: ";
	cin.ignore();
	getline(cin,ans);
	bool is_exist=Ask_.answer_question(question_id,ans);
	if(!is_exist){
		cout<<"Invalid question id!...\n\n";
	}
	cout<<"\n\n";
}


void delete_question(Ask& Ask_, int user_id){

	cout<<"Enter question that you want to delete or -1 to cancel: ";

	int question_id;
	cin>>question_id;
	cout<<"\n";
	if(question_id==-1)
		return;
	if(Ask_.delete_quesion(question_id,user_id)){
		cout<<"your question is deleted\n";
		return;
	}
	cout<<"\nError!..Wrong question id OR you can't delete this question\n\n";

}



void run() {
	Ask Ask_;
	Ask_.read_users_from_file();
	Ask_.read_question();
	int user_id { };
	bool main_menu = false;
	int choice = entry_menu();
	if (choice == 1) {
		user_id = log_in(Ask_);
		if (user_id == -1)
			return;
	} else if (choice == 2) {
		user_id = sign_up(Ask_);
	}

	while (true) {
		if (main_menu) {
			int choice = entry_menu();
			if (choice == 1) {
				user_id = log_in(Ask_);
				if (user_id == -1)
					return;
			} else if (choice == 2) {
				user_id = sign_up(Ask_);
			}
			main_menu = false;
		}
		int ch_menu = user_menu();
		switch (ch_menu) {
		case 1: {
			Ask_.edit_information(user_id);
			break;
		}
		case 2: {
			Ask_.question_to_user(user_id);
			break;
		}
		case 3: {
			Ask_.question_from_user(user_id);
			break;
		}
		case 4: {
			ask_question(Ask_, user_id);
			break;
		}
		case 5: {
			answer_question(Ask_);
			break;
		}
		case 6: {
			delete_question(Ask_, user_id);
			break;
		}
		case 7: {
			Ask_.list_users();
			break;
		}
		case 8: {
			Ask_.feed();
			break;
		}
		case 9: {
			main_menu = true;
			break;
		}
		default: {
			Ask_.write_question();
			Ask_.write_users_in_file();
			return;
		}

		}
	}

}

