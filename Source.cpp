#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include<Windows.h>

struct Student {
    std::string name;
    std::vector<int> grades;
};

std::vector<Student> students;

// Функция для добавления нового ученика
void addStudent() {
    Student student;
    std::cout << "Введите имя ученика: ";
    std::getline(std::cin, student.name);
    students.push_back(student);
}

// Функция для добавления оценок для ученика
void addGrades() {
    std::string name;
    std::cout << "Введите имя ученика: ";
    std::getline(std::cin, name);

    for (auto& student : students) {
        if (student.name == name) {
            int grade;
            std::cout << "Введите оценку(-1 для завершения): ";
            while (std::cin >> grade && grade != -1) {
                student.grades.push_back(grade);
                std::cout << "Введите оценку(-1 для завершения): ";
            }
            break;
        }
    }
    std::cin.ignore();
}

// Функция для удаления ученика или оценок
void removeStudentOrGrades() {
    std::string name;
    std::cout << "Введите имя ученика: ";
    std::getline(std::cin, name);

    for (auto it = students.begin(); it != students.end(); ) {
        if (it->name == name) {
            int choice;
            std::cout << "Выберите: (1) Удалить учащегося (2) Удалить оценки: ";
            std::cin >> choice;
            if (choice == 1) {
                it = students.erase(it);
            }
            else if (choice == 2) {
                it->grades.clear();
                ++it;
            }
            else {
                ++it;
            }
        }
        else {
            ++it;
        }
    }
    std::cin.ignore();
}

// Функция для изменения оценки у ученика
void changeGrade() {
    std::string name;
    std::cout << "Введите имя ученика: ";
    std::getline(std::cin, name);

    for (auto& student : students) {
        if (student.name == name) {
            int index;
            std::cout << "Введите оценку: ";
            std::cin >> index;

            if (index >= 0 && index < student.grades.size()) {
                int newGrade;
                std::cout << "Введите новую оценку: ";
                std::cin >> newGrade;
                student.grades[index] = newGrade;
            }
            break;
        }
    }
    std::cin.ignore();
}

// Функция для расчета итоговой оценки у ученика или всех учеников
void calculateTotalGrade() {
    std::string name;
    std::cout << "Введите имя ученика: ";
    std::getline(std::cin, name);

    if (name == "all") {
        for (const auto& student : students) {
            int total = 0;
            for (int grade : student.grades) {
                total += grade;
            }

            double average = static_cast<double>(total) / student.grades.size();
            std::cout << "Студенты: " << student.name << ", Средний балл: " << std::fixed << std::setprecision(2) << average << std::endl;
        }
    }
    else {
        for (const auto& student : students) {
            if (student.name == name) {
                int total = 0;
                for (int grade : student.grades) {
                    total += grade;
                }

                double average = static_cast<double>(total) / student.grades.size();
                std::cout << "Студенты: " << student.name << ", Средний балл: " << std::fixed << std::setprecision(2) << average << std::endl;
                break;
            }
        }
    }
}

// Функция для сохранения изменений в файл
void saveChanges(const std::string& filename) {
    std::ofstream file(filename);

    if (file) {
        for (const auto& student : students) {
            file << student.name << " ";
            for (int grade : student.grades) {
                file << grade << " ";
            }
            file << std::endl;
        }
        std::cout << "Изменения сохранены!" << std::endl;
    }
    else {
        std::cout << "Ошибка сохранения изменений." << std::endl;
    }

    file.close();
}

// Функция для импорта из файла
void importFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (file) {
        students.clear();
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            Student student;
            iss >> student.name;
            int grade;
            while (iss >> grade) {
                student.grades.push_back(grade);
            }
            students.push_back(student);
        }
    }
    else {
        std::cout << "Ошибка импорта файла." << std::endl;
    }

    file.close();
}

// Функция для экспорта в файл
void exportToFile(const std::string& filename) {
    std::ofstream file(filename);

    if (file) {
        for (const auto& student : students) {
            file << student.name << " ";
            for (int grade : student.grades) {
                file << grade << " ";
            }
            file << std::endl;
        }
    }
    else {
        std::cout << "Ошибка экспорта" << std::endl;
    }

    file.close();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::string filename = "journal.txt";

    importFromFile(filename);

    int choice;
    do {
        std::cout << "Выберите функцию:" << std::endl;
        std::cout << "1. Добавить ученика" << std::endl;
        std::cout << "2. Добавить оценки" << std::endl;
        std::cout << "3. Удаление учащегося или оценки" << std::endl;
        std::cout << "4. Изменение оценки" << std::endl;
        std::cout << "5. Рассчитать среднюю оценку учащегося" << std::endl;
        std::cout << "6. Сохранить изменения в файл" << std::endl;
        std::cout << "0. Выйти" << std::endl;
        std::cout << "Выберите функцию: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            addGrades();
            break;
        case 3:
            removeStudentOrGrades();
            break;
        case 4:
            changeGrade();
            break;
        case 5:
            calculateTotalGrade();
            break;
        case 6:
            saveChanges(filename);
            break;
        case 0:
            exportToFile(filename);
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте ещё раз(" << std::endl;
            break;
        }

        std::cout << std::endl;
    } while (choice != 0);

    return 0;
}