#include <iostream>
#include <vector>
#include <cmath>
#include<Windows.h>
#include<algorithm>

using namespace std;

void error()
{
    cout << "������������ ������" << endl;
}

int main() {
    int n;

    do
    {
        cout << "Colichestvo veshei: "; // ���� ���������� �����
        cin >> n;
        // �������� �� ������������ �����
        cin.clear();
        cin.sync();
        cin.ignore(1000, '\n');
        if (cin.fail() || n <= 0)
            error();
    } while (n <= 0 || cin.fail());


    vector<double> weights(n);

    // ���� ����� �����
    cout << "Ves kagdoi veshi:\n";
    for (int i = 0; i < n; ++i) {
        do
        {
            cout << "Ves veshi  " << i + 1 << ": ";
            cin >> weights[i];

            cin.clear();
            cin.sync();
            cin.ignore(1000, '\n');
            if (cin.fail() || weights[i] <= 0)
                error();
        } while (weights[i] <= 0 || cin.fail());
    }

    // ���������� ����� ����� �� ��������
    sort(weights.rbegin(), weights.rend());

    double totalWeight = 0;

    // ���������� ������ ���� �����
    for (const auto& weight : weights) {
        totalWeight += weight;
    }

    double backpack1Weight = 0;
    double backpack2Weight = 0;

    // ������������� ����� �� ��������
    for (const auto& weight : weights) {
        if (backpack1Weight <= backpack2Weight) {
            backpack1Weight += weight;
        }
        else {
            backpack2Weight += weight;
        }
    }

    // ����� �����������
    cout << "Pykzak 1: " << backpack1Weight << " kg\n";
    cout << "Pykzak 2: " << backpack2Weight << " kg\n";

    // ����� ������� �����
    cout << "Paznitca vesov: " << fabs(backpack1Weight - backpack2Weight) << " kg\n";

    return 0;
}