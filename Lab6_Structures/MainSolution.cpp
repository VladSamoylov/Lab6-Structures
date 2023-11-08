#include "iostream"
#include "string"
#include "vector"
#include "list"
#include "ctime"
#include "chrono"
#include "map"

using namespace std;

/**
 * @brief Структура, яка містить інформацію про замовлення книги у бібліотеці
*/
struct Order {
	string surname_reader;
	string book_name;
	string autor;
	chrono::year_month_day date_order;
	chrono::year_month_day date_issuance;
	chrono::days time_waiting;

	void Get_Data() {
		cout << surname_reader << " | " << book_name << " | " << autor << " | " << date_order << " | " << date_issuance << " | " << chrono::sys_days{ date_issuance } - chrono::sys_days{ date_order } << endl;
	}
	chrono::days GetTimeofWaiting() {
		time_waiting = chrono::sys_days{ date_issuance } - chrono::sys_days{ date_order };
		return time_waiting;
	}
};

// Function For the First Task
int CheckIntValue(int*);
int CheckMinMembersOfOrder(int*);
int GetRandomNumber(int);
void FillLib(list<string>&, map<string, list<string>>&, string&);
void CreateLib(map<string, list<string>>&);
chrono::year_month_day GetRandomData(int&, int&);
chrono::days GetTimeOfWaiting(vector<Order>&, string&);
void FindMostFrequentReader(vector<Order>&, list<string>&);
void PercentageNotCompleteOrders(vector<Order>&);
void FillStructures(int*, map<string, list<string>>&, list<string>&, vector<Order>&);
int MenuOfSolution(int*);

/**
 * @brief Перевіряє коректне значення типу int, яке ввів користувач до системи
 * @param i Значення типу int введене з клавіатури
 * @return Повертає коректне значення для подальшої роботи системи
*/
int CheckIntValue(int* i) {

	cin.ignore(666, '\n');
	while (true) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(666, '\n');
			cout << "You enter wrong data! Please enter correct data: \n";
			cin >> *i;
		}
		else {
			return *i;
		}
	}
}

/**
 * @brief Перевіряє мінімальну кількість замовлень
 * @param n Кількість замовлень введенна користувачем з клавіатури
 * @return Повертає коректне значення кількості елементів замовлень
*/
int CheckMinMembersOfOrder(int* n) {

	if (*n <= 0) {
		cout << "You enter wrong data! Please enter correct data (min members - 1): \n";
		cin >> *n;
		*n = CheckIntValue(n);
	}
	return *n;
}

/**
 * @brief Створює колекцію за автором
 * @param current_list Поточний список назв книг
 * @param current_lib Поточна колекція книг
 * @param autor Поточний автор
*/
void FillLib(list<string>& current_list, map <string, list<string>>& current_lib, string& autor) {

	for (int i = 0; i < current_list.size(); i++) {
		list<string>::iterator it = next(current_list.begin(), i);
		current_lib[autor].push_back(*it);
	}
}

/**
 * @brief Заповнює каталог книг
 * @param lib Поточний каталог книг
*/
void CreateLib(map<string, list<string>>& lib) {
	list<string> rowling{ "Harry Potter and the Philosopher’s Stone", "Harry Potter and the Prisoner of Azkaban", "Harry Potter and the Chamber of Secrets",
		"Harry Potter and the Deathly Hallows", "Harry Potter and the Goblet of Fire","Harry Potter and the Order of the Phoenix", "Harry Potter and the Half-Blood Prince",
		"Harry Potter and the Cursed Child: Parts One and Two", "The Tales of Beedle the Bard", "Fantastic Beasts and Where to Find Them" };
	list<string>  martin{ "A Game of Thrones", "A Clash of Kings", "A Storm of Swords", "A Feast for Crows", "A Dance with Dragons", "Fire & Blood", "A Storm of Swords: Steel and Snow" };
	list<string> king{ "The Shining", "it", "The Stand", "Misery", "Carrie", "The Gunslinger","The Green Mile", "Mr. Mercedes", "Under the Dome", "The Institute", "The Dead Zone" };
	string autor_rowling = "J.K. Rowling";
	string autor_martin = "R.R. Martin";
	string autor_king = "Stephen King";

	FillLib(rowling, lib, autor_rowling);
	FillLib(martin, lib, autor_martin);
	FillLib(king, lib, autor_king);	
}

