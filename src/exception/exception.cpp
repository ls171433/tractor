#include "exception/exception.hpp"

// for std::move
#include <utility>



namespace tractor
{
    text_exception::text_exception() :
        m_text{}
    {
    }

    text_exception::text_exception(const text_exception& other) :
        m_text{other.m_text}
    {
    }

    text_exception::text_exception(text_exception&& other) :
        m_text{std::move(other.m_text)}
    {
    }

    text_exception::text_exception(const std::string& text) :
        m_text{text}
    {
    }

    text_exception::text_exception(const std::exception& e) :
        m_text{e.what()}
    {
    }



    text_exception::~text_exception() noexcept
    {
    }



    text_exception& text_exception::operator=(const text_exception& other)
    {
        m_text = other.m_text;

        return *this;
    }

    text_exception& text_exception::operator=(text_exception&& other)
    {
        m_text = std::move(other.m_text);

        return *this;
    }



    const char* text_exception::what() noexcept
    {
        return m_text.c_str();
    }
}
