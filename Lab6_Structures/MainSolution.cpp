#include "iostream"
#include "string"
#include "vector"
#include "list"
#include "ctime"
#include "chrono"
#include "map"
#include "iomanip"
#include "cctype"

#define ANSI_COLOR_BLUE "\033[34m"
#define ANSI_COLOR_RESET "\033[0m"

using namespace std;

time_t t = time(0);
tm now;

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

/**
 * @brief Структура, яка містить інформацію про продаж товарів
*/
struct Sales {
	string product_name;
	int amount;
	float unit_cost;
	chrono::year_month_day sales_date;

	void GetInfo() {
		cout << setw(25) << product_name << " | " << setw(4) << amount << " | " << setw(8) << fixed << setprecision(2) << unit_cost << "$ | " << sales_date << endl;
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

void MenuOfSolution(int*);

// Function For the Second Task
float CheckFloatValue(float*);
float CheckFloatPositive(float*);
void EnterDate(int*, int*, int*);
void CheckDate(int*, int*, int*);
chrono::year_month_day CheckNoFutureSalesDate(chrono::year_month_day&, int*, int*, int*, bool);
void CreateCatalogGoods(map <string, list<string>>&);
bool CheckProductName(string&, map<string, list<string>>&);
void KeybordFillStructure(Sales*, int*, map<string, list<string>>&);
void FillStrucruresRandom(Sales*, int*, map<string, list<string>>&);
void GetTotalCostPrevYear(Sales*, int*);
void GetAmountProductForUserYear(Sales*, int*);
void IfSales(Sales*, int*);

// Function for the Lab 7 sort algorihms
void BubbleSort(Sales*, int*);
void GetSalesInfo(Sales*, int*);

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
			cin.ignore(666, '\n');
		}
		else {
			return *i;
		}
	}
}

/**
 * @brief Перевіряє мінімальну кількість замовлень
 * @param n Кількість замовлень введена користувачем з клавіатури
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
	localtime_s(&now, &t);
	chrono::year_month_day current_date = chrono::year(now.tm_year + 1900) / chrono::month(now.tm_mon + 1) / chrono::day(now.tm_mday);
	float amount_failed = 0;

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
*/
void MenuOfSolution(int* q) {
	int n;
	map<string, list<string>> lib, catalog;
	list<string> surname{ "Rossi", "Russo", "Ferrari", "Esposito", "Bianchi", "Romano", "Colombo", "Ricci", "Gallo", "Lombardi" };
	vector<Order> number_order;
	Sales* inform_mas;

	srand(time(0));
	CreateLib(lib);
	CreateCatalogGoods(catalog);
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
		break;
	case 2:
		cout << "\n__Task B__\n";
		cout << "Enter n amount of Sales: ";
		cin >> n;
		n = CheckIntValue(&n);
		n = CheckMinMembersOfOrder(&n);
		inform_mas = new Sales[n];
		KeybordFillStructure(inform_mas, &n, catalog);
		if (n > 2) {
			FillStrucruresRandom(inform_mas, &n, catalog);
		}
		GetTotalCostPrevYear(inform_mas, &n);
		GetAmountProductForUserYear(inform_mas, &n);
		IfSales(inform_mas, &n);
		BubbleSort(inform_mas, &n);
		GetSalesInfo(inform_mas, &n);
		delete[] inform_mas;
		break;
	default:
		cout << "\n__You don't enter any task for execution__\n";
		break;
	}
	if (*q == 1 || *q == 2) {
		MenuOfSolution(q);
	}	
}

int main() {
	int q;

	cout << "\nCreated by Vladislav Samoilov / KNT - 223\n";
	cout << "--------Select task:--------\n";
	cout << "Task A) Orders in the library - Enter 1\n";
	cout << "Task B) Information on the sale of products - Enter 2\n";
	cout << "------------------------------------------------------------\n";
	cin >> q;
	q = CheckIntValue(&q);
	MenuOfSolution(&q);	

	return main();
}

