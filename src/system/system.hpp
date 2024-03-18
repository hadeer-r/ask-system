#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_
#include "ask.hpp"

int entry_menu();
int sign_up(Ask& Ask_);
int log_in(Ask& Ask_);

int user_menu();

void ask_question(Ask &Ask_,int user_id);
void answer_question(Ask& Ask_);
void delete_question(Ask& Ask_);

void run();

#endif /* SYSTEM_HPP_ */
