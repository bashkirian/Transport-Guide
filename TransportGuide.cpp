#include "Guide.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
	int number_of_entries, number_of_queries;
	cin >> number_of_entries;
	TransportDB guide;
	for (int i = 0; i < number_of_entries; ++i)
	{
		string entry_name, stop_name;
		double latitude, longtitude;
		cin >> entry_name;
		if (entry_name == "Stop")
		{
			cin.ignore(1);
			getline(cin, stop_name, ':');
			cin >> latitude;
			cin.ignore(1);
			cin >> longtitude;
			guide.addStop(stop_name, latitude, longtitude);
		}
		else
		{
			if (entry_name == "Bus")
			{
				string bus_number;
				cin >> bus_number;
				bus_number.pop_back();
				string stop_name, stop_name_part;
				cin >> stop_name_part;
				stop_name.append(stop_name_part);
				cin >> stop_name_part;
				while (stop_name_part != ">" && stop_name_part != "-")
				{
					stop_name.append(" " + stop_name_part);
					cin >> stop_name_part;
				}
				vector<string> stops_for_bus;
				stops_for_bus.push_back(stop_name);
				char delim;
				delim = (stop_name_part == ">") ? '>' : '-';
				string line;
				getline(cin, line);
				stringstream ss(line);
				while (getline(ss, stop_name, delim))
				{
					stop_name.erase(stop_name.begin());
					if (stop_name.back() == ' ') stop_name.pop_back();
					stops_for_bus.push_back(stop_name);
				}
				guide.addBus(bus_number, stops_for_bus);
			}
		}
	}
	cin >> number_of_queries;
	string query, bus_number;
	for (int i = 0; i < number_of_queries; ++i)
	{
		cin >> query;
		if (query == "Bus")
		{
			cin >> bus_number;
			guide.busInfo(bus_number);
		}
	}
}