#if !defined TRACTOR_EXCEPTION_EXCEPTION_HPP



// for std::exception
#include <exception>
// for std::string
#include <string>
// for std::move
#include <utility>

// for std::strerror
#include <cstring>



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



// struct numeric_code_translator;
// using using int_code_translator;
namespace tractor
{
    template<class number_type>
    struct numeric_code_translator
    {
    public:
        std::string operator()(number_type code) const volatile;
    };



    template<class number_type>
    inline std::string numeric_code_translator<number_type>::operator()(number_type code) const volatile
    {
        return std::to_string(code);
    }



    using int_code_translator = numeric_code_translator<int>;
}



// struct errno_code_translator ;
namespace tractor
{
    struct errno_code_translator
    {
    public:
        std::string operator()(int code) const volatile;
    };



    inline std::string errno_code_translator::operator()(int code) const volatile
    {
        return std::string{std::strerror(code)};
    }
}



// class basic_code_exception;
// using numeric_code_exception;
// using int_code_exception;
// using errno_code_exception;
namespace tractor
{
    template<class code_type, class code_translator_type>
    class basic_code_exception : public std::exception
    {
    public:
        basic_code_exception(const code_translator_type& code_translator = code_translator_type{});
        basic_code_exception(const basic_code_exception& other) = default;
        basic_code_exception(basic_code_exception&& other) = default;
        basic_code_exception(code_type code, const code_translator_type& code_translator = code_translator_type{});

        virtual ~basic_code_exception() noexcept override = default;

        basic_code_exception& operator=(const basic_code_exception&) = default;
        basic_code_exception& operator=(basic_code_exception&&) = default;

        virtual const char* what() const noexcept override;
        virtual code_type code() const noexcept;

    protected:
        code_type m_code;
        std::string m_text;
    };



    template<class code_type, class code_translator_type>
    inline basic_code_exception<code_type, code_translator_type>::basic_code_exception(const code_translator_type& code_translator) :
        basic_code_exception{code_type{}, code_translator}
    {
    }

    template<class code_type, class code_translator_type>
    inline basic_code_exception<code_type, code_translator_type>::basic_code_exception(code_type code, const code_translator_type& code_translator) :
        m_code{code},
        m_text{code_translator(code)}
    {
    }

    template<class code_type, class code_translator_type>
    inline const char* basic_code_exception<code_type, code_translator_type>::what() const noexcept
    {
        return m_text.c_str();
    }

    template<class code_type, class code_translator_type>
    inline code_type basic_code_exception<code_type, code_translator_type>::code() const noexcept
    {
        return m_code;
    }



    template<class code_type>
    using numeric_code_exception = basic_code_exception<code_type, numeric_code_translator<code_type>>;
    using int_code_exception = numeric_code_exception<int>;
    using errno_code_exception = basic_code_exception<int, errno_code_translator>;
}



#endif // !defined TRACTOR_EXCEPTION_EXCEPTION_HPP
