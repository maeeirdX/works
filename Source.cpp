#include <iostream>
#include <vector>
#include <queue>
#include<Windows.h>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // Запрашиваем размеры матрицы
    int n, m;
    std::cout << "Введите размеры матрицы (n и m): ";
    std::cin >> n >> m;

    // Создаем матрицу
    std::vector<std::vector<int>> matrix(n, std::vector<int>(m));

    // Заполняем матрицу случайными цветами
    std::vector<int> colors = { 1, 2, 3, 4, 5, 6, 7 };
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = colors[rand() % 7];
        }
    }

    // Вспомогательный массив для отслеживания пройденных ячеек
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));

    // Массив для хранения размеров областей
    std::vector<int> areas;

    // Обходим каждую ячейку матрицы
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // Если ячейка не посещена, начинаем новую область
            if (!visited[i][j]) {
                int color = matrix[i][j];
                int area = 0;
                // Используем очередь для поиска смежных ячеек одного цвета
                std::queue<std::pair<int, int>> q;
                q.push({ i, j });
                while (!q.empty()) {
                    int x = q.front().first;
                    int y = q.front().second;
                    q.pop();
                    // Проверяем смежные ячейки
                    if (x >= 0 && x < n && y >= 0 && y < m && !visited[x][y] && matrix[x][y] == color) {
                        visited[x][y] = true;
                        area++;
                        // Добавляем смежные ячейки в очередь
                        q.push({ x - 1, y });
                        q.push({ x + 1, y });
                        q.push({ x, y - 1 });
                        q.push({ x, y + 1 });
                    }
                }
                // Добавляем размер области в массив
                areas.push_back(area);
            }
        }
    }

    // Находим максимальную область
    int maxArea = 0;
    for (int i = 0; i < areas.size(); i++) {
        if (areas[i] > maxArea) {
            maxArea = areas[i];
        }
    }

    // Выводим результат
    std::cout << "Наибольшая область одинакового цвета: " << maxArea << std::endl;

    return 0;
}