/**
 * @brief Структура, що використовується як буфер при сортуванні інформаційного масиву структури продажу товару
*/
struct SalesSortBuf {
	string product_name_buf;
	int amount_buf;
	float unit_cost_buf;
	chrono::year_month_day sales_date_buf;
};

/**
 * @brief Сортує інформаційний масив продажів за датою продажу, використовуючи алгоритм сортування обміном
 * @param inform_mas Інформаційний масив структури продажу товару
 * @param n Кількість фіскальних звітних чеків
*/
void BubbleSort(Sales* inform_mas, int* n) {
	SalesSortBuf buffer;
	int length = *n;

	cout << "\n____________________________________\n";
	cout << "Bubble Sorting is in progress..." << endl;
	while (length != 0) {
		int max_index = 0;
		for (int j = 0; j < length - 1; j++) {
			if (inform_mas[j].sales_date > inform_mas[j + 1].sales_date) {
				buffer.product_name_buf = inform_mas[j].product_name;
				buffer.amount_buf = inform_mas[j].amount;
				buffer.unit_cost_buf = inform_mas[j].unit_cost;
				buffer.sales_date_buf = inform_mas[j].sales_date;
				
				inform_mas[j].product_name = inform_mas[j + 1].product_name;
				inform_mas[j].amount = inform_mas[j + 1].amount;
				inform_mas[j].unit_cost = inform_mas[j + 1].unit_cost;
				inform_mas[j].sales_date = inform_mas[j + 1].sales_date;

				inform_mas[j + 1].product_name = buffer.product_name_buf;
				inform_mas[j + 1].amount = buffer.amount_buf;
				inform_mas[j + 1].unit_cost = buffer.unit_cost_buf;
				inform_mas[j + 1].sales_date = buffer.sales_date_buf;				
				max_index = j + 1;
			}
			else if ((inform_mas[j].sales_date == inform_mas[j + 1].sales_date)) {
				if (inform_mas[j].amount > inform_mas[j + 1].amount) {
					buffer.product_name_buf = inform_mas[j].product_name;
					buffer.amount_buf = inform_mas[j].amount;
					buffer.unit_cost_buf = inform_mas[j].unit_cost;
					buffer.sales_date_buf = inform_mas[j].sales_date;

					inform_mas[j].product_name = inform_mas[j + 1].product_name;
					inform_mas[j].amount = inform_mas[j + 1].amount;
					inform_mas[j].unit_cost = inform_mas[j + 1].unit_cost;
					inform_mas[j].sales_date = inform_mas[j + 1].sales_date;

					inform_mas[j + 1].product_name = buffer.product_name_buf;
					inform_mas[j + 1].amount = buffer.amount_buf;
					inform_mas[j + 1].unit_cost = buffer.unit_cost_buf;
					inform_mas[j + 1].sales_date = buffer.sales_date_buf;	
					max_index = j + 1;
				}
			}
		}
		length = max_index;
	}
}

