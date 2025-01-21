#include "String.h"

namespace Chess
{
    FenString::FenString(const std::string_view &content) : m_Content(content)
    {
    }

    FenString::FenString()
    {
    }

    FenString::FenString(const FenString &other) : m_Content(other.m_Content)
    {
    }

    FenString::FenString(FenString &&other) : m_Content(std::move(other.m_Content))
    {
    }

    std::deque<FenString> FenString::Split(std::string_view delim) const
    {
        std::deque<FenString> result;
        size_t start = 0;
        size_t end;

        while ((end = m_Content.find(delim, start)) != std::string_view::npos)
        {
            result.push_back(m_Content.substr(start, end - start));
            start = end + 1;
        }

        result.push_back(m_Content.substr(start));

        return result;
    }
}