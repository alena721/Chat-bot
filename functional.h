#ifndef FUNCTIONAL_H 
#define FUNCTIONAL_H

#include <vector>
#include <string>

using namespace std;


void input_question(vector<string>& questions, vector<string>& answers, int& question_index);
bool input_file_question(vector<string>& questions, vector<string>& answers, const string& file_name);
void input_answer(vector<string>& questions, vector<string>& answers, int& question_index);
void output_all_questions(vector<string>& questions, vector<string>& answers, int& question_index);
void edit_question(vector<string>& questions, vector<string>& answers, int& question_index);
void edit_answer(vector<string>& questions, vector<string>& answers, int& question_index);
void delete_question(vector<string>& questions, vector<string>& answers, int& question_index);
char simplify_question_text(char c);
void dialog(vector<string>& questions, vector<string>& answers, int& question_index);

#endif