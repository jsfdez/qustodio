#include <list>
#include <iostream>
#include <stdlib.h>
#include <functional>

#include "serverlib/server.h"

#ifdef _WIN32
#define CLEAR() system("cls")
#else
#define CLEAR() system("clear")
#endif

typedef std::list<std::pair<Activity, std::uint8_t>> Activities;
Activities activities;
std::mutex activitiesMutex;

void ShowQuestionableActivities(std::ostream& os, std::atomic_bool& closing)
{
    while (!closing)
    {
        CLEAR();
        {
            std::lock_guard<std::mutex> lg(activitiesMutex);
            for(Activities::value_type& item: activities)
            {
                os << item.first;
                item.second++;
            }
            activities.erase(std::remove_if(activities.begin(), activities.end(), [](
                const std::pair<Activity, std::uint8_t>& pair)
            {
                return pair.second >= 5;
            }), activities.end());
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void QuestionableActivityReceived(const Activity& activity)
{
    std::lock_guard<std::mutex> lg(activitiesMutex);
    activities.push_back(std::make_pair(activity, 0));
}

int main(int, char**)
{
    boost::asio::io_service ios;
    boost::asio::io_service::work work(ios);
    Server server(ios);

    if (server.StartListening(PORT))
    {
        std::atomic_bool closing;
        server.GetQuestionableActivityReceivedSignal().connect(
            std::bind(&QuestionableActivityReceived, std::placeholders::_1));
        std::thread thread(std::bind(&ShowQuestionableActivities, 
            std::ref(std::cout), std::ref(closing)));
        ios.run();
        if(thread.joinable())
            thread.join();
        return EXIT_SUCCESS;
    }
    std::cout << "Port already in use" << std::endl;
    return EXIT_FAILURE;
}
