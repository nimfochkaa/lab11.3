#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

struct Product {
    char name[100];
    double unitPrice;
    int quantity;
    char unit[50];
};

void printTableHeader() {
    cout << "================================================================================================================\n";
    cout << "| �   | ����� ������          | ������� ������� | ʳ������ | ������� ����������     | �������� �������     |\n";
    cout << "----------------------------------------------------------------------------------------------------------------\n";
}

void printTableFooter() {
    cout << "================================================================================================================\n";
}

void inputProductData(Product& product) {
    cout << "������ ����� ������: ";
    cin >> ws;
    cin.getline(product.name, 100);

    cout << "������ ������� ������� ������ � �������: ";
    cin >> product.unitPrice;

    cout << "������ ������� ������: ";
    cin >> product.quantity;

    cout << "������ ������� ����������: ";
    cin >> ws;
    cin.getline(product.unit, 50);
}

void printProduct(const Product& product, int index) {
    double totalValue = product.unitPrice * product.quantity;
    cout << "| " << setw(3) << right << index + 1 << " ";
    cout << "| " << setw(22) << left << product.name
        << "| " << setw(17) << right << fixed << setprecision(2) << product.unitPrice << " "
        << "| " << setw(9) << right << product.quantity << " "
        << "| " << setw(23) << left << product.unit
        << "| " << setw(21) << right << fixed << setprecision(2) << totalValue << " |\n";
}

void addProductToFile(const string& filename) {
    ofstream file(filename, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "������� �������� ����� ��� ������.\n";
        return;
    }

    Product product;
    inputProductData(product);

    file.write(reinterpret_cast<char*>(&product), sizeof(Product));
    file.close();

    cout << "����� ������ �� ����� " << filename << ".\n";
}

void displayProductsFromFile(const string& filename) {
    ifstream file(filename, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "���� �� �������� ��� �� ������� �������.\n";
        return;
    }

    Product product;
    int index = 0;

    printTableHeader();
    while (file.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
        printProduct(product, index++);
    }
    printTableFooter();

    if (index == 0) {
        cout << "���� �������.\n";
    }
    file.close();
}

void findProductByName(const string& filename, const string& name) {
    ifstream file(filename, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "���� �� �������� ��� �� ������� �������.\n";
        return;
    }

    Product product;
    int index = 0;
    bool found = false;

    printTableHeader();
    while (file.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
        if (name == product.name) {
            printProduct(product, index);
            found = true;
        }
        index++;
    }
    printTableFooter();

    if (!found) {
        cout << "����� � ������ '" << name << "' �� ��������.\n";
    }
    file.close();
}
void displayProductsByPriceRange(const string& filename, double minPrice, double maxPrice) {
    ifstream file(filename, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "���� �� �������� ��� �� ������� �������.\n";
        return;
    }

    Product product;
    int index = 0;
    bool found = false;

    printTableHeader();
    while (file.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
        if (product.unitPrice >= minPrice && product.unitPrice <= maxPrice) {
            printProduct(product, index);
            found = true;
        }
        index++;
    }
    printTableFooter();

    if (!found) {
        cout << "������ � ������� " << minPrice << " - " << maxPrice << " ��� �� ��������.\n";
    }
    file.close();
}

void mainMenu() {
    string filename;

    cout << "³���� � ������� ������ � ��������!\n";

    while (true) {
        cout << "\n����:\n";
        cout << "1. ������� ���� ��� ������\n";
        cout << "2. ������ ����� �����\n";
        cout << "3. ����������� ������ ������\n";
        cout << "4. ����� ������ �� ������\n";
        cout << "5. ������� ������ � ������� �������\n";
        cout << "6. �����\n";
        cout << "������� ����� (1-6): ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "������ ��'� �����: ";
            cin >> filename;
            cout << "������� ����: " << filename << "\n";
        }
        else if (choice == 2) {
            if (filename.empty()) {
                cout << "�������� ������� ����.\n";
            }
            else {
                addProductToFile(filename);
            }
        }
        else if (choice == 3) {
            if (filename.empty()) {
                cout << "�������� ������� ����.\n";
            }
            else {
                displayProductsFromFile(filename);
            }
        }
        else if (choice == 4) {
            if (filename.empty()) {
                cout << "�������� ������� ����.\n";
            }
            else {
                string name;
                cout << "������ ����� ������ ��� ������: ";
                cin >> ws;
                getline(cin, name);
                findProductByName(filename, name);
            }
        }
        else if (choice == 5) {
            if (filename.empty()) {
                cout << "�������� ������� ����.\n";
            }
            else {
                double minPrice, maxPrice;
                cout << "������ �������� �������: ";
                cin >> minPrice;
                cout << "������ ����������� �������: ";
                cin >> maxPrice;
                displayProductsByPriceRange(filename, minPrice, maxPrice);
            }
        }
        else if (choice == 6) {
            cout << "������ �� ������������ ��������!\n";
            break;
        }
        else {
            cout << "������� ����. ��������� �� ���.\n";
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    mainMenu();
    return 0;
}