/**
 * @brief Відображує інформацію, яку містить в собі інформаційний масив структури продажу товару
 * @param inform_mas Інформаційний масив структури продажу товару
 * @param n Кількість фіскальних звітних чеків
*/
void GetSalesInfo(Sales* inform_mas, int* n) {
	int count = 0;
	int n_count = 0;

	for (int i = 0; i < *n; i++) {
		bool once = true;
		for (int j = 0; j < *n; j++) {
			if ((inform_mas + i + j)->sales_date == (inform_mas + i + j + 1)->sales_date) {
				if (once) {
					cout << setw(25) << inform_mas[i + j].product_name << " | " << setw(4) << inform_mas[i + j].amount << " | " << setw(8) << fixed << setprecision(2) << inform_mas[i + j].unit_cost << "$ | " << ANSI_COLOR_BLUE << inform_mas[i + j].sales_date << ANSI_COLOR_RESET << endl;
					cout << setw(25) << inform_mas[i + j + 1].product_name << " | " << setw(4) << inform_mas[i + j + 1].amount << " | " << setw(8) << fixed << setprecision(2) << inform_mas[i + j + 1].unit_cost << "$ | " << ANSI_COLOR_BLUE << inform_mas[i + j + 1].sales_date << ANSI_COLOR_RESET << endl;
					once = false;
					n_count++;
				}
				else {
					cout << setw(25) << inform_mas[i + j + 1].product_name << " | " << setw(4) << inform_mas[i + j + 1].amount << " | " << setw(8) << fixed << setprecision(2) << inform_mas[i + j + 1].unit_cost << "$ | " << ANSI_COLOR_BLUE << inform_mas[i + j + 1].sales_date << ANSI_COLOR_RESET << endl;
					n_count++;
				}
				count++;
			}
			else {
				if (once) (inform_mas + i)->GetInfo(); n_count++;
				break;
			}			
		}
		i += count;
		count = 0;
	}
	cout << n_count << endl;
}

/**
 * @brief Встановлює значення в структурі з клавіатури
 * @param inform_mas Інформаційний масив структури продажу товару
 * @param n Кількість фіскальних звітних чеків
 * @param catalog Каталог товарів магазину 
*/
void KeybordFillStructure(Sales* inform_mas, int* n, map<string, list<string>>& catalog) {
	int day_sales = 0, month_sales = 0, year_sales = 0;
	chrono::year_month_day date_sale;
	int user_enter = 2;

	if (*n < user_enter) {
		user_enter = *n;
	}
	for (int i = 0; i < user_enter; i++) {
		cout << "Enter product name: ";
		getline(cin, inform_mas[i].product_name);
		if (!CheckProductName(inform_mas[i].product_name, catalog))
		{
			do {
				cout << "This product name wasn't found! Please Re-enter: ";
				getline(cin, inform_mas[i].product_name);
			} while (!CheckProductName(inform_mas[i].product_name, catalog));
		}
		cout << "Enter amount of sales: ";
		cin >> inform_mas[i].amount;
		inform_mas[i].amount = CheckIntValue(&inform_mas[i].amount);
		inform_mas[i].amount = CheckMinMembersOfOrder(&inform_mas[i].amount);
		cout << "Enter unit cost: ";
		cin >> inform_mas[i].unit_cost;
		inform_mas[i].unit_cost = CheckFloatValue(&inform_mas[i].unit_cost);
		inform_mas[i].unit_cost = CheckFloatPositive(&inform_mas[i].unit_cost);
		EnterDate(&day_sales, &month_sales, &year_sales);
		CheckDate(&day_sales, &month_sales, &year_sales);
		date_sale = chrono::year(year_sales) / chrono::month(month_sales) / chrono::day(day_sales);
		inform_mas[i].sales_date = CheckNoFutureSalesDate(date_sale, &day_sales, &month_sales, &year_sales, true);
	}
	for (int i = 0; i < user_enter; i++) {
		inform_mas[i].GetInfo();
	}
}

/**
 * @brief Автоматично встановлює значення в структурі 
 * @param inform_mas  Інформаційний масив структури продажу товару
 * @param n Кількість фіскальних звітних чеків
 * @param catalog Каталог товарів магазину
*/
void FillStrucruresRandom(Sales* inform_mas, int* n, map<string, list<string>>& catalog) {
	int year_base, date_now;
	chrono::year_month_day rnd_date;
	map<string, list<string>>::iterator it;
	localtime_s(&now, &t);

	for (int i = 2; i < *n; i++) {
		it = next(catalog.begin(), GetRandomNumber(catalog.size()));
		inform_mas[i].product_name = it->first;
		//(inform_mas + i)->product_name;
		inform_mas[i].amount = GetRandomNumber(10) + 1;
		inform_mas[i].unit_cost = (float)GetRandomNumber(500) + (float)GetRandomNumber(100) / 10 + (float)GetRandomNumber(100) / 100;
		rnd_date = GetRandomData(year_base = 2000, date_now = now.tm_year - 100);
		inform_mas[i].sales_date = CheckNoFutureSalesDate(rnd_date, 0, 0, 0, false);
		inform_mas[i].GetInfo();
	}
}

