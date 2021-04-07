#include <iostream>
#include <string>
#include <filesystem>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
namespace fs = filesystem;

void add_stats(const fs::directory_entry& root_entry, map<string, int>& extensions)
{
	for (const auto& entry : fs::directory_iterator(root_entry))
	{
		string temp = entry.path().extension().string();
		if (entry.is_directory())
		{
			add_stats(entry, extensions);
		}
		else
		{
			extensions[temp]++;
		}
	}
}

bool compare_length(const pair<string, int>& lhs, const pair<string, int>& rhs)
{
	return lhs.first.size() < rhs.first.size();
}

void print_stats(map<string, int>& extensions)
{
	string no_extension_placeholder = "no ext";
	auto result = max_element(extensions.begin(), extensions.end(), compare_length);
	int max_length = max(no_extension_placeholder.size(), result->first.size());

	vector<pair<int, string>> sorted_extensions;
	for (auto it = extensions.begin(); it != extensions.end(); it++)
	{
		sorted_extensions.push_back(make_pair(it->second, it->first));
	}
	sort(sorted_extensions.rbegin(), sorted_extensions.rend());

	cout.width(max_length);
	cout << left << "ext" << " " << "count\n\n";
	for (auto it = sorted_extensions.begin(); it != sorted_extensions.end(); it++)
	{
		cout.width(max_length);
		cout << left;
		if (it->second == "")
		{
			cout << no_extension_placeholder << " " << it->first << endl;
		}
		else
		{
			cout << it->second << " " << it->first << endl;
		}
	}
}

int main(int argc, char* argv[])
{
	map<string, int> extensions;
	string path;

	if (argc != 2)
	{
		cout << "usage: " << argv[0] << " path\n";
		return 1;
	}
	path = argv[1];

	add_stats(fs::directory_entry(fs::path(path)), extensions);
	print_stats(extensions);
}