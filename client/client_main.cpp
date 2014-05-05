#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "clientlib/client.h"

void QuestionableActivityFound(const Activity& activity)
{
    time_t t = activity.timestamp;
    struct tm *tm = localtime(&t);
    char date[BUFSIZ];
    strftime(date, sizeof(date), "%c", tm);

    std::cout << "New activity:" << std::endl;
    std::cout << "Address: " << activity.address << std::endl;
    std::cout << "Url: " << activity.url << std::endl;
    std::cout << "Timestamp: " << date << std::endl;
}

void ServerAnswer(Client::ServerMessageType result, std::uint32_t count)
{
    std::cout << "Result: " << std::endl;
    switch (result)
    {
    case Client::ServerMessageType::STORED:
        std::cout << "STORED " << std::endl;
        break;
    case Client::ServerMessageType::NOT_STORED:
        std::cout << "NOT_STORED " << std::endl;
        break;
    }
    std::cout << "(Total Activities: " << count << ")" << std::endl << std::endl;
}

int main(int argc, char** argv)
{
    if(argc > 2)
    {
        boost::asio::io_service ios;
        Client client(ios);
        client.AddOffendingWord("porn").AddOffendingWord("xxx")
            .AddOffendingWord("sex").AddOffendingWord("Bieber");
        client.GetQuestionableActivityFoundSignal().connect(std::bind(
                &QuestionableActivityFound, 
                std::placeholders::_1));
        client.GetServerAnswerReceivedSignal().connect(std::bind(
            &ServerAnswer, std::placeholders::_1, std::placeholders::_2));
        if(!client.Connect(argv[1], PORT))
        {
            std::cout << "Server not found" << std::endl;
            return EXIT_FAILURE;
        }
        for (int i = 2; i < argc; i++)
        {
            std::fstream stream(argv[i]);
            if(!stream.is_open())
            {
                std::cout << "File " << argv[i] << " not found." << std::endl;
                return EXIT_FAILURE;
            }
            client.Filter(stream);
        }
    }
	else
	{
		std::cout << "Syntax: " << argv[0] << " address input_file..." << std::endl;
	}
    return EXIT_SUCCESS;
}
