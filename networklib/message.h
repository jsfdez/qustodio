#pragma once

#include <memory>
#include <string>
#include <boost/asio.hpp>
#include <boost/optional.hpp>

class Message
{
public:
    enum class Type
    {
        QUESTIONABLE_ACTIVITY_FOUND = 0,
        STORED,
        NOT_STORED,

        INVALID
    };

    struct Activity
    {
        std::string address;
        std::string url;
        time_t timestamp;
    };

    Message();
    Message(const Activity& activity);
    ~Message(); // for forward declaration

    bool IsValid() const;
    Type GetType() const;
    void SetType(Type type);

    Activity GetActivity() const;

    std::string GetAddress() const;
    std::string GetUrl() const;
    time_t GetTimestamp() const;
    boost::optional<std::uint32_t> GetActivityCount() const;
    void SetActivityCount(std::uint32_t count);

    size_t Send(boost::asio::ip::tcp::socket& socket);
    size_t Receive(boost::asio::ip::tcp::socket& socket);

private:
    void Serialize(std::string& data);
    void Serialize(boost::asio::streambuf& streambuf);
    void Deserialize(boost::asio::streambuf& streambuf);

    struct Private;
    std::unique_ptr<Private> m_private;
};
