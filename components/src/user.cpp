#include "user.hpp"

int User::next_id = 100;

User::User(string name, string email, string password,
		bool allowing_anonymous) {
	set_anonymous(allowing_anonymous);
	set_name(name);
	set_password(password);
	set_email(email);
	this->id = ++next_id;
}

void User::set_anonymous(bool anonymous) {
	this->allowing_anonymous = anonymous;
}

void User::set_email(string email) {
	this->email = email;
}

void User::set_name(string name) {
	this->name = name;
}
void User::set_password(string password) {
	this->password = password;
}

void User::view_information() const {
	cout << "your id is: " << this->id << "\nname: " << this->name << "\nemail:"
			<< this->email << "\nallowing anonymous: ";
	(this->allowing_anonymous == true) ? cout << "Yes\n\n" : cout << "No\n\n";
}

void User::print_user() const {
	cout << "user: " << this->name << "\tid:" << this->id << "\n\n";
}

template<>
void User::update_information(int choice, string var) {
	if (choice == 1)
		set_name(string(var));

	else if (choice == 2)
		set_email(var);

	else if (choice == 3) {
		set_password(var);
		cout << "your new password is:" << this->password << "\n\n";
	}

}
template<>
void User::update_information(int choice, bool var) {
	if (choice == 4)
		set_anonymous(var);
}

string User::to_string() {
	ostringstream user;
	user << id << " " << name<<" "<<email << " " << password << " " << allowing_anonymous;
	return user.str();
}

void User::from_string(string user) {
	istringstream string_user(user);
	int id { };
	string name;
	string email;
	string password;
	bool allow_anon;
	string_user >> id >> name >> email >> password >> allow_anon;
	this->id=id;
	this->set_name(name);
	this->set_email(email);
	this->set_password(password);
	this->set_anonymous(allow_anon);
}

