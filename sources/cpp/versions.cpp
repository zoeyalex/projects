#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class Version
{
private:
	unsigned int major, minor, release;

public:
	Version(unsigned int _major, unsigned int _minor, unsigned int _release)
		: major(_major)
		, minor(_minor)
		, release(_release)
	{}

	void print() const
	{
		cout << major << "." << minor << "." << release << endl;
	}

	// operator overloading / method
	bool operator<(const Version& other) const
	{
		if (major != other.major)
		{
			return major < other.major;
		}
		if (minor != other.minor)
		{
			return minor < other.minor;
		}
		return release < other.release;
	}

	unsigned int get_major() const
	{
		return major;
	}

	unsigned int get_minor() const
	{
		return minor;
	}

	unsigned int get_release() const
	{
		return release;
	}
};

/* operator overloading / function
bool operator< (const Version& lhs, const Version& rhs)
{
	if (lhs.get_major() != rhs.get_major())
	{
		return lhs.get_major() < rhs.get_major();
	}
	if (lhs.get_minor() != rhs.get_minor())
	{
		return lhs.get_minor() < rhs.get_minor();
	}
	return lhs.get_release() < rhs.get_release();
}
*/


unsigned int randrange(unsigned int min, unsigned int max)
{
	return rand() % (max - min + 1) + min;
}

int main()
{
	srand(time(NULL));

	vector<Version> versions;
	for (int i = 0; i < 10; i++)
	{
		versions.push_back({ randrange(0, 9), randrange(0, 9), randrange(0, 9) });
	}
	sort(versions.begin(), versions.end());
	for (const Version& v : versions)
	{
		v.print();
	}
}