/**
 * @brief Шукає рандомне число
 * @param n Діапазон чисел від 0 до n-1
 * @return Повертає рандомне число
*/
int GetRandomNumber(int n) {
	int random;
	
	random = rand() % n;
	
	return random;
}

/**
 * @brief Створює рандомну дату
 * @param year_base Базовий рік від якого починається обчислення
 * @param date Максимальна кількість років для обчислення 
 * @return Повертає рандомну дату
*/
chrono::year_month_day GetRandomData(int& year_base, int& date) {
	
	chrono::year_month_day random_date;

	int day;
	int month = GetRandomNumber(12) + 1;
	date = GetRandomNumber(date + 1);
	int year = year_base + date;

	if (month == 2) {
		do {
			day = GetRandomNumber(29) + 1;
		} while ((day > 28 && day < 30) && year % 4 != 0);
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		day = GetRandomNumber(30) + 1;
	}
	else {
		day = GetRandomNumber(31) + 1;
	}
	random_date = chrono::year(year) / chrono::month(month) / chrono::day(day);

	return random_date;
}

/**
 * @brief Визначає середній час очікування замовлення
 * @param number_order Інформація про замовлення
 * @param current_surname Прізвище замовника 
 * @return Середній час очікування замовлення
*/
chrono::days GetTimeOfWaiting(vector<Order>& number_order, string& current_surname) {
	chrono::days time_waiting = chrono::days{ 0 };
	int amount_middle = 0;

	for (int i = 0; i < number_order.size(); i++) {
		if (number_order[i].surname_reader == current_surname) {
			time_waiting += number_order[i].GetTimeofWaiting();
			amount_middle++;
		}			
	}
	return time_waiting / amount_middle;
}

/**
 * @brief Шукає того, хто найчастіше замовляє книги
 * @param number_order Інформація про замовлення
 * @param surname Список всіх прізвищ замовників 
*/
void FindMostFrequentReader(vector<Order>& number_order, list<string>& surname) {
	
	int surname_listsize = surname.size();
	int* amount = new int[surname_listsize];
	int first_reader = 0, second_reader = 0, third_reader = 0;
	vector<string> first_surnames, second_surnames, third_surnames;
	list<string>::iterator sur;

	for (int i = 0; i < surname_listsize; i++) {
		amount[i] = 0;
	}
	for (int i = 0; i < number_order.size(); i++) {
		for (int j = 0; j < surname_listsize; j++) {
			list<string>::iterator itv = next(surname.begin(), j);
			if (*itv == number_order[i].surname_reader) {
				amount[j] += 1;
				break;
			}
		}
	}
	for (int i = 0; i < surname_listsize; i++) {
		cout << amount[i] << " | ";
	}
	cout << endl;
	for (int i = 0; i < surname_listsize; i++) {
		sur = next(surname.begin(), i);
		if (amount[i] > first_reader) {
			third_reader = second_reader;
			third_surnames = move(second_surnames);
			second_reader = first_reader;
			second_surnames = move(first_surnames);
			first_reader = amount[i];
			first_surnames.clear();
			first_surnames.push_back(*sur);
		}
		else if (amount[i] == first_reader) {
			first_surnames.push_back(*sur);
		}
		if (amount[i] > second_reader && amount[i] < first_reader) {
			third_reader = second_reader;
			third_surnames = move(second_surnames);
			second_reader = amount[i];
			second_surnames.clear();
			second_surnames.push_back(*sur);
		}
		else if (amount[i] == second_reader) {
			second_surnames.push_back(*sur);
		}
		if (amount[i] > third_reader && amount[i] < second_reader) {
			third_reader = amount[i];
			third_surnames.clear();
			third_surnames.push_back(*sur);
		}
		else if (amount[i] == third_reader) {
			third_surnames.push_back(*sur);
		}
	}
	cout << "\n----------------------------The most often orders books:----------------------------\n";
	if (!first_surnames.empty() && first_reader != 0) {
		cout <<"With order(s) "<< first_reader << " the fist place is/are taken: \n";
		for (string i : first_surnames) {
			chrono::days amount_waiting = GetTimeOfWaiting(number_order, i);
			cout << "! " << i << " with middle waiting: " << amount_waiting << endl;
		}
	}
	if (!second_surnames.empty() && second_reader != 0) {
		cout << "With order(s) " << second_reader << " the second place is/are taken: \n";
		for (string i : second_surnames) {
			chrono::days amount_waiting = GetTimeOfWaiting(number_order, i);
			cout << "! " << i << " with middle waiting: " << amount_waiting << endl;
		}
	}
	if (!third_surnames.empty() && third_reader != 0) {
		cout << "With order(s) " << third_reader << " the third place is/are taken: \n";
		for (string i : third_surnames) {
			chrono::days amount_waiting = GetTimeOfWaiting(number_order, i);
			cout << "! " << i << " with middle waiting: " << amount_waiting << endl;
		}
	}
}

