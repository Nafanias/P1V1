#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <limits>
#include <utility>
#include <sstream>
#include <Windows.h>

// Функция для поиска и вывода минимального и максимального элементов массива
void FindAndPrintMinMax(std::vector<int>& array)
{
	// Инициализация переменных для минимального и максимального элементов
	int max = array[0];
	int min = array[0];

	// Векторы для хранения индексов минимального и максимального элементов
	std::vector<int> maxIndexes;
	std::vector<int> minIndexes;

	// Обход массива для поиска минимального и максимального элементов
	for (int i = 0; i < array.size(); i++)
	{
		// Поиск максимального элемента
		if (max < array[i])
		{
			max = array[i];
			maxIndexes.clear();
			maxIndexes.push_back(i);
		}
		else if (max == array[i])
		{
			maxIndexes.push_back(i);
		}

		// Поиск минимального элемента
		if (min > array[i])
		{
			min = array[i];
			minIndexes.clear();
			minIndexes.push_back(i);
		}
		else if (min == array[i])
		{
			minIndexes.push_back(i);
		}
	}

	// Вывод результатов на экран
	std::cout << "Максимальный элемент: " << max << std::endl;
	std::cout << "Индексы максимального элемента: ";
	for (int i : maxIndexes)
	{
		std::cout << i << " ";
	}

	std::cout << std::endl;

	std::cout << "Минимальный элемент: " << min << std::endl;
	std::cout << "Индексы минимального элемента: ";
	for (int i : minIndexes)
	{
		std::cout << i << " ";
	}

	std::cout << std::endl << std::endl;
}

// Функция для вычисления суммы и произведения элементов вектора
std::pair<long long, long long> SummAndCompositionElement(const std::vector<int>& array)
{
	// Используем long long для суммы и произведения для обработки большего диапазона чисел
	long long sum = 0;  // Переменная для хранения суммы элементов
	long long product = 1;  // Переменная для хранения произведения элементов
	bool productOverflow = false;  // Флаг для проверки переполнения произведения

	// Проходим по всем элементам вектора и вычисляем сумму и произведение
	for (int num : array)
	{
		// Проверяем переполнение при сложении
		if (num > 0 && sum > (std::numeric_limits<long long>::max)() - num)
		{
			return { 0, 0 }; // Возвращаем 0, 0 в случае переполнения суммы
		}

		// Проверяем переполнение при умножении
		if (num != 0 && product > (std::numeric_limits<long long>::max)() / num)
		{
			return { sum, 0 }; // Возвращаем сумму и 0 в случае переполнения произведения
		}

		// Проверяем, что при сложении суммы с текущим числом не происходит переполнения
		if (sum + num > sum)
		{
			sum += num; // Увеличиваем сумму на текущий элемент

			// Проверяем переполнение произведения, только если до этого не было переполнения
			if (!productOverflow)
			{
				if (product * num / num == product)
				{
					product *= num; // Умножаем произведение на текущий элемент
				}
				else
				{
					productOverflow = true; // Устанавливаем флаг на переполнение произведения
				}
			}
		}
		else
		{
			return { 0, 0 }; // Возвращаем 0, 0 в случае переполнения суммы
		}

		// Если произошло переполнение произведения, возвращаем сумму и 0
		if (productOverflow)
		{
			return { sum, 0 };
		}
	}

	// Возвращаем сумму и произведение в виде пары
	return { sum, product };
}

