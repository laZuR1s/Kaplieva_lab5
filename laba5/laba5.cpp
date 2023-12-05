#include <iostream>
#include<fstream>
#include<Windows.h>
#include<functional> 

// Вспомогателььные функции
bool isFileWithContent(std::ifstream& file);
void ending(int n);
template <typename T, typename Predicat>
void Read_and_check(T& x, std::istream& stream, Predicat condition, const char* message);
int getRandomInInterval(int a, int b);
void print(int* arr, int size, const char* message);
void preamb(short choice, std::ifstream& file, int& size);

// Функции связанные с памятью, выделяемой для массивов
int* memory_allocation(int size);
void free_memory(int*& arr);

//Функции заполняющие массив элементами из cin/file или random
void fill(int* arr, int size, std::istream& stream = std::cin);
void fill(int* begin, int* end, int A, int B);

// TASK1 Вычислить произведение положительных элементов массива
bool task1(int* begin, int* end, int& product, std::function<bool(int)> predicate);

// TASK2 Вычислить сумму элементов массива, расположенных до первого минимального элемента
void findMinIndex(int* begin, int* end, int*& minIndex);
int task2(int* begin, int* end);

// TASK3 Упорядочить по возрастанию отдельно элементы, стоящие на четных местах, и элементы, стоящие на 
// нечетных местах методом простого обмена
void task3(int* arr, int size);

//Менюшки
int main_menu();
int choice_menu();

int main()
{
	SetConsoleOutputCP(1251);

	short mainChoice;
	do
	{
		mainChoice = main_menu();
		if (mainChoice != 4)
		{
			std::cout << "\nВыбран пункт меню: '" << mainChoice << "'\n";
			short choice;
			do
			{
				choice = choice_menu();
				if (choice != 4)
				{
					std::cout << "\nВыбран пункт меню: '" << choice << "'\n";
					int size;
					std::ifstream file("data.txt");
					preamb(choice, file, size);
					int* arr = memory_allocation(size);

					if (choice == 1)
					{
						ending(size);
						fill(arr, size, std::cin);
					}
					else if (choice == 2)
					{
						fill(arr, size, file);
						print(arr, size, "\nЭлементы массива: ");

					}
					else if (choice == 3)
					{
						int a, b;
						std::cout << "\nВведите диапазон рандома(от A до B): ";
						Read_and_check(a, std::cin, [](int x) {return true; }, "\n-> ");
						Read_and_check(b, std::cin, [](int x) {return true; }, "");
						std::cin.ignore(std::cin.rdbuf()->in_avail());
						fill(arr, arr + size, a, b);
						print(arr, size, "\nЭлементы массива: ");
					}

					if (mainChoice == 1)
					{
						int product;
						if (task1(arr, arr + size, product, [](int x) {return x > 0; }))
						{
							std::cout << "\nПроизведение положительных элементов: " << product << '\n';
						}
						else
							std::cout << "\nНет положительных элементов! " << '\n';
					}
					else if (mainChoice == 2)
					{
						std::cout << "\nСумма заданных элементов: " << task2(arr, arr + size) << '\n';
					}
					else if (mainChoice == 3)
					{
						task3(arr, size);
						print(arr, size, "\nОтсортированные по данному правилу элементы массива: ");
					}
					free_memory(arr);
				}
			} while (choice != 4);
			std::cout << "\nВыбран пункт меню: '" << choice << "'\n";

		}
	} while (mainChoice != 4);

}

bool task1(int* begin, int* end, int& product, std::function<bool(int)> predicate)
{
	bool isFind = false;
	product = 1;
	for (int* ptr = begin; ptr < end; ++ptr)
	{
		if (predicate(*ptr))
		{
			product = *ptr * product;
			isFind = true;
		}
	}
	return isFind;
}

void findMinIndex(int* begin, int* end, int*& minIndex)
{
	for (int* ptr = begin; ptr < end; ++ptr)
	{
		if (*ptr < *minIndex)
		{
			minIndex = ptr;
		}
	}
}

int task2(int* begin, int* end)
{
	int sum = 0;
	int* minIndex = begin;
	findMinIndex(begin, end, minIndex);
	for (int* ptr = begin; ptr < minIndex; ++ptr)
	{
		sum = sum + *ptr;
	}
	return sum;
}

void task3(int* arr, int size)
{
	bool isSorted;

	do
	{
		isSorted = true;
		for (int i = 0; i < size - 2; i++)
		{
			if (arr[i] > arr[i + 2])
			{
				int temp = arr[i];
				arr[i] = arr[i + 2];
				arr[i + 2] = temp;
				isSorted = false;
			}
		}
	} while (!isSorted);
}

int main_menu()
{
	std::cout << "\n--------------\n";
	std::cout << "\nМеню";
	std::cout << "\n1. Вычислить произведение положительных элементов массива\n";
	std::cout << "2. Вычислить сумму элементов массива, расположенных до первого минимального элемента\n";
	std::cout << "3. Упорядочить по возрастанию отдельно элементы, стоящие на четных местах и на нечетных местах методом простого обмена\n";
	std::cout << "4. Завершить работу" << '\n';
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

bool isFileWithContent(std::ifstream& file)
{
	int result = 1;
	if (!file)
	{
		result = -1;
		std::cout << "\nФайл не найден!\n";
	}
	else
		if (file.peek() == EOF) //==-1
		{
			result = 0;
			std::cout << "\nФайл пустой!\n";
		}

	return result == 1;
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
			std::cout << ": ";
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

int getRandomInInterval(int a, int b)
{
	return a + rand() % (b - a + 1);
}


int* memory_allocation(int size)
{
	return new int[size];
}

void free_memory(int*& arr)
{
	delete[]arr;
	arr = nullptr;
}

void print(int* arr, int size, const char* message)
{
	std::cout << message;
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << ' ';
	}
	std::cout << '\n';
}

void preamb(short choice, std::ifstream& file, int& size)
{
	if (choice == 1)
	{
		std::cout << " \nВведите количество элементов: ";
		Read_and_check(size, std::cin, [](int x) {return x > 0; }, "");
		std::cin.ignore(std::cin.rdbuf()->in_avail());
	}
	else
		if (choice == 2 && isFileWithContent(file))
		{
			file >> size;
		}
		else
		{
			std::cout << "\nВведите количество случайных слагаемых: ";
			Read_and_check(size, std::cin, [](int x) {return x > 0; }, "\n-> ");
			std::cin.ignore(std::cin.rdbuf()->in_avail());
		}
}

void fill(int* arr, int size, std::istream& stream)
{
	for (int i = 0; i < size; i++)
	{
		Read_and_check(arr[i], stream, [](int x) {return true; }, "");
	}
	std::cin.ignore(std::cin.rdbuf()->in_avail());
}

void fill(int* begin, int* end, int a, int b)
{
	for (int* ptr{ begin }; ptr < end; ++ptr)
	{
		*ptr = getRandomInInterval(a, b);
	}
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