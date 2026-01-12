#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>  
#include "functional.h"

void input_question(vector<string>& questions, vector<string>& answers, int& question_index) {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    using namespace std;
    
    string question;
    cin.ignore();
    cout << "Введите вопрос: ";
    
    do {
        getline(cin, question);
        if (question.empty()) {
            cout << "Ошибка: Вопрос не может быть пустым!" << endl;
            cout << "Введите вопрос: ";
        }
    } while (question.empty());

    // проверяем чтобы вопросы не повторялись
    bool flag = false;
    for (int i = 0; i < questions.size(); i++) {
        if (question == questions[i]) {
            question_index = i;
            if (i < answers.size() && !answers[i].empty()) {
                cout << "Этот вопрос уже существует " << endl;
                cout << "Ответ: " << answers[i] << endl;
            } else {
                cout << "На него еще нет ответа." << endl;
            }
            flag = true;
            break;
        }
    }
    
    if (!flag) {
        questions.push_back(question);
        question_index = questions.size() - 1;
        cout << "Новый вопрос добавлен, номер: " << question_index + 1 << endl;
        input_answer(questions, answers, question_index);
    }
}

bool input_file_question(vector<string>& questions, vector<string>& answers, const string& file_name) {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    using namespace std;
    
    ifstream file(file_name);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла " << file_name << " !" << endl;
        return false;
    }

    string line;
    bool condition_question = true;
    string current_question, current_answer;
    int questions_before = questions.size();
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        if (condition_question) {
            current_question = line;
            condition_question = false;
        } else {
            current_answer = line;
            
            // Проверяем повторяется ли вопрос
            bool exists = false;
            for (int i = 0; i < questions.size(); i++) {
                if (current_question == questions[i]) {
                    if (i < answers.size()) {
                        answers[i] = current_answer;
                    }
                    exists = true;
                    break;
                }
            }
            
            if (!exists) {
                questions.push_back(current_question);
                if (answers.size() < questions.size()) {
                    answers.resize(questions.size(), "");
                }
                answers[questions.size() - 1] = current_answer;
            }
            
            condition_question = true;
        }
    }
    

    if (!condition_question && !current_question.empty()) {
        questions.push_back(current_question);
        if (answers.size() < questions.size()) {
            answers.resize(questions.size(), "");
        }
        cout << "Из файла был добавлен(ы) вопрос(ы) без ответа(ов)" << endl; 
    }

    int loaded_count = questions.size() - questions_before;
    cout << "Загружено вопросов из файла: " << loaded_count << endl;

    if(loaded_count == 0){
        cout << "Файл " << file_name << " пустой!" << endl;
        cout << "Запишите в файл вопросы с ответами (в первой строке вопрос, в следующей ответ)" << endl;
        return false;
    }

    return true;
}

void input_answer(vector<string>& questions, vector<string>& answers, int& question_index) {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    using namespace std;

    string answer;
    cout << "Введите ответ для вопроса: ";

    do {
        getline(cin, answer);
        if (answer.empty()) {
            cout << "Ошибка: Ответ не может быть пустым!" << endl;
            cout << "Введите ответ для вопроса: ";
        }
    } while (answer.empty());

    if (answers.size() <= question_index) {
        answers.resize(question_index + 1, "");
    }
    
    answers[question_index] = answer;
    
    cout << "Ответ добавлен!" << endl;
    cout << question_index + 1 << " Вопрос: " << questions[question_index] << endl;
    cout << question_index + 1 << " Ответ: " << answers[question_index] << endl;
}

void output_all_questions(vector<string>& questions, vector<string>& answers, int& question_index) {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    using namespace std;
    
    if (questions.empty()) {
        int choice;
        
        cout << "\n1. Ввести через консоль" << endl;
        cout << "2. Ввести из файла" << endl;
        cout << "0. Назад" << endl;
        cout << "Введите выбор: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "ОШИБКА: Некорректный ввод!" << endl;
            return;
        }
        
        cin.ignore();
        
        switch(choice) {
            case 1:
                input_question(questions, answers, question_index);
                break;
            case 2: {
                string file_name;
                cout << "\n^ Для коректного ввода вопросов и ответов из файла строго соблюдайте порядок:\nв первой строке ответ в следующей ответ на вопрос! ^" << endl;
                cout << "\nВведите имя файла: ";
                
                do {
                    getline(cin, file_name);
                    if (file_name.empty()) {
                        cout << "ОШИБКА: Имя файла не может быть пустым!" << endl;
                        cout << "Введите имя файла: ";
                    }
                } while (file_name.empty());
                
                bool uploaded_successfully = input_file_question(questions, answers, file_name);
                
                if(!uploaded_successfully){
                    cout << "Не удалось загрузить вопросы из файла." << endl;
                }
                break;
            }
            case 0:
                break;
            default:
                cout << "\nНеверный выбор!" << endl;
        }
        return;
    }

    cout << "\nВсе доступные вопросы (с ответами): " << endl;
    cout << "__________________________________" << endl;
    for (int i = 0; i < questions.size(); i++) {
        cout << i + 1 << ". Вопрос: " << questions[i] << endl;
        cout << "   Ответ: ";
        if (i < answers.size() && !answers[i].empty()) {
            cout << answers[i];
        } else {
            cout << "(нет ответа)";
        }
        cout << endl;
    }

    int choice1;
    do{
        if(!questions.empty()){
            cout << "\nДобавить еще вопрос? (1 - да / 0 - нет): ";
            if (!(cin >> choice1)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "ОШИБКА: Некорректный ввод!" << endl;
                choice1 = 0;
            } else {
                cin.ignore();
                switch(choice1){
                    case 1: 
                        input_question(questions, answers, question_index);
                        break;
                    case 0:
                        cout << "\nВсе вопросы введены!"<< endl;
                        break;
                    default:
                        cout << "\nОШИБКА: Неверный выбор!" << endl;
                        choice1 = 1;
                }
            }
        }
    } while(choice1 != 0);
}

