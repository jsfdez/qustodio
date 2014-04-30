#pragma once

#include "networklib/connection.h"
#include <boost/signals2.hpp>

class Client : public Connection
{
public:
    struct Activity {
        std::string address;
        std::string url;
        time_t timestamp;
    };

    typedef boost::signals2::signal<void(Activity)>
        QuestionableActivityFoundSignal;

    Client(boost::asio::io_service& ios);

    bool Connect(const std::string& host, uint16_t port);

    bool Filter(std::istream& stream);

    QuestionableActivityFoundSignal& GetQuestionableActivityFoundSignal();

    Client& AddOffendingWord(const std::string& word);
    size_t OffendingWordCount();
    std::string GetOffendingWord(size_t index) const;
    Client& RemoveOffendingWord(size_t index);

protected:
    void UpdateFilterExpression();

private:
    QuestionableActivityFoundSignal m_questionableActivityFound;
    std::vector<std::string> m_offendingWords;
    std::string m_filterExpression;
};
