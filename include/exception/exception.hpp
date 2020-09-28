#if !defined TRACTOR_EXCEPTION_EXCEPTION_HPP
#define TRACTOR_EXCEPTION_EXCEPTION_HPP



// for std::exception
#include <exception>
// for std::string
#include <string>
// for std::move
#include <utility>

// for std::strerror
#include <cstring>



// class exception_base
namespace tractor
{
    class exception_base : public std::exception
    {
    public:
        virtual const char *what() const noexcept override;
    };



    inline const char *exception_base::what() const noexcept
    {
        return "tractor::exception_base";
    }
}



// template class basic_text_exception;
// using text_exception;
namespace tractor
{
    template<class char_traits_type_template = std::char_traits<char>, class allocator_type_template = std::allocator<char>>
    class basic_text_exception : public exception_base
    {
    public:
        using string_type = std::basic_string<char, char_traits_type_template, allocator_type_template>;

        basic_text_exception();
        basic_text_exception(const basic_text_exception&) = default;
        basic_text_exception(basic_text_exception&&) = default;
        explicit basic_text_exception(const string_type& text);
        explicit basic_text_exception(string_type&& text);
        explicit basic_text_exception(const std::exception& e);

        virtual ~basic_text_exception() noexcept override = default;

        basic_text_exception& operator=(const basic_text_exception&) = default;
        basic_text_exception& operator=(basic_text_exception&&) = default;

        virtual const char *what() const noexcept override;

    protected:
        string_type m_text;
    };



    template<class char_traits_type_template, class allocator_type_template>
    inline basic_text_exception<char_traits_type_template, allocator_type_template>::basic_text_exception() :
        basic_text_exception{"tractor::basic_text_exception"}
    {
    }

    template<class char_traits_type_template, class allocator_type_template>
    inline basic_text_exception<char_traits_type_template, allocator_type_template>::basic_text_exception(const string_type& text) :
        m_text{text}
    {
    }

    template<class char_traits_type_template, class allocator_type_template>
    inline basic_text_exception<char_traits_type_template, allocator_type_template>::basic_text_exception(string_type&& text) :
        m_text{std::move(text)}
    {
    }

    template<class char_traits_type_template, class allocator_type_template>
    inline basic_text_exception<char_traits_type_template, allocator_type_template>::basic_text_exception(const std::exception& e) :
        basic_text_exception{e.what()}
    {
    }



    template<class char_traits_type_template, class allocator_type_template>
    inline const char *basic_text_exception<char_traits_type_template, allocator_type_template>::what() const noexcept
    {
        return m_text.c_str();
    }



    using text_exception = basic_text_exception<>;
}



// template struct numeric_code_translator;
// using using int_code_translator;
namespace tractor
{
    template<class code_type_template>
    struct numeric_code_translator
    {
    public:
        using code_type = code_type_template;
        using string_type = std::string;

        string_type operator()(code_type code) const;
    };



    template<class code_type_template>
    inline auto numeric_code_translator<code_type_template>::operator()(code_type code) const
        -> typename numeric_code_translator<code_type_template>::string_type
    {
        return std::to_string(code);
    }



    using int_code_translator = numeric_code_translator<int>;
}



// tempalte struct basic_errno_code_translator;
// using errno_code_translator;
namespace tractor
{
    template<class traits_type_template = std::char_traits<char>, class allocator_type_template = std::allocator<char>>
    struct basic_errno_code_translator
    {
    public:
        using code_type = int;
        using string_type = std::basic_string<char, traits_type_template, allocator_type_template>;

        string_type operator()(code_type code) const;
    };



    template<class traits_type_template, class allocator_type_template>
    inline auto basic_errno_code_translator<traits_type_template, allocator_type_template>::operator()(code_type code) const
        -> typename basic_errno_code_translator<traits_type_template, allocator_type_template>::string_type
    {
        return string_type{std::strerror(code)};
    }



    using errno_code_translator = basic_errno_code_translator<>;
}



// template class basic_code_exception;
// template using numeric_code_exception;
// using int_code_exception;
// using errno_code_exception;
namespace tractor
{
    template<class code_translator_type_template>
    class basic_code_exception : public exception_base
    {
    public:
        using code_type = typename code_translator_type_template::code_type;
        using string_type = typename code_translator_type_template::string_type;

        basic_code_exception(const code_translator_type_template& code_translator = code_translator_type_template{});
        basic_code_exception(const basic_code_exception& other) = default;
        basic_code_exception(basic_code_exception&& other) = default;
        explicit basic_code_exception(const code_type& code, const code_translator_type_template& code_translator = code_translator_type_template{});
        explicit basic_code_exception(code_type&& code, const code_translator_type_template& code_translator = code_translator_type_template{});

        virtual ~basic_code_exception() noexcept override = default;

        basic_code_exception& operator=(const basic_code_exception&) = default;
        basic_code_exception& operator=(basic_code_exception&&) = default;

        virtual const char *what() const noexcept override;
        virtual const code_type& code() const noexcept;

    protected:
        code_type m_code;
        string_type m_text;
    };



    template<class code_translator_type_template>
    inline basic_code_exception<code_translator_type_template>::basic_code_exception(const code_translator_type_template& code_translator) :
        basic_code_exception{code_type{}, code_translator}
    {
    }

    template<class code_translator_type_template>
    inline basic_code_exception<code_translator_type_template>::basic_code_exception(const code_type& code, const code_translator_type_template& code_translator) :
        m_code{code},
        m_text{code_translator(m_code)}
    {
    }

    template<class code_translator_type_template>
    inline basic_code_exception<code_translator_type_template>::basic_code_exception(code_type&& code, const code_translator_type_template& code_translator) :
        m_code{std::move(code)},
        m_text{code_translator(m_code)}
    {
    }

    template<class code_translator_type_template>
    inline const char *basic_code_exception<code_translator_type_template>::what() const noexcept
    {
        return m_text.c_str();
    }

    template<class code_translator_type_template>
    inline auto basic_code_exception<code_translator_type_template>::code() const noexcept
        -> const code_type&
    {
        return m_code;
    }



    template<class code_type_template>
    using numeric_code_exception = basic_code_exception<numeric_code_translator<code_type_template>>;
    using int_code_exception = numeric_code_exception<int>;
    using errno_code_exception = basic_code_exception<errno_code_translator>;
}



#endif // !defined TRACTOR_EXCEPTION_EXCEPTION_HPP
