#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

class Expense {
public:
    int id;
    string category;
    double amount;
    string date;

    Expense(int id, const string& category, double amount, const string& date)
        : id(id), category(category), amount(amount), date(date) {}
};

void addExpense(vector<Expense>& expenses, int id, const string& category, double amount, const string& date) {
    expenses.emplace_back(id, category, amount, date);
    cout << "Expense added successfully!\n";
}

void viewExpenses(const vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "No expenses recorded yet.\n";
        return;
    }

    cout << setw(5) << "ID" << setw(15) << "Category" << setw(10) << "Amount" << setw(15) << "Date" << endl;
    cout << "---------------------------------------------------\n";
    for (const auto& expense : expenses) {
        cout << setw(5) << expense.id << setw(15) << expense.category << setw(10) << fixed << setprecision(2) << expense.amount << setw(15) << expense.date << endl;
    }
}

void deleteExpense(vector<Expense>& expenses, int id) {
    auto it = find_if(expenses.begin(), expenses.end(), [id](const Expense& e) {
        return e.id == id;
    });

    if (it != expenses.end()) {
        expenses.erase(it);
        cout << "Expense deleted successfully!\n";
    } else {
        cout << "Expense with ID " << id << " not found.\n";
    }
}

void summarizeExpenses(const vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "No expenses to summarize.\n";
        return;
    }

    map<string, double> categoryTotals;
    for (const auto& expense : expenses) {
        categoryTotals[expense.category] += expense.amount;
    }

    cout << "\nExpense Summary by Category:\n";
    for (const auto& pair : categoryTotals) {
        string category = pair.first;
        double total = pair.second;
        cout << category << ": $" << fixed << setprecision(2) << total << endl;
    }
}

void saveToFile(const vector<Expense>& expenses, const string& filename) {
    ofstream file(filename);
    for (const auto& expense : expenses) {
        file << expense.id << "," << expense.category << "," << expense.amount << "," << expense.date << "\n";
    }
    cout << "Expenses saved to file successfully!\n";
}

void loadFromFile(vector<Expense>& expenses, const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int id;
        string category, date;
        double amount;
        char delim;

        ss >> id >> delim;
        getline(ss, category, ',');
        ss >> amount >> delim;
        getline(ss, date);

        expenses.emplace_back(id, category, amount, date);
    }
    cout << "Expenses loaded from file successfully!\n";
}

void displayMenu() {
    cout << "\nPersonal Expense Tracker\n";
    cout << "1. Add Expense\n";
    cout << "2. View Expenses\n";
    cout << "3. Delete Expense\n";
    cout << "4. Summarize Expenses\n";
    cout << "5. Save Expenses to File\n";
    cout << "6. Load Expenses from File\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    vector<Expense> expenses;
    int choice, id = 1;
    string category, date, filename = "expenses.txt";
    double amount;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter category: ";
            cin >> category;
            cout << "Enter amount: ";
            cin >> amount;
            cout << "Enter date (YYYY-MM-DD): ";
            cin >> date;
            addExpense(expenses, id++, category, amount, date);
            break;
        case 2:
            viewExpenses(expenses);
            break;
        case 3:
            cout << "Enter expense ID to delete: ";
            cin >> id;
            deleteExpense(expenses, id);
            break;
        case 4:
            summarizeExpenses(expenses);
            break;
        case 5:
            saveToFile(expenses, filename);
            break;
        case 6:
            loadFromFile(expenses, filename);
            break;
        case 7:
            cout << "Thankyou you using me, Goodbye :) !\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
