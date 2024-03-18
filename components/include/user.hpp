#ifndef USER_H_
#define USER_H_

#include <iostream>
#include <sstream>
using namespace std;

class User {
private:
	static int next_id;
	int id { };
	string name;
	string email;
	string password;
	bool allowing_anonymous = true;


	void set_name(string name);
	void set_email(string email);
	void set_password(string password);
	void set_anonymous(bool anonymous);

public:
	User()=default;
	User(string name, string email, string password, bool allowing_anonymous);

	template<typename t>
	void update_information(int choice, t var);
	void view_information()const;

	void print_user()const;
	string get_name(){return this->name;}
	string get_password(){return this->password;}
	int get_id()const{return this->id;}
	bool get_anonymous()const{return allowing_anonymous;}
	string to_string();
	void from_string(string user);
	void static set_next_id(int id){next_id=id;};

};

#endif /* USER_H_ */