/**
 * @brief Визначає загальну вартість товарів, проданих за попередній рік
 * @param inform_mas Інформаційний масив структури продажу товару
 * @param n Кількість фіскальних звітних чеків
*/
void GetTotalCostPrevYear(Sales* inform_mas, int* n) {
	localtime_s(&now, &t);
	chrono::year_month_day current_date = chrono::year(now.tm_year + 1900 - 1) / chrono::month(now.tm_mon + 1) / chrono::day(now.tm_mday);
	chrono::year prev_year = chrono::year(now.tm_year + 1900 - 1);
	float total_cost = 0.0;

	for (int i = 0; i < *n; i++) {
		if (inform_mas[i].sales_date.year() == prev_year) {
			total_cost += inform_mas[i].unit_cost * inform_mas[i].amount;
		}
	}
	cout << "------------------------------------------------------\n";
	cout << "The total cost of goods sold for the previous year: " << total_cost << "$" << endl;
}

/**
 * @brief Визначає загальну і середню кількість кожного найменування товару, продану за заданий користувачем рік
 * @param inform_mas Інформаційний масив структури продажу товару
 * @param n Кількість фіскальних звітних чеків
*/
void GetAmountProductForUserYear(Sales* inform_mas, int* n) {
	localtime_s(&now, &t);
	int year = 0;
	chrono::year user_year;
	map<string, pair <int, int>> total_amount;

	cout << "Please enter a year to find the total amount of product: ";
	do {
		cin >> year;
		if (year < now.tm_year + 1850) {
			cout << "Minimum year to find is " << now.tm_year + 1850 << endl;
		}
		else if (year > now.tm_year + 1900) {
			cout << "You can't find for a future years!" << endl;
		}
	} while (year > now.tm_year + 1900 || year < now.tm_year + 1850);
	user_year = chrono::year(year);
	for (int i = 0; i < *n; i++) {
		if (inform_mas[i].sales_date.year() == user_year) {
			total_amount[inform_mas[i].product_name].first += inform_mas[i].amount;
			total_amount[inform_mas[i].product_name].second += 1;
		}
	}
	for (int i = 0; i < total_amount.size(); i++) {
		map<string, pair<int, int>>::iterator it = next(total_amount.begin(), i);
		cout << setw(25) << it->first << ": " << setw(6) << it->second.first << " total sold | the average amount of goods bought at a time: " << it->second.first / it->second.second << endl;
	}
}

/**
 * @brief Визначає, яким чином змінились би результати продажів, якщо б надавалася знижка у 10% при покупці більше 29$
 * @param inform_mas Інформаційний масив структури продажу товару
 * @param n Кількість фіскальних звітних чеків
*/
void IfSales(Sales* inform_mas, int* n) {
	float total_cost = 0, total_salecost = 0;

	for (int i = 0; i < *n; i++) {
		total_cost += inform_mas[i].unit_cost * inform_mas[i].amount;
		if (inform_mas[i].unit_cost * inform_mas[i].amount >= 30) {
			total_salecost += (inform_mas[i].unit_cost * inform_mas[i].amount) * 0.9;
		}
		else {
			total_salecost += inform_mas[i].unit_cost * inform_mas[i].amount;
		}
	}
	cout << "------------------------------------\n";
	cout << "The total revenue for all time: " << total_cost << "$" << endl;
	cout << "The total revenue for all time with 10% discount: " << total_salecost << "$" << endl;
	cout << "Income difference: " << total_salecost - total_cost << "$" << endl;
}

