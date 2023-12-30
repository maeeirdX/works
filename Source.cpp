#include <iostream>
#include <fstream>
#include<Windows.h>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string filename = "answers.txt";

    // Считываем ответы пользователя и записываем в файл
    std::ofstream file;
    file.open(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Ошибка при открытии файла" << std::endl;
        return 1;
    }

    std::string questions[8] = {
        "Вам нравится программирование?",
        "Вы знакомы с языком программирования C++?",
        "Вам нравится C++?",
        "Вы готовы учиться и развиваться в области программирования?",
        "Вам нравится решать сложные задачи?",
        "Вы эффективно управляете своим временем?",
        "Вы готовы работать в команде разработчиков?",
        "Вам нравится создавать новые программы и приложения?"
    };

    std::string answers[8];

    for (int i = 0; i < 8; i++) {
        std::cout << questions[i] << " (да/нет): ";
        std::cin >> answers[i];

        answers[i] = (answers[i] == "да" || answers[i] == "Да" || answers[i] == "ДА") ? "да" : "нет";

        file.write(answers[i].c_str(), 1);
    }

    file.close();
    std::cout << "Ответы записаны в файл " << filename << std::endl;

    // Пользователь может изменить свои ответы после окончания работы программы
    std::cout << "Вы хотите изменить свои ответы? (да/нет): ";
    std::string changeAnswer;
    std::cin >> changeAnswer;

    if (changeAnswer == "да" || changeAnswer == "Да" || changeAnswer == "ДА") {
        file.open(filename, std::ios::out | std::ios::trunc);

        if (!file.is_open()) {
            std::cout << "Ошибка при открытии файла" << std::endl;
            return 1;
        }

        for (int i = 0; i < 8; i++) {
            std::cout << questions[i] << " (да/нет): ";
            std::cin >> answers[i];

            answers[i] = (answers[i] == "да" || answers[i] == "Да" || answers[i] == "ДА") ? "да" : "нет";

            file.write(answers[i].c_str(), 1);
        }

        file.close();
        std::cout << "Ваши новые ответы записаны в файл " << filename << std::endl;
    }

    return 0;
}