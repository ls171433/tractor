#if !defined TRACTOR_EXCEPTION_EXCEPTION_HPP



// for std::exception
#include <exception>
// for std::string
#include <string>
// for std::move
#include <utility>



// class text_exception;
namespace tractor
{
    class text_exception : public std::exception
    {
    public:
        text_exception();
        text_exception(const text_exception&) = default;
        text_exception(text_exception&&) = default;
        text_exception(const std::string& text);
        text_exception(std::string&& text);
        text_exception(const std::exception& e);

        virtual ~text_exception() noexcept override = default;

        text_exception& operator=(const text_exception&) = default;
        text_exception& operator=(text_exception&&) = default;

        virtual const char* what() const noexcept override;

    protected:
        std::string m_text;
    };



    inline text_exception::text_exception() :
        text_exception{"tractor::text_exception"}
    {
    }

    inline text_exception::text_exception(const std::string& text) :
        m_text{text}
    {
    }

    inline text_exception::text_exception(std::string&& text) :
        m_text{std::move(text)}
    {
    }

    inline text_exception::text_exception(const std::exception& e) :
        text_exception{e.what()}
    {
    }



    inline const char* text_exception::what() const noexcept
    {
        return m_text.c_str();
    }
}



#endif // !defined TRACTOR_EXCEPTION_EXCEPTION_HPP
