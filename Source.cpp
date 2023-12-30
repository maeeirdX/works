#include <iostream>
#include <fstream>
#include<Windows.h>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string filename = "answers.txt";

    // ��������� ������ ������������ � ���������� � ����
    std::ofstream file;
    file.open(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cout << "������ ��� �������� �����" << std::endl;
        return 1;
    }

    std::string questions[8] = {
        "��� �������� ����������������?",
        "�� ������� � ������ ���������������� C++?",
        "��� �������� C++?",
        "�� ������ ������� � ����������� � ������� ����������������?",
        "��� �������� ������ ������� ������?",
        "�� ���������� ���������� ����� ��������?",
        "�� ������ �������� � ������� �������������?",
        "��� �������� ��������� ����� ��������� � ����������?"
    };

    std::string answers[8];

    for (int i = 0; i < 8; i++) {
        std::cout << questions[i] << " (��/���): ";
        std::cin >> answers[i];

        answers[i] = (answers[i] == "��" || answers[i] == "��" || answers[i] == "��") ? "��" : "���";

        file.write(answers[i].c_str(), 1);
    }

    file.close();
    std::cout << "������ �������� � ���� " << filename << std::endl;

    // ������������ ����� �������� ���� ������ ����� ��������� ������ ���������
    std::cout << "�� ������ �������� ���� ������? (��/���): ";
    std::string changeAnswer;
    std::cin >> changeAnswer;

    if (changeAnswer == "��" || changeAnswer == "��" || changeAnswer == "��") {
        file.open(filename, std::ios::out | std::ios::trunc);

        if (!file.is_open()) {
            std::cout << "������ ��� �������� �����" << std::endl;
            return 1;
        }

        for (int i = 0; i < 8; i++) {
            std::cout << questions[i] << " (��/���): ";
            std::cin >> answers[i];

            answers[i] = (answers[i] == "��" || answers[i] == "��" || answers[i] == "��") ? "��" : "���";

            file.write(answers[i].c_str(), 1);
        }

        file.close();
        std::cout << "���� ����� ������ �������� � ���� " << filename << std::endl;
    }

    return 0;
}