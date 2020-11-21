#include <iostream>
#include <ctime>
#include "httplib.h"

using namespace std;

int rand_range(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

int main()
{
	
	httplib::Server svr;
	
	svr.Get("/randomnumber", [](const httplib::Request&, httplib::Response& res) {
		string json = to_string(rand_range(1, 100));
		res.set_header("Access-Control-Allow-Origin", "*");
		cout << "Request" << endl;
		res.set_content(json, "application/json");
		});

	svr.listen("0.0.0.0", 8080);
	return 0;
}