// Функция для нахождения среднего арифметического и геометрического 
void FindingArithmeticMeanAndGeometricMean(const std::vector<int>& array)
{
	double geometricMean = 1.0;

	// Вызываем функцию для вычисления суммы и произведения
	auto result = SummAndCompositionElement(array);

	// Было ли переполнение в прошлой функции
	if (result.first != 0 and result.second !=0)
	{
		// Выводим сумму и произведение на экран
		std::cout << "Сумма всех элементов массива: " << result.first << std::endl;
		std::cout << "Произведение всех элементов массива: " << result.second << std::endl;
		std::cout << std::endl;
		// Вычисляем среднее арифметическое 
		double arithmeticMean = static_cast<double>(result.first) / array.size();

		// Выводим средние арифметическое на экран
		std::cout << "Среднее арифметическое: " << arithmeticMean << std::endl;
	}
	else if (result.first != 0 and result.second == 0)
	{
		// Выводим сумму на экран
		std::cout << "Сумма всех элементов массива: " << result.first << std::endl;
		std::cout << "Переполнение произведения. Вычисления прерваны." << std::endl;
		std::cout << std::endl;
		// Вычисляем среднее арифметическое 
		double arithmeticMean = static_cast<double>(result.first) / array.size();

		// Выводим средние арифметическое на экран
		std::cout << "Среднее арифметическое: " << arithmeticMean << std::endl;
	}
	else
	{
		std::cout << "Переполнение суммы. Вычисления прерваны." << std::endl;
		std::cout << "Переполнение произведения. Вычисления прерваны." << std::endl;
		std::cout << "Переполнение суммы. Вычисления прерваны (среднее арифметическое)." << std::endl;
	}

	// Вычисляем среднее геометрическое 
	for (int num : array)
	{
		// Проверяем на возможное переполнение
		if ((std::numeric_limits<double>::max)() / geometricMean < num)
		{
			std::cout << "Переполнение при вычислении среднего геометрического" << std::endl;
			return; // Завершаем функцию
		}

		geometricMean *= num;
	}
	geometricMean = std::pow(geometricMean, 1.0 / array.size());

	// Выводим средние геометрическое на экран
	std::cout << "Среднее геометрическое: " << geometricMean << std::endl;
	std::cout << std::endl;
}

// Функция для нахождения количества чётных и нечётных элементов в массиве
void FindEvenOddElements(std::vector<int>& array)
{
	int evenCount = 0; // Счетчик чётных элементов
	int oddCount = 0; // Счетчик нечётных элементов

	// Проход по всем элементам массива
	for (int i = 0; i < array.size(); ++i)
	{
		// Проверка чётности элемента
		if (array[i] % 2 == 0)
		{
			evenCount++; // Увеличение счётчика чётных элементов
		}
		else
		{
			oddCount++; // Увеличение счётчика нечётных элементов
		}
	}

	std::cout << "Количество чётных элементов: " << evenCount << std::endl;
	std::cout << "Количество нечётных элементов: " << oddCount << std::endl;
}

// Функция для поиска значения в массиве, заданного пользователем программы.
void SearchValue(std::vector<int> array, int value)
{
	bool found = false; // Флаг для отслеживания наличия значения в массиве
	int count = 0; // Счетчик повторений искомого значения

	std::cout << std::endl;
	std::cout << "Индексы найденного значения: ";
	// Проход по всем элементам массива
	for (int i = 0; i < array.size(); i++)
	{
		// Проверка на равенство элемента массива искомому значению
		if (array[i] == value)
		{
			std::cout << i << "  "; // Вывод индекса найденного значения
			count++; // Увеличение счетчика повторений
			found = true; // Установка флага, что значение найдено
		}
	}

	// Вывод информации о результате поиска
	if (found)
	{
		std::cout << "\nЗначение " << value << " найдено " << count << " раз(а) в массиве." << std::endl;
	}
	else
	{
		std::cout << "Значение " << value << " не найдено в массиве." << std::endl;
	}
}

// Функция сортировки массива по возрастанию с использованием алгоритма сортировки выбором
void SelectionSortAscending(std::vector<int>& array)
{
	// Внешний цикл проходит по всем элементам массива, кроме последнего
	for (int i = 0; i < array.size() - 1; i++)
	{
		int minIndex = i;
		// Внутренний цикл ищет минимальный элемент в оставшейся части массива
		for (int j = i + 1; j < array.size(); j++)
		{
			// Если находится элемент меньше текущего минимального, его индекс сохраняется
			if (array[j] < array[minIndex])
			{
				minIndex = j;
			}
		}

		// Если индекс минимального элемента не равен текущему индексу, происходит обмен элементов
		if (minIndex != i)
		{
			// Обмен местами элементов для сортировки по возрастанию
			int temp = array[i];
			array[i] = array[minIndex];
			array[minIndex] = temp;
		}
	}
}

// Функция сортировки массива по убыванию с использованием алгоритма сортировки выбором
void SelectionSortDescending(std::vector<int>& array)
{
	// Внешний цикл проходит по всем элементам массива, кроме последнего
	for (int i = 0; i < array.size() - 1; i++)
	{
		int maxIndex = i;

		// Внутренний цикл ищет максимальный элемент в оставшейся части массива
		for (int j = i + 1; j < array.size(); j++)
		{
			// Если находится элемент больше текущего максимального, его индекс сохраняется
			if (array[j] > array[maxIndex])
			{
				maxIndex = j;
			}
		}

		// Если индекс максимального элемента не равен текущему индексу, происходит обмен элементов
		if (maxIndex != i)
		{
			// Обмен местами элементов для сортировки по убыванию
			int temp = array[i];
			array[i] = array[maxIndex];
			array[maxIndex] = temp;
		}
	}
}