void edit_question(vector<string>& questions, vector<string>& answers, int& question_index) {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    using namespace std;
    
    if (questions.empty()) {
        cout << "Нет вопросов для редактирования!" << endl;
        return;
    }
    
    int number;
    cout << "\nВведите номер вопроса для редактирования (0 - отмена): ";
    cin >> number;
    
    if (number == 0) return;
    
    cin.ignore();
    question_index = number - 1;

    if (question_index >= 0 && question_index < questions.size()) {
        cout << "Текущий вопрос: " << questions[question_index] << endl;
        cout << "Введите новый текст вопроса: ";
        string new_question;
        
        do {
            getline(cin, new_question);
            if (new_question.empty()) {
                cout << "Ошибка: Вопрос не может быть пустым!" << endl;
                cout << "Введите новый текст вопроса: ";
            }
        } while (new_question.empty());
        
        questions[question_index] = new_question;
        cout << "Вопрос успешно обновлен!" << endl;
    } else {
        cout << "Неверный номер вопроса!" << endl;
        cout << "Доступные номера: 1-" << questions.size() << endl;
    }
}

void edit_answer(vector<string>& questions, vector<string>& answers, int& question_index) {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    using namespace std;

    if (questions.empty()) {
        cout << "Нет вопросов для редактирования ответов!" << endl;
        return;
    }
    
    int number;
    cout << "\nВведите номер вопроса для редактирования ответа (0 - отмена): ";
    cin >> number;
    
    if (number == 0) return;
    
    cin.ignore();
    question_index = number - 1;

    if (question_index >= 0 && question_index < questions.size()) {
        cout << "Вопрос: " << questions[question_index] << endl;
        cout << "Текущий ответ: ";
        if (question_index < answers.size() && !answers[question_index].empty()) {
            cout << answers[question_index];
        } else {
            cout << "(нет ответа)";
        }
        cout << endl;
        
        cout << "Введите новый ответ: ";
        string new_answer;
        
        do {
            getline(cin, new_answer);
            if (new_answer.empty()) {
                cout << "Ошибка: Ответ не может быть пустым!" << endl;
                cout << "Введите новый ответ: ";
            }
        } while (new_answer.empty());
        
        if (answers.size() <= question_index) {
            answers.resize(question_index + 1, "");
        }
        answers[question_index] = new_answer;
        cout << "Ответ успешно обновлен!" << endl;
    } else {
        cout << "Неверный номер Ответа!" << endl;
    }
}

void delete_question(vector<string>& questions, vector<string>& answers, int& question_index) {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    using namespace std;
    
    if (questions.empty()) {
        cout << "Нет вопросов для удаления!" << endl;
        return;
    }
    
    int number;
    cout << "\nВведите номер вопроса для удаления (0 - отмена): ";
    cin >> number;
    
    if (number == 0) {
        cout << "Удаление отменено." << endl;
        return;
    }

    cin.ignore();
    question_index = number - 1;

    if (question_index >= 0 && question_index < questions.size()) {
        string deleted_question = questions[question_index];
        string deleted_answer = "";
        
        if (question_index < answers.size()) {
            deleted_answer = answers[question_index];
        }
        
        questions.erase(questions.begin() + question_index);
        if (question_index < answers.size()) {
            answers.erase(answers.begin() + question_index);
        }
        
        cout << "Удален вопрос: " << deleted_question << endl;
        if (!deleted_answer.empty()) {
            cout << "Ответ: " << deleted_answer << endl;
        }
        cout << "Осталось вопросов: " << questions.size() << endl;
    } else {
        cout << "Неверный номер вопроса!" << endl;
    }
}

// Функция для dialog, переводящая русские и английские буквы в нижней регистр
char simplify_question_text(char c) {

    if (c >= 'А' && c <= 'Я') {
        return c + 32; // В Windows-1251 русские строчные буквы начинаются с 32 позиции
    }
    else if (c == 'Ё') {
        return 'ё';
    }
    else if (c >= 'A' && c <= 'Z') {
        return tolower(c);
    }
    return c;
}

