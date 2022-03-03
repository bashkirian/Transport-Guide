#pragma once

#include "Distance.h"

#include <map>
#include <set>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

class TransportDB
{
private:
	struct StopInfo
	{
		double latitude;
		double longtitude;
	};
	using BusName = string;
	map<BusName, vector<string>> bus_to_stops;
	map<string, StopInfo> stops_info;
public:
	void addStop(const string& stop_name, double latitude, double longtitude)
	{
		stops_info[stop_name] = { latitude, longtitude };
	}
	void addBus(const string& bus_number, vector<string>& stops_for_bus)
	{
		bus_to_stops[bus_number] = move(stops_for_bus);
	}
	void busInfo(const string& bus_number) 
	{
		vector<string> buses = bus_to_stops[bus_number];
		if (buses.empty())
		{
			bus_to_stops.erase(bus_number);
			cout << "Bus " << bus_number << ": not found" << endl;
			return;
		}
		double distance = 0;
		int number_of_unique_stops;
		int number_of_overall_stops;
		cout << "Bus " << bus_number << ": " << buses.size();
		cout << " stops on route, ";
		unordered_set<string> unique_stops(buses.begin(), buses.end());
		cout << unique_stops.size() << " unique stops, ";
		for (size_t i = 1; i < buses.size(); ++i)
		{
			StopInfo current_stop = stops_info[buses[i]];
			StopInfo prev_stop = stops_info[buses[i - 1]];
			distance += Distance(current_stop.latitude, current_stop.longtitude,
				                 prev_stop.latitude, prev_stop.longtitude);
		}
		if (buses.front() != buses.back()) distance *= 2;
		cout << setprecision(6) << distance << " route length" << endl;
	}
};