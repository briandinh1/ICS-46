// main.cpp
//
// ICS 46 Spring 2016
// Project #4: Rock and Roll Stops the Traffic
//
// This is the program's main() function, which is the entry point for your
// console user interface.

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "InputReader.hpp"
#include "RoadMapReader.hpp"
#include "RoadMapWriter.hpp"
#include "TripReader.hpp"


void showTime(double time)
{
    int hours = (int)time;
    double temp = time - hours;
    int minutes = (int)(temp * 60);
    temp = (temp * 60) - minutes;
    double seconds = temp * 60;

    if (hours > 0) std::cout << hours << " hours ";
    if (minutes > 0) std::cout << minutes << " mins ";
    if (seconds > 0) std::cout << std::setprecision(2) << seconds << " secs";
}

int main()
{
    // read from standard input stream
    InputReader input(std::cin);
    RoadMapReader r_reader;
    RoadMap r = r_reader.readRoadMap(input);

    TripReader t_reader;
    std::vector<Trip> trips = t_reader.readTrips(input);

    for (size_t i = 0; i < trips.size(); ++i)
    {
        std::map<int, int> m = r.findShortestPaths(trips[i].startVertex);
        std::vector<int> path;
        double totalDistance = 0.0, totalTime = 0.0;

        // make an array of the path from startVertex to EndVertex
        path.push_back(trips[i].endVertex);
        while (true)
        {
            if (m.at(path.back()) == path.back()) break;
            path.push_back(m.at(path.back()));
        }

        if (path.back() != trips[i].startVertex)
        {
            std::cout << "Cannot travel from " << r.vertexInfo(trips[i].startVertex)
                << " to " << r.vertexInfo(trips[i].endVertex) << std::endl << std::endl;
            continue;
        }

        std::cout << "Shortest distance from " << r.vertexInfo(trips[i].startVertex)
            << " to " << r.vertexInfo(trips[i].endVertex) << std::endl;

        std::cout << "\tBegin at " << r.vertexInfo(trips[i].startVertex) << std::endl;


        for (std::vector<int>::reverse_iterator rit = path.rbegin(); rit != path.rend(); ++rit)
        {
            double distance = 0.0, speed = 0.0, time = 0.0; 

            if (*rit == trips[i].endVertex)
            {
                distance = r.edgeInfo(m[trips[i].endVertex], trips[i].endVertex).miles;
                speed = r.edgeInfo(m[trips[i].endVertex], trips[i].endVertex).milesPerHour;

                std::cout << "\tContinue to " << r.vertexInfo(trips[i].endVertex) << " (" << distance;
            }
            else
            {
                distance = r.edgeInfo(*rit, *(rit + 1)).miles;
                speed = r.edgeInfo(*rit, *(rit + 1)).milesPerHour;

                std::cout << "\tContinue to " << r.vertexInfo(*rit) << " (" << distance;
            }

            if (trips[i].metric == TripMetric::Distance) std::cout << " miles)";
            else
            {
                std::cout << " miles @ " << speed << " mph = ";
                showTime(time = distance / speed);
                std::cout << ")";
            }

            std::cout << std::endl;
            totalDistance += distance;
            totalTime += time;
        }

        if (trips[i].metric == TripMetric::Distance)
            std::cout << "Total Distance: " << totalDistance << " miles";
        else
        {
            std::cout << "Total Time: ";
            showTime(totalTime);
        }

        std::cout << std::endl << std::endl << std::endl;
    }

    return 0;
}
