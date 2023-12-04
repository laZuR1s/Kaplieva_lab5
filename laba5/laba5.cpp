#include <iostream>
#include<fstream>
#include<Windows.h>
#include<functional> 

int check_file(std::ifstream& file);
void ending(int n);
template <typename T, typename Predicat>
void Read_and_check(T& x, std::istream& stream, Predicat condition, const char* message);
int GetRandomInInterval(int a, int b);
bool fileInput(std::ifstream& file);

int* memory_allocation(int size);
void free_memory(int*& arr);
void print(int* arr, int size);

void fill(int* arr, int size, std::istream& stream = std::cin);
void fill(int* begin, int* end, int A, int B);

bool task1(int* arr, int size, int& product, std::function<bool(int)> predicate);

int findMinIndex(int* arr, int size);
int task2(int* arr, int size);


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
			short choice;
			do
			{
				choice = choice_menu();
				if (choice != 4)
				{
					if (choice == 1)
					{
						std::cout << " \nВведите количество элементов: ";
						int size;
						Read_and_check(size, std::cin, [](int x) {return x > 0; }, "");
						std::cin.ignore(std::cin.rdbuf()->in_avail());

						int* arr = memory_allocation(size);
						ending(size);
						fill(arr, size, std::cin);

						if (mainChoice == 1)
						{
							int product;
							if (task1(arr, size, product, [](int x) {return x > 0; }))
							{
								std::cout << "\nПроизведение положительных элементов: " << product << '\n';
							}
							else
								std::cout << "\nНет положительных элементов! " << '\n';
							free_memory(arr);
						}

						if (mainChoice == 2)
						{
							std::cout << "\nСумма заданных элементов: " << task2(arr, size)<<'\n';
						}

						if (mainChoice == 3)
						{

						}
					}

					if (choice == 2)
					{
						std::ifstream file("data.txt");
						if (fileInput(file))
						{
							int size;
							file >> size;
							int* arr = memory_allocation(size);
							fill(arr, size, file);
							print(arr, size);

							if (mainChoice == 1)
							{
								int product;
								if (task1(arr, size, product, [](int x) {return x > 0; }))
								{
									std::cout << "\nПроизведение положительных элементов: " << product << '\n';
								}
								else
									std::cout << "\nНет положительных элементов! " << '\n';
								free_memory(arr);
							}

							if (mainChoice == 2)
							{
								std::cout << "\nСумма заданных элементов: " << task2(arr, size) << '\n';
							}

							if (mainChoice == 3)
							{

							}
						}
					}

					if (choice == 3)
					{
						int size;
						std::cout << "\nВведите количество случайных слагаемых: ";
						Read_and_check(size, std::cin, [](int x) {return x > 0; }, "\n-> ");
						std::cin.ignore(std::cin.rdbuf()->in_avail());

						int a, b;
						std::cout << "\nВведите диапазон рандома(от A до B): ";
						Read_and_check(a, std::cin, [](int x) {return true; }, "\n-> ");
						Read_and_check(b, std::cin, [](int x) {return true; }, "");

						int* arr = memory_allocation(size);
						fill(arr, arr + size, a, b);
						print(arr, size);

						if (mainChoice == 1)
						{
							int product;
							if (task1(arr, size, product, [](int x) {return x > 0; }))
							{
								std::cout << "\nПроизведение положительных элементов: " << product << '\n';
							}
							else
								std::cout << "\nНет положительных элементов! " << '\n';
							free_memory(arr);
						}

						if (mainChoice == 2)
						{
							std::cout << "\nСумма заданных элементов: " << task2(arr, size) << '\n';
						}

						if (mainChoice == 3)
						{

						}
					}
				}
			} while (choice != 4);
		}
	} while (mainChoice != 4);

}

bool task1(int* arr, int size, int& product, std::function<bool(int)> predicate)
{
	bool isFind = false;
	product = 1;
	for (int i = 0; i < size; ++i)
	{
		if (predicate(*(arr + i)))
		{
			product = *(arr + i) * product;
			isFind = true;
		}
	}
	return isFind;
}

int findMinIndex(int* arr, int size)
{
	int i = 0;
	int minIndex=0;
	bool isFind = false;
	for (int i = 0; i < size; ++i)
	{
		if (*(arr + i) < *(arr + minIndex))
		{
			minIndex = i;
		}
		
	}
	return minIndex;
}

int task2(int* arr, int size)
{
	int sum = 0;
	for (int i = 0; i < findMinIndex(arr,size); ++i)
	{
		sum = sum + *(arr + i);
	}
	return sum;
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

int GetRandomInInterval(int a, int b)
{
	return a + rand() % (b - a + 1);
}

bool fileInput(std::ifstream& file)
{
	bool ConditionFlag = true;
	if (check_file(file) == -1)
	{
		std::cout << "\nФайл не найден!\n";
		ConditionFlag = false;
	}
	if (check_file(file) == 0)
	{
		std::cout << "\nФайл пустой!\n";
		ConditionFlag = false;
	}
	return ConditionFlag;
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

void print(int* arr, int size)
{
	std::cout << "\nЭлементы массива: ";
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << ' ';
	}
	std::cout << '\n';
}

void fill(int* arr, int size, std::istream& stream)
{
	for (int i = 0; i < size; i++)
	{
		Read_and_check(arr[i], stream, [](int x) {return true; }, "");
	}
}

void fill(int* begin, int* end, int a, int b)
{
	for (int* ptr{ begin }; ptr != end; ++ptr)
	{
		*ptr = GetRandomInInterval(a, b);
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