void dialog(vector<string>& questions, vector<string>& answers, int& question_index) {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    using namespace std;
    
    if (questions.empty()) {
        cout << "Нет вопросов для диалога! Сначала добавьте вопросы" << endl;
        return;
    }

    output_all_questions(questions, answers, question_index);

    cout << "_________________________" << endl;
    cout << "\n ^ ДИАЛОГ С БОТОМ ^" << endl;
    cout << "Для выхода введите 0" << endl;
    cout << "Можно вводить текст вопроса или его номер" << endl;
    cout << "Доступно вопросов: " << questions.size() << endl;
    cout << "_________________________" << endl;
    
    while (true) {
        string input;
        cout << "\nВы: ";
        
        while (true) {
            getline(cin, input);
            if (!input.empty()) {
                break;
            }
            cout << "БОТ: Вы ничего не ввели, попробуйте снова" << endl;
            cout << "Вы: ";
        }
        
        if (input == "0") {
            cout << "Выход из диалога" << endl;
            break;
        }
        
        // Далее проверяем введен вопрос или его номер

        bool number_condition = true;
        
        for (char c : input) {
            if (!isdigit(c)) {
                number_condition = false;
                break;
            }
        }
        
        if (number_condition) {

            int number = 0;
            bool conversion_condition = true;
            
            for (char c : input) {
                if (c >= '0' && c <= '9') {
                    int digit = c - '0';
                    
                    // Проверка на переполнение int перед умножением
                    // Если number > (INT_MAX / 10), то number * 10 > INT_MAX
                    if (number > INT_MAX / 10) {
                        conversion_condition = false;
                        break;
                    }
                    number = number * 10;
                    
                    // Проверка на переполнение int перед сложением
                    // Если number > (INT_MAX - digit), то number + digit > INT_MAX
                    if (number > INT_MAX - digit) {
                        conversion_condition = false;
                        break;
                    }
                    number = number + digit;
                } else {
                    conversion_condition = false;
                    break;
                }
            }
            
            if (conversion_condition) {
                if (number >= 1 && number <= questions.size()) {
                    question_index = number - 1;
                    
                    cout << "БОТ: ";
                    if (question_index < answers.size() && !answers[question_index].empty()) {
                        cout << answers[question_index] << endl;
                    } else {
                        cout << "Ответа на этот вопрос нет" << endl;
                    }
                } else {
                    cout << "БОТ: Вопроса с номером " << number << " не существует!" << endl;
                    cout << "Доступные номера: 1-" << questions.size() << endl;
                }
            } else {
                cout << "БОТ: Некорректный номер (слишком большое число)!" << endl;
            }
        } else {
            /* если пользователь ввел текст вопроса, то нужно поработать с пользовательскими привычками, 
            а именно 1 игнорированием пунктуации 2 неиспользованием заглавных букв

            если вопрос в базе и введенный пользователем текст различаются только этими двумя пунктами
            то вывод ошибки о несуществовании введенного вопроса некорректен, поэтому будем приводить
            вопросы к "нормальному" виду:
            - без знаков препинания
            - все буквы в нижнем регистре

            Ищем такой же вопрос в базе (также приведенный в "нормальный" вид)*/

            string normalized_input = "";
            for (char c : input) {
                if (c != '?' && c != '!' && c != '.' && c != ',')
                    normalized_input += simplify_question_text(c); 
            }

            bool flag = false;
            for (int i = 0; i < questions.size(); i++) {
                string normalized_question = "";
                for (char c : questions[i]) {
                    if (c != '?' && c != '!' && c != '.' && c != ',')
                        normalized_question += simplify_question_text(c); 
                }
                
                if (normalized_input == normalized_question) {
                    cout << "БОТ: ";
                    if (i < answers.size() && !answers[i].empty())
                        cout << answers[i] << endl;
                    else
                        cout << "Ответа нет\n";
                    flag = true;
                    break;
                }
            }
            
            if (!flag) {
                cout << "БОТ: Такого вопроса нет в базе" << endl;
                cout << "Хотите добавить этот вопрос? (1 - да / 0 - нет): ";
                string choice;
                
                while (true) {
                    getline(cin, choice);
                    
                    if (!choice.empty() && choice.length() == 1 && isdigit(choice[0])) {
                        int num = choice[0] - '0';
                        if (num == 0 || num == 1) {
                            break;
                        }
                    }
                    cout << "Ошибка: Введите 0 или 1!" << endl;
                }
                
                int choice_number = choice[0] - '0';
                
                if (choice_number == 1) {
                    questions.push_back(input);
                    question_index = questions.size() - 1;
                    cout << "БОТ: Вопрос добавлен! Теперь введите ответ на него" << endl;
                    input_answer(questions, answers, question_index);
                } 
            }
        }
    }
}