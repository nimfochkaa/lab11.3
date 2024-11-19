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
    cout << "| №   | Назва товару          | Вартість одиниці | Кількість | Одиниця вимірювання     | Загальна вартість     |\n";
    cout << "----------------------------------------------------------------------------------------------------------------\n";
}

void printTableFooter() {
    cout << "================================================================================================================\n";
}

void inputProductData(Product& product) {
    cout << "Введіть назву товару: ";
    cin >> ws;
    cin.getline(product.name, 100);

    cout << "Введіть вартість одиниці товару в гривнях: ";
    cin >> product.unitPrice;

    cout << "Введіть кількість товару: ";
    cin >> product.quantity;

    cout << "Введіть одиницю вимірювання: ";
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
        cout << "Помилка відкриття файлу для запису.\n";
        return;
    }

    Product product;
    inputProductData(product);

    file.write(reinterpret_cast<char*>(&product), sizeof(Product));
    file.close();

    cout << "Товар додано до файлу " << filename << ".\n";
}

void displayProductsFromFile(const string& filename) {
    ifstream file(filename, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "Файл не знайдено або не вдалося відкрити.\n";
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
        cout << "Файл порожній.\n";
    }
    file.close();
}

void findProductByName(const string& filename, const string& name) {
    ifstream file(filename, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "Файл не знайдено або не вдалося відкрити.\n";
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
        cout << "Товар з назвою '" << name << "' не знайдено.\n";
    }
    file.close();
}
void displayProductsByPriceRange(const string& filename, double minPrice, double maxPrice) {
    ifstream file(filename, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "Файл не знайдено або не вдалося відкрити.\n";
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
        cout << "Товари у діапазоні " << minPrice << " - " << maxPrice << " грн не знайдено.\n";
    }
    file.close();
}

void mainMenu() {
    string filename;

    cout << "Вітаємо у програмі роботи з товарами!\n";

    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Вибрати файл для роботи\n";
        cout << "2. Додати новий товар\n";
        cout << "3. Переглянути список товарів\n";
        cout << "4. Пошук товару за назвою\n";
        cout << "5. Вивести товари у діапазоні вартості\n";
        cout << "6. Вийти\n";
        cout << "Виберіть опцію (1-6): ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Введіть ім'я файлу: ";
            cin >> filename;
            cout << "Вибрано файл: " << filename << "\n";
        }
        else if (choice == 2) {
            if (filename.empty()) {
                cout << "Спочатку виберіть файл.\n";
            }
            else {
                addProductToFile(filename);
            }
        }
        else if (choice == 3) {
            if (filename.empty()) {
                cout << "Спочатку виберіть файл.\n";
            }
            else {
                displayProductsFromFile(filename);
            }
        }
        else if (choice == 4) {
            if (filename.empty()) {
                cout << "Спочатку виберіть файл.\n";
            }
            else {
                string name;
                cout << "Введіть назву товару для пошуку: ";
                cin >> ws;
                getline(cin, name);
                findProductByName(filename, name);
            }
        }
        else if (choice == 5) {
            if (filename.empty()) {
                cout << "Спочатку виберіть файл.\n";
            }
            else {
                double minPrice, maxPrice;
                cout << "Введіть мінімальну вартість: ";
                cin >> minPrice;
                cout << "Введіть максимальну вартість: ";
                cin >> maxPrice;
                displayProductsByPriceRange(filename, minPrice, maxPrice);
            }
        }
        else if (choice == 6) {
            cout << "Дякуємо за використання програми!\n";
            break;
        }
        else {
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    mainMenu();
    return 0;
}