/**
 * @brief Визначає, який відсоток замовлень не було успішно завершено.
 * @param number_order Інформація про замовлення
*/
void PercentageNotCompleteOrders(vector<Order>& number_order) {
	time_t t = time(0);
	tm now;
	localtime_s(&now, &t);
	chrono::year_month_day current_date = chrono::year(now.tm_year + 1900) / chrono::month(now.tm_mon + 1) / chrono::day(now.tm_mday);
	int amount_failed = 0;

	for (int i = 0; i < number_order.size(); i++) {
		if (number_order[i].date_issuance > current_date) {
			amount_failed++;
		}
	}
	if (amount_failed != 0) {
		cout << "\n Percentage of not complete orders is " << amount_failed * 100 / number_order.size() << '%' << endl;
	}
	else cout << "\n Not found of not complete orders" << endl;
}

/**
 * @brief Заповнює структуру інформацією про замовлення
 * @param n Кількість замовлень
 * @param lib Поточний каталог книг
 * @param surname Список всіх прізвищ замовників 
 * @param number_order Вектор структур, що містить в собі інформацію про замовлення
*/
void FillStructures(int* n, map<string, list<string>>& lib, list<string>& surname, vector<Order>& number_order) {
	
	time_t t = time(0);
	tm now;
	Order order;
	localtime_s(&now, &t);
	int date_now, year_base;	

	for (int i = 0; i < *n; i++) {
		list<string>::iterator it = next(surname.begin(), GetRandomNumber(surname.size()));
		order.surname_reader = *it;
		map<string, list<string>>::iterator its = next(lib.begin(), GetRandomNumber(3));
		order.autor = its->first;
		list<string>::iterator iti = next(its->second.begin(), GetRandomNumber(its->second.size()));
		order.book_name = *iti;
		order.date_order = GetRandomData(year_base = 2000, date_now = now.tm_year - 100);
		do {
			order.date_issuance = GetRandomData(year_base += date_now, date_now = 1);
		} while (order.date_issuance < order.date_order);
		number_order.push_back(order);
	}
	for (int i = 0; i < number_order.size(); i++) {
		number_order[i].Get_Data();
	}
}

/**
 * @brief Інтерфейс який дає змогу користувачу працювати з додатком
 * @param q Вибір виконуваного завдання, яке задається користувачем з клавіатури
 * @return Повертає сама себе для продовження роботи користувача з додатком
*/
int MenuOfSolution(int* q) {
	int n;
	map<string, list<string>> lib;
	list<string> surname{ "Rossi", "Russo", "Ferrari", "Esposito", "Bianchi", "Romano", "Colombo", "Ricci", "Gallo", "Lombardi" };
	vector<Order> number_order;

	srand(time(0));
	CreateLib(lib);
	switch (*q) {
	case 1:
		cout << "\n__Task A__\n";
		cout << "Enter n amount of Orders: ";
		cin >> n;
		n = CheckIntValue(&n);
		n = CheckMinMembersOfOrder(&n);
		FillStructures(&n, lib, surname, number_order);
		FindMostFrequentReader(number_order, surname);
		PercentageNotCompleteOrders(number_order);		
	case 2:
		cout << "\n__Task B__\n";
		
		break;
	default:
		cout << "\n__You don't enter any task for execution__\n";
		return 0;
	}
	return MenuOfSolution(q);
}

int main() {

	int q;
	cout << "\nCreated by Vladislav Samoilov / KNT - 223\n";

	cout << "--------Select task:--------\n";
	cout << "Task A) Identify The Symbol With Largest Code in the matrix - Enter 1\n";
	cout << "Task B) Determine How Many Times Given Letter Multiples Of 5 - Enter 2\n";
	cout << "------------------------------------------------------------\n";
	cin >> q;
	q = CheckIntValue(&q);
	MenuOfSolution(&q);

	return main();
}