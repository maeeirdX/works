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

// ������� ��� ���������� ������ �������
void addStudent() {
    Student student;
    std::cout << "������� ��� �������: ";
    std::getline(std::cin, student.name);
    students.push_back(student);
}

// ������� ��� ���������� ������ ��� �������
void addGrades() {
    std::string name;
    std::cout << "������� ��� �������: ";
    std::getline(std::cin, name);

    for (auto& student : students) {
        if (student.name == name) {
            int grade;
            std::cout << "������� ������(-1 ��� ����������): ";
            while (std::cin >> grade && grade != -1) {
                student.grades.push_back(grade);
                std::cout << "������� ������(-1 ��� ����������): ";
            }
            break;
        }
    }
    std::cin.ignore();
}

// ������� ��� �������� ������� ��� ������
void removeStudentOrGrades() {
    std::string name;
    std::cout << "������� ��� �������: ";
    std::getline(std::cin, name);

    for (auto it = students.begin(); it != students.end(); ) {
        if (it->name == name) {
            int choice;
            std::cout << "��������: (1) ������� ��������� (2) ������� ������: ";
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

// ������� ��� ��������� ������ � �������
void changeGrade() {
    std::string name;
    std::cout << "������� ��� �������: ";
    std::getline(std::cin, name);

    for (auto& student : students) {
        if (student.name == name) {
            int index;
            std::cout << "������� ������: ";
            std::cin >> index;

            if (index >= 0 && index < student.grades.size()) {
                int newGrade;
                std::cout << "������� ����� ������: ";
                std::cin >> newGrade;
                student.grades[index] = newGrade;
            }
            break;
        }
    }
    std::cin.ignore();
}

// ������� ��� ������� �������� ������ � ������� ��� ���� ��������
void calculateTotalGrade() {
    std::string name;
    std::cout << "������� ��� �������: ";
    std::getline(std::cin, name);

    if (name == "all") {
        for (const auto& student : students) {
            int total = 0;
            for (int grade : student.grades) {
                total += grade;
            }

            double average = static_cast<double>(total) / student.grades.size();
            std::cout << "��������: " << student.name << ", ������� ����: " << std::fixed << std::setprecision(2) << average << std::endl;
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
                std::cout << "��������: " << student.name << ", ������� ����: " << std::fixed << std::setprecision(2) << average << std::endl;
                break;
            }
        }
    }
}

// ������� ��� ���������� ��������� � ����
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
        std::cout << "��������� ���������!" << std::endl;
    }
    else {
        std::cout << "������ ���������� ���������." << std::endl;
    }

    file.close();
}

// ������� ��� ������� �� �����
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
        std::cout << "������ ������� �����." << std::endl;
    }

    file.close();
}

// ������� ��� �������� � ����
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
        std::cout << "������ ��������" << std::endl;
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
        std::cout << "�������� �������:" << std::endl;
        std::cout << "1. �������� �������" << std::endl;
        std::cout << "2. �������� ������" << std::endl;
        std::cout << "3. �������� ��������� ��� ������" << std::endl;
        std::cout << "4. ��������� ������" << std::endl;
        std::cout << "5. ���������� ������� ������ ���������" << std::endl;
        std::cout << "6. ��������� ��������� � ����" << std::endl;
        std::cout << "0. �����" << std::endl;
        std::cout << "�������� �������: ";
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
            std::cout << "�������� �����. ���������� ��� ���(" << std::endl;
            break;
        }

        std::cout << std::endl;
    } while (choice != 0);

    return 0;
}