// Главная функция
int main(int argc, char* argv[])
{
	SetConsoleCP(1251); // Установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // Установка кодовой страницы win-cp 1251 в поток вывода
	int numberEnteredByUser; // Значение которое ввёл пользователь
	bool validInput = true; // Флаг удовлетворения условий ввода значений для поиска в векторе
	std::vector<int> array;

	// Проверяем, были ли переданы аргументы командной строки
	if (argc == 1)
	{
		std::cout << "Нет данных в аргументах командной строки." << std::endl;
		return 0;
	}

	// Проверяем, что все аргументы являются положительными целыми числами > 0
	for (int i = 1; i < argc; i++) {
		try {
			std::string argString = std::string(argv[i]); // Преобразуем аргумент в строку
			size_t pos = 0;
			int num = std::stoi(argString, &pos);

			if (pos != argString.size() || !argString.empty() && std::isspace(argString.back())) {
				throw std::invalid_argument("Неверное значение введено");
			}
			else if (num <= 0) {
				throw std::out_of_range("Число должно быть больше 0");
			}

			array.push_back(num);
		}
		catch (const std::invalid_argument& e) {
			std::cout << "Ошибка для аргумента " << i << ": Неверное значение введено.\n";
			validInput = false;
		}
		catch (const std::out_of_range& e) {
			std::cout << "Ошибка для аргумента " << i << ": Число должно быть неотрицательным и в допустимом диапазоне.\n";
			validInput = false;
		}
	}

	if (!validInput) {
		std::cout << "Одно или более значений не удовлетворяют условиям. Пожалуйста, исправьте данные и повторите попытку.\n";
		return 1; // Возвращаем код ошибки
	}

	FindAndPrintMinMax(array); // Находим и выводим минимальный и максимальный элементы
	SummAndCompositionElement(array); // Суммируем и находим произведение элементов
	FindingArithmeticMeanAndGeometricMean(array); // Находим среднее арифметическое и среднее геометрическое

	FindEvenOddElements(array); // Находим четные и нечетные элементы

	std::cout << "Введите значение для поиска. ";
	std::string inputValue;
	bool isValidInputM = false;
	do {
		// Запрос пользовательского ввода
		std::cout << "Введите положительное целое число, которое входит в диапазон типа int и больше 0: "; 
		std::cin >> inputValue;
		int integerValue;

		try {
			size_t pos = 0;
			integerValue = std::stoi(inputValue, &pos); // Преобразование строки в int
			if (pos < inputValue.size()) {
				throw std::invalid_argument("Неверный формат числа");
			}
			if (integerValue <= 0) {
				throw std::out_of_range("Число должно быть положительным");
			}
			else {
				numberEnteredByUser = integerValue;
				validInput = true;
			}
		}
		catch (const std::invalid_argument& e) {
			std::cout << "Ошибка для аргумента " << integerValue << ": Неверное значение введено.\n";
			validInput = false; // Устанавливаем флаг в false, так как одно из значений не удовлетворяет условиям
			std::cin.clear();
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		}
		catch (const std::out_of_range& e) {
			std::cout << "Ошибка для аргумента " << integerValue << ": Число должно быть неотрицательным и в допустимом диапазоне.\n";
			validInput = false; // Устанавливаем флаг в false
			std::cin.clear();
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		}
	} while (!validInput);

	SearchValue(array, numberEnteredByUser); // Ищем значение в массиве
	std::cout << std::endl;

	SelectionSortAscending(array); // Сортируем массив в порядке возрастания
	std::cout << "Отсортированный массив по возрастанию: ";
	for (int i = 0; i < array.size(); i++) {
		std::cout << array[i] << ", ";
	}

	
	SelectionSortDescending(array); // Сортируем массив в порядке убывания
	std::cout << std::endl;
	std::cout << "Отсортированный массив по убыванию: ";
	for (int i = 0; i < array.size(); i++) {
		std::cout << array[i] << ", ";
	}

	std::cout << std::endl;

	return 0;
}