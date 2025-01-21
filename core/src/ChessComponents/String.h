#pragma once
#include <string_view>

#include "Components.h"
#include <deque>

namespace Chess
{
    class FenString
    {
    public:
        /** Default Constructors */
        FenString(const std::string_view &content);
        FenString();

        /* Copy & Move */
        FenString(const FenString &other);
        FenString(FenString &&other);

        /* Overloads */
        void operator=(const std::string_view &content)
        {
            this->m_Content = content;
        }

        FenString &operator=(const FenString &content)
        {
            this->m_Content = content.m_Content;
            return *this;
        }

        void operator=(std::string_view &&content)
        {
            this->m_Content = std::move(content);
        }

        FenString &operator=(FenString &&content)
        {
            this->m_Content = std::move(content.m_Content);
            return *this;
        }

        operator std::string_view() const
        {
            return m_Content;
        }

        /**
         * @brief Returns the memory block containing the FenString.
         * 
         * @return const char* 
         */
        const char *Data() const
        {
            return m_Content.data();
        }

        /**
         * @brief Splits the FenString using the delimeter.
         * 
         * @param std::string_view delim : Delimeter that is used to parse the string.
         * @return std::deque<FenString> : Contains parsed string. 
         */
        std::deque<FenString> Split(std::string_view delim) const;

        /**
         * @brief Returns the size of FenString. This is a wrapper function.
         * 
         * @return const size_t : Size of FenString 
         */
        const size_t Size() const
        {
            return m_Content.size();
        }

    private:
        std::string_view m_Content;
    };
}