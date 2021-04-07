#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>
#include <map>
#include <stack>

using namespace std;

bool load(vector<uint8_t> &instructions, const char *path)
{
	ifstream bf_file(path, ios::in | ios::binary); // opens file at path in binary mode
	if (!bf_file.is_open())
	{
		return false;
	}

	char *buffer;

	bf_file.seekg(0, bf_file.end);
	int length = bf_file.tellg();
	bf_file.seekg(0, bf_file.beg);

	buffer = new char[length];


	bf_file.read(buffer, length);

	if (!bf_file)
	{
		printf("error: only %lld bytes(characters) could be read\n", bf_file.gcount());
		bf_file.close();
		delete[] buffer;

		return false;
	}

	for (int i = 0; i < length; i++)
	{
		switch (buffer[i])
		{
		case '+':
		case '-':
		case '<':
		case '>':
		case '.':
		case ',':
		case '[':
		case ']':
			instructions.push_back(buffer[i]);
			break;
		}
	}
	bf_file.close();
	delete[] buffer;

	return true;
}

bool mapped_jumps(const vector<uint8_t> &instructions, map<int, int> &jumps)
{
	stack<int> leftside; // useless

	for (int i = 0; i < instructions.size(); i++)
	{
		switch(instructions[i])
		{
		case '[':
			leftside.push(i);
			break;
		case ']':
			if (leftside.empty())
			{
				return false;
			}
			jumps[leftside.top()] = i;
			jumps[i] = leftside.top();
			leftside.pop();
			break;
		}
	}
	return leftside.empty();
}

#define BYTES 256
int main(int argc, char *argv[])
{
	uint8_t bytes[BYTES] = { 0 };
	vector<uint8_t> instructions;
	map<int, int> jumps;
	int data_pointer = 0;
	int instruction_pointer = 0;

	if (argc != 2)
	{
		printf("usage: %s filename\n", argv[0]);
		return 1;
	}

	if (!load(instructions, argv[1]))
	{
		printf("couldn't open: %s\n", argv[1]);
		return 1;
	}

	if (!mapped_jumps(instructions, jumps))
	{
		printf("unmatched parentheses\n");
		return 1;
	}

	for (instruction_pointer; instruction_pointer < instructions.size(); instruction_pointer++)
	{
		switch(instructions[instruction_pointer])
		{
		case '+':
			bytes[data_pointer]++;
			break;

		case '-':
			bytes[data_pointer]--;
			break;

		case '.':
			printf("%c", bytes[data_pointer]);
			break;

		case ',':
			bytes[data_pointer] = getchar();
			break;

		case '<':
			if (!data_pointer)
			{
				printf("runtime error\n");
				return 2;
			}
			data_pointer--;
			break;

		case '>':
			if (data_pointer == (BYTES - 1))
			{
				printf("runtime error\n");
				return 2;
			}
			data_pointer++;
			break;

		case '[':
			if (bytes[data_pointer] == 0)
			{
				instruction_pointer = jumps[instruction_pointer]; // jump to matching ]
			}
			break;

		case ']':
			if (bytes[data_pointer] != 0)
			{
				instruction_pointer = jumps[instruction_pointer];
			}
			break;
		}
	}
}