/**
 * @brief Забезпечує введення користувачем дати продажу  
 * @param day День продажу введений користувачем типу int
 * @param month Місяць продажу введений користувачем типу int
 * @param year Рік продажу введений користувачем типу int
*/
void EnterDate(int* day, int* month, int* year) {

	cout << "Enter day of sales: ";
	cin >> *day;
	*day = CheckIntValue(day);
	*day = CheckMinMembersOfOrder(day);
	cout << "Enter month of sales: ";
	cin >> *month;
	*month = CheckIntValue(month);
	*month = CheckMinMembersOfOrder(month);
	cout << "Enter year of sales: ";
	cin >> *year;
	*year = CheckIntValue(year);
	*year = CheckMinMembersOfOrder(year);
}

/**
 * @brief Перевіряє правильність введеної користувачем дати продажу
 * @param day День продажу введений користувачем типу int
 * @param month Місяць продажу введений користувачем типу int
 * @param year Рік продажу введений користувачем типу int
*/
void CheckDate(int* day, int* month, int* year) {

	localtime_s(&now, &t);
	if (*month > 12) {
		do {
			cout << "YOU enter wrong data for month! Please enter again: ";
			cin >> *month;
			*month = CheckIntValue(month);
			*month = CheckMinMembersOfOrder(month);
		} while (*month > 12);
	}
	if (*year > now.tm_year + 1900 || *year < now.tm_year + 1850) {
		do {
			cout << "YOU enter wrong data for year! Please enter again (ex. 2020): ";
			cin >> *year;
			*year = CheckIntValue(year);
			*year = CheckMinMembersOfOrder(year);
		} while (*year > now.tm_year + 1900 || *year < now.tm_year + 1850);
	}
	if (*month == 2 && ((*day == 29 && *year % 4 != 0) || *day > 28)) {
		do {
			cout << "This month have max days(28 or 29)! Please enter again: ";
			cin >> *day;
			*day = CheckIntValue(day);
			*day = CheckMinMembersOfOrder(day);
		} while ((*day > 28 && *day < 30) && *year % 4 != 0);
	}
	else if ((*month == 4 || *month == 6 || *month == 9 || *month == 11) && *day > 30) {
		do {
			cout << "This months have max 30 days! Please enter again: ";
			cin >> *day;
			*day = CheckIntValue(day);
			*day = CheckMinMembersOfOrder(day);
		} while (*day > 30);
	}
	else if (*day > 31) {
		do {
			cout << "This months have max 31 days! Please enter again: ";
			cin >> *day;
			*day = CheckIntValue(day);
			*day = CheckMinMembersOfOrder(day);
		} while (*day > 31);
	}
}

/**
 * @brief Перевіряє чи введене користувачем дата продажу не є майбутнього часу
 * @param target_date Дата продажу введена користувачем типу chrono
 * @param day День продажу введений користувачем типу int
 * @param month Місяць продажу введений користувачем типу int
 * @param year Рік продажу введений користувачем типу int
 * @param manual Перемикач, який вказує чи дата продажу введена користувачем чи системою
 * @return Коректну дату продажу товару до системи
*/
chrono::year_month_day CheckNoFutureSalesDate(chrono::year_month_day& target_date, int* day, int* month, int* year, bool manual) {
	localtime_s(&now, &t);
	chrono::year_month_day current_date = chrono::year(now.tm_year + 1900) / chrono::month(now.tm_mon + 1) / chrono::day(now.tm_mday);
	int year_base, date_now;

	if (target_date > current_date) {
		if (manual) {
			do {
				cout << "Error: enter future date of sales! Please enter present/past date of sales: \n";
				EnterDate(day, month, year);
				CheckDate(day, month, year);
				target_date = chrono::year(*year) / chrono::month(*month) / chrono::day(*day);
			} while (target_date > current_date);
		}
		else {
			do {
				target_date = GetRandomData(year_base = 2000, date_now = now.tm_year - 100);
			} while (target_date > current_date);
		}
	}

	return target_date;
}

