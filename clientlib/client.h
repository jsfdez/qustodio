#pragma once

#include <boost/signals2.hpp>

#include "commonlib/message.h"
#include "commonlib/connection.h"

class Client : public Connection
{
public:
    enum class ServerMessageType
    {
        STORED = Message::Type::STORED,
        NOT_STORED = Message::Type::NOT_STORED
    };

    typedef boost::signals2::signal<void(const Message::Activity&)> QuestionableActivityFoundSignal;
    typedef boost::signals2::signal<void(ServerMessageType, std::uint32_t)> ServerAnswerReceivedSignal;

    Client(boost::asio::io_service& ios);

    bool Connect(const std::string& host, uint16_t port);

    bool Filter(std::istream& stream);

    QuestionableActivityFoundSignal& GetQuestionableActivityFoundSignal();
    ServerAnswerReceivedSignal& GetServerAnswerReceivedSignal();

    Client& AddOffendingWord(const std::string& word);
    size_t OffendingWordCount();
    std::string GetOffendingWord(size_t index) const;
    Client& RemoveOffendingWord(size_t index);

protected:
    void UpdateFilterExpression();

private:
    void SendQuestionableActivity(const Message::Activity& activity);

    std::vector<std::string> m_offendingWords;
    std::string m_filterExpression;
    QuestionableActivityFoundSignal m_questionableActivityFoundSignal;
    ServerAnswerReceivedSignal m_serverAnswerReceivedSignal;
};
