#include <iostream>
#include <vector>
#include <string>
#include <windows.h>  
#include "functional.h"

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    using namespace std;

    vector<string> questions;
    vector<string> answers;
    int question_index = -1;
    
    int choice;
    do {
        cout << "\n ^ МЕНЮ БОТА ^ " << endl;
        cout << "1. Ввести вопросы" << endl;
        cout << "2. Вывести все вопросы" << endl;
        cout << "3. Разыграть диалог" << endl;
        cout << "0. Выход" << endl;
        
        bool flag_choice = false;
        while (!flag_choice) {
            cout << "Введите выбор: ";
            
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "ОШИБКА: Некорректный ввод! Введите число от 0 до 3" << endl;
                continue;
            }
            
            if (choice < 0 || choice > 3) {
                cout << "ОШИБКА: Число должно быть от 0 до 3!" << endl;
                cin.ignore(1000, '\n');
                continue;
            }
            
            flag_choice = true;
        }
        
        cin.ignore(); 
        
        switch(choice) {
            case 1:
                output_all_questions(questions, answers, question_index);
                break;

            case 2:
                if (questions.empty()) {
                    cout << "\nНет доступных вопросов!" << endl;
                    output_all_questions(questions, answers, question_index);
                    if(questions.empty()){
                        break;
                    }
                }
                else{
                    output_all_questions(questions, answers, question_index);
                    int choice1;
                    cout << "\n^ ДЕЙСТВИЯ С ВОПРОСАМИ/ОТВЕТАМИ ^" << endl;
                    cout << "1. Редактировать вопрос" << endl;
                    cout << "2. Редактировать ответ на вопрос" << endl;
                    cout << "3. Удалить вопрос" << endl;
                    cout << "0. Назад" << endl;
                    cout << "Введите выбор: ";
                    
                    
                    bool valid_choice1 = false;
                    while (!valid_choice1) {
                        if (!(cin >> choice1)) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "ОШИБКА: Некорректный ввод! Введите число от 0 до 3: ";
                            continue;
                        }
                        
                        if (choice1 < 0 || choice1 > 3) {
                            cout << "ОШИБКА: Число должно быть от 0 до 3! Попробуйте снова: ";
                            cin.ignore(1000, '\n');
                            continue;
                        }
                        
                        valid_choice1 = true;
                    }
                    
                    cin.ignore();
                    
                    switch(choice1) {
                        case 1:
                            edit_question(questions, answers, question_index);
                            break;
                        case 2:
                            edit_answer(questions, answers, question_index);
                            break;
                        case 3:
                            delete_question(questions, answers, question_index);
                            break;
                        case 0:
                            break;
                        default:
                            cout << "\nНеверный выбор!" << endl;
                    }
                }
                break;

            case 3:
                dialog(questions, answers, question_index);
                break;
                
            case 0:
                cout << "\nДосвидания! буду ждать следующей встречи с вами!" << endl;
                cout << "\n_______________________";
                cout << "\n|  |______|______|_____|";
                cout << "\n|  |                |  |";
                cout << "\n|--|  _/|___/|      |  |";
                cout << "\n|  | | O ^ O |  *** |--|";
                cout << "\n|__|__//__//_|__*|*_|  |";
                cout << "\n|_____|______|______|__| :>";
                break;
                
            default:
                cout << "\nНеверный выбор! Попробуйте еще раз." << endl;
        }
        
        if (choice != 0) {
            cout << "\nНажмите Enter для продолжения...";
            cin.ignore();
            cin.get();
        }
        
    } while (choice != 0);

    return 0;
}