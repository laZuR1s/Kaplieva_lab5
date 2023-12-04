#include <iostream>
#include<fstream>
#include<Windows.h>
#include<functional> 

int check_file(std::ifstream& file);
void ending(int n);
template <typename T, typename Predicat>
void Read_and_check(T& x, std::istream& stream, Predicat condition, const char* message);
int GetRandomInInterval(int a, int b);

int main_menu();
int choice_menu();



int main()
{
	SetConsoleOutputCP(1251);


}

int main_menu()
{
	std::cout << "\n--------------\n";
	std::cout << "\nМеню";
	std::cout << "\n1. Вычислить произведение положительных элементов массива\n";
	std::cout << "2. Вычислить сумму элементов массива, расположенных до первого минимального элемента\n";
	std::cout << "3. Упорядочить по возрастанию отдельно элементы, стоящие на четных местах, и элементы, стоящие на нечетных местах методом простого обмена\n";
	std::cout << "4. Завершить работу" << '\n';
	std::cout << "\n--------------\n";

	std::function<bool(int)> Lambda = [](int x)->bool
		{
			return x >= 1 && x <= 3;
		};
	int choice = 0;
	Read_and_check(choice, std::cin, Lambda, "\n-> ");
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return choice;
}

int choice_menu()
{
	std::cout << "\n--------------\n";
	std::cout << "\n1. Ввод чисел с клавиатуры" << '\n';
	std::cout << "2. Ввод чисел из файла" << '\n';
	std::cout << "3. Случайный набор чисел" << '\n';
	std::cout << "4. Выйти в главное меню" << '\n';
	std::cout << "\n--------------\n";

	std::function<bool(int)> Lambda = [](int x)->bool
		{
			return x >= 1 && x <= 4;
		};
	int choice = 0;
	Read_and_check(choice, std::cin, Lambda, "\n-> ");
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return choice;
}
int check_file(std::ifstream& file)
{
	int result = 1;
	if (!file)
		result = -1;
	else
		if (file.peek() == EOF) //==-1
			result = 0;

	return result;
}

void ending(int n)
{
	std::cout << "\nВведите " << n << " элемент";
	if (n < 21 && n>10)
		std::cout << "ов: ";
	else
	{
		switch (n % 10)
		{
		case 1:
			break;
		case 2:
		case 3:
		case 4:
			std::cout << "а: ";
			break;
		default:
			std::cout << "ов: ";
			break;

		}
	}
}

int GetRandomInInterval(int a, int b)
{
	return a + rand() % (b - a + 1);
}

template<typename T, typename Predicat>
void Read_and_check(T& x, std::istream& stream, Predicat condition, const char* message)
{
	std::cout << message;
	while (!(stream >> x && condition(x)))
	{
		std::cout << "Ошибка ввода!\n";
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cout << message;

	}
}
