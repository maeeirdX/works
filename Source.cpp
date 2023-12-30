#include <iostream>
#include <vector>
#include <queue>
#include<Windows.h>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // ����������� ������� �������
    int n, m;
    std::cout << "������� ������� ������� (n � m): ";
    std::cin >> n >> m;

    // ������� �������
    std::vector<std::vector<int>> matrix(n, std::vector<int>(m));

    // ��������� ������� ���������� �������
    std::vector<int> colors = { 1, 2, 3, 4, 5, 6, 7 };
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = colors[rand() % 7];
        }
    }

    // ��������������� ������ ��� ������������ ���������� �����
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));

    // ������ ��� �������� �������� ��������
    std::vector<int> areas;

    // ������� ������ ������ �������
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // ���� ������ �� ��������, �������� ����� �������
            if (!visited[i][j]) {
                int color = matrix[i][j];
                int area = 0;
                // ���������� ������� ��� ������ ������� ����� ������ �����
                std::queue<std::pair<int, int>> q;
                q.push({ i, j });
                while (!q.empty()) {
                    int x = q.front().first;
                    int y = q.front().second;
                    q.pop();
                    // ��������� ������� ������
                    if (x >= 0 && x < n && y >= 0 && y < m && !visited[x][y] && matrix[x][y] == color) {
                        visited[x][y] = true;
                        area++;
                        // ��������� ������� ������ � �������
                        q.push({ x - 1, y });
                        q.push({ x + 1, y });
                        q.push({ x, y - 1 });
                        q.push({ x, y + 1 });
                    }
                }
                // ��������� ������ ������� � ������
                areas.push_back(area);
            }
        }
    }

    // ������� ������������ �������
    int maxArea = 0;
    for (int i = 0; i < areas.size(); i++) {
        if (areas[i] > maxArea) {
            maxArea = areas[i];
        }
    }

    // ������� ���������
    std::cout << "���������� ������� ����������� �����: " << maxArea << std::endl;

    return 0;
}
