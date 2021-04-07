#include <iostream>

using namespace std;

int min_index(int array[], int from, int to)
{
	int current_min = array[from];
	int current_min_index = from;
	for (int i = from + 1; i <= to; i++)
	{
		if (current_min > array[i])
		{
			current_min = array[i];
			current_min_index = i;
		}
	}
	return current_min_index;
}

void sort(int array[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int index = min_index(array, i, size - 1);
		int temp = array[i];
		array[i] = array[index];
		array[index] = temp;
	}
}


int main()
{
	int array[10] = { 27, 34, 67, 82, 18, 72, 38, 12, 1, 32 };
	sort(array, 10);
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
}