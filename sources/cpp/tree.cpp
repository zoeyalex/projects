#include <iostream>
#include <string>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

void print_entries(const fs::directory_entry& root_entry, int indent = 0)
{
	for (const auto& entry : fs::directory_iterator(root_entry))
	{
		for (int i = 0; i < indent; i++)
		{
			cout << ' ';
		}
		cout << entry.path().filename().string() << " - ";
		if (entry.is_directory())
		{
			cout << "directory\n";
			print_entries(entry, indent + 4);
		}
		else
		{
			cout << "file\n";
		}
		
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << "usage: " << argv[0] << " path\n";
		return 1;
	}
	string path = argv[1];
	print_entries(fs::directory_entry(fs::path(path)));
}