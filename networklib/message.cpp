#include "message.h"

#include <vector>
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

#define STRINGIFY(arg)  #arg

static const char* k_typeKey = "type";
static const char* k_addressKey = "address";
static const char* k_urlKey = "url";
static const char* k_timestampKey = "timestamp";
static const char* k_activityCountKey = "activity_count";
static const char k_eof = '\0';

struct Message::Private : rapidjson::Document
{
    Private() 
    {
        SetObject();
    }

    boost::optional<ValueType&> FindMember(const char* name)
    {
        for (Private::MemberIterator it = MemberBegin(); it != MemberEnd(); it++)
        {
            if (strcmp(it->name.GetString(), name) == 0)
            {
                return it->value;
            }
        }
        return boost::none;
    }
};

Message::Message()
    : m_private(new Private)
{
}

Message::Message(const Message::Activity &activity)
    : m_private(new Private)
{
    rapidjson::Value address, url, timestamp, type;
    type.SetString(STRINGIFY(Type::QUESTIONABLE_ACTIVITY_FOUND),
        m_private->GetAllocator());
    address.SetString(activity.address.c_str(), 
        m_private->GetAllocator());
    url.SetString(activity.url.c_str(), 
        m_private->GetAllocator());
    timestamp.SetUint64(activity.timestamp);
    m_private->AddMember(k_typeKey, type, m_private->GetAllocator());
    m_private->AddMember(k_addressKey, address, m_private->GetAllocator());
    m_private->AddMember(k_urlKey, url, m_private->GetAllocator());
    m_private->AddMember(k_timestampKey, timestamp, m_private->GetAllocator());
}

Message::~Message()
{
    rapidjson::Value type;
    type.SetString(STRINGIFY(Type::INVALID), m_private->GetAllocator());
    m_private->AddMember(k_typeKey, type, m_private->GetAllocator());
}

bool Message::IsValid() const
{
    return m_private->HasParseError();
}

Message::Type Message::GetType() const
{
    static std::vector<std::string> strings =
    {
        STRINGIFY(Type::QUESTIONABLE_ACTIVITY_FOUND),
        STRINGIFY(Type::STORED),
        STRINGIFY(Type::NOT_STORED)
    };

    auto it = std::find(strings.cbegin(), strings.cend(),
                        (*m_private)[k_typeKey].GetString());

    return it == strings.cend()
            ? Type::INVALID
            : static_cast<Type>(std::distance(strings.cbegin(), it));
}

void Message::SetType(Message::Type type)
{
    char* data;
    switch (type)
    {
    case Type::QUESTIONABLE_ACTIVITY_FOUND:
        data = STRINGIFY(Type::QUESTIONABLE_ACTIVITY_FOUND);
        break;
    case Type::STORED:
        data = STRINGIFY(Type::STORED);
        break;
    case Type::NOT_STORED:
        data = STRINGIFY(Type::NOT_STORED);
        break;
    case Type::INVALID:
        assert(false);
        break;
    }
    (*m_private)[k_typeKey].SetString(data);
}

Message::Activity Message::GetActivity() const
{
    Activity activity;
    activity.address = GetAddress();
    activity.url = GetUrl();
    activity.timestamp = GetTimestamp();
    return activity;
}

std::string Message::GetAddress() const
{
    return (*m_private)[k_addressKey].GetString();
}

std::string Message::GetUrl() const
{
    return (*m_private)[k_urlKey].GetString();
}

time_t Message::GetTimestamp() const
{
    return (*m_private)[k_timestampKey].GetInt64();
}

boost::optional<std::uint32_t> Message::GetActivityCount() const
{
    auto result = m_private->FindMember(k_activityCountKey);
    if (result.is_initialized())
        return result->GetUint();
    return boost::none;
}

void Message::SetActivityCount(std::uint32_t count)
{
    auto result = m_private->FindMember(k_activityCountKey);
    if(result.is_initialized())
        result->SetUint(count);
    else
    {
        rapidjson::Value value;
        value.SetUint(count);
        m_private->AddMember(k_activityCountKey, value,
                             m_private->GetAllocator());
    }
}

void Message::Serialize(std::string& data)
{
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    m_private->Accept(writer);
    buffer.Put('\0');
    data = std::string(buffer.GetString(), buffer.Size());
}

void Message::Serialize(boost::asio::streambuf& streambuf)
{
    std::ostream stream(&streambuf);
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    m_private->Accept(writer);
    buffer.Put(k_eof);
    stream.write(buffer.GetString(), buffer.Size());
}

void Message::Deserialize(boost::asio::streambuf &streambuf)
{
    m_private->Parse<0>(boost::asio::buffer_cast<const char*>(streambuf.data()));
    streambuf.consume(streambuf.size());
}

size_t Message::Send(boost::asio::ip::tcp::socket &socket)
{
    boost::asio::streambuf streambuf;
    Serialize(streambuf);
    return boost::asio::write(socket, streambuf);
}

size_t Message::Receive(boost::asio::ip::tcp::socket &socket)
{
    boost::asio::streambuf streambuf;
    size_t bytes = boost::asio::read_until(socket, streambuf, k_eof);
    Deserialize(streambuf);
    return bytes;
}