/**
 * @brief Перевіряє коректне значення типу float, яке ввів користувач до системи
 * @param i  Значення типу float введене з клавіатури
 * @return Повертає коректне значення для подальшої роботи системи
*/
float CheckFloatValue(float* i) {

	cin.ignore(666, '\n');
	while (true) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(666, '\n');
			cout << "You enter wrong data! Please enter correct data: \n";
			cin >> *i;
			cin.ignore(666, '\n');
		}
		else {
			return *i;
		}
	}
}

/**
 * @brief Перевіряє чи введена користувачем ціна за товар є позитивна і більша 0
 * @param n Число ти float для перевірки
 * @return Коректне число для ціни товару
*/
float CheckFloatPositive(float* n) {

	if (*n <= 0) {
		cout << "You enter wrong data! Please enter correct data (min members - 0.01): \n";
		cin >> *n;
		*n = CheckFloatValue(n);
	}
	return *n;
}

/**
 * @brief Перевіряє, чи введений користувачем найменування товару є в каталозі товарів
 * @param check_string Найменування товару
 * @param catalog Поточний каталог
 * @return Повертає true, якщо таке найменування товару існує в каталозі товарів
*/
bool CheckProductName(string& check_string, map<string, list<string>>& catalog) {
	string correct_string;

	for (char& s : check_string) {
		s = tolower(s);
	}
	for (pair<string, list<string>> pair : catalog) {
		for (string it : pair.second) {
			if (it == check_string) {
				check_string = pair.first;
				return true;
			}
		}
	}
	return false;
}

/**
 * @brief Заповнює каталог товарів 
 * @param catalog Поточний каталог
*/
void CreateCatalogGoods(map <string, list<string>>& catalog) {
	string nintendo_switch = "Nintendo Switch";
	string nintendo_switchOLED = "Nintendo Switch OLED";
	string playstation3 = "Playstation 3 Fat";
	string playstation3_slim = "Playstation 3 Slim";
	string playstation3_sslim = "Playstation 3 SuperSlim";
	string playstation4 = "Playstation 4";
	string playstation4_slim = "Playstation 4 Slim";
	string playstation4_pro = "Playstation 4 Pro";
	string playstation5 = "Playstation 5";
	string steam_deck = "Steam Deck";
	list<string> playstation4_contraction{ "playstation 4", "ps4" };
	list<string> playstation4pro_contraction{ "playstation 4 pro", "ps4 pro", "ps4pro" };
	list<string> playstation4slim_contraction{ "playstation 4 slim", "ps4 slim", "ps4slim" };
	list<string> playstation3fat_contraction{ "playstation 3 fat", "ps3 fat", "ps3fat" };
	list<string> playstation3slim_contraction{ "playstation 3 slim", "ps3 slim", "ps3slim" };
	list<string> playstation3sslim_contraction{ "playstation 3 super slim", "playstation 3 ss", "ps3 ss", "ps3ss" };
	list<string> playstation5_contraction{ "playstation 5", "ps5" };
	list<string> nintendoswitch_contraction{ "nintendo switch", "switch" };
	list<string> nintendoswitchOLED_contraction{ "nintendo switch oled", "switch oled" };
	list<string> steamdeck_contraction{ "steam deck", "deck" };


	FillLib(playstation3fat_contraction, catalog, playstation3);
	FillLib(playstation3slim_contraction, catalog, playstation3_slim);
	FillLib(playstation3sslim_contraction, catalog, playstation3_sslim);
	FillLib(playstation4_contraction, catalog, playstation4);
	FillLib(playstation4slim_contraction, catalog, playstation4_slim);
	FillLib(playstation4pro_contraction, catalog, playstation4_pro);
	FillLib(playstation5_contraction, catalog, playstation5);
	FillLib(nintendoswitch_contraction, catalog, nintendo_switch);
	FillLib(nintendoswitchOLED_contraction, catalog, nintendo_switchOLED);
	FillLib(steamdeck_contraction, catalog, steam_deck);
}
