#if !defined TRACTOR_EXCEPTION_EXCEPTION_HPP
#define TRACTOR_EXCEPTION_EXCEPTION_HPP

// for std::exception
#include <exception>
// for std::allocator
#include <memory>
// for std::basic_string
// for std::char_traits
// for std::string
// for std::to_string
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
} // namespace tractor

// template class basic_text_exception;
// template using text_exception_basic_string_char;
// using text_exception;
namespace tractor
{
    template <class string_type_template = std::string>
    class basic_text_exception : public exception_base
    {
    public:
        using string_type = string_type_template;

        static_assert(std::is_same<typename string_type::value_type, char>::value, "the 'value_type' of 'string_type' is not 'char'");

        basic_text_exception();
        basic_text_exception(const basic_text_exception &) = default;
        basic_text_exception(basic_text_exception &&) = default;
        explicit basic_text_exception(const string_type &text);
        explicit basic_text_exception(string_type &&text);
        explicit basic_text_exception(const std::exception &e);

        virtual ~basic_text_exception() noexcept override = default;

        basic_text_exception &operator=(const basic_text_exception &) = default;
        basic_text_exception &operator=(basic_text_exception &&) = default;

        virtual const char *what() const noexcept override;

    protected:
        string_type m_text;
    };

    template <class string_type_template>
    inline basic_text_exception<string_type_template>::basic_text_exception() : basic_text_exception{"tractor::basic_text_exception"}
    {
    }

    template <class string_type_template>
    inline basic_text_exception<string_type_template>::basic_text_exception(const string_type &text) : m_text{text}
    {
    }

    template <class string_type_template>
    inline basic_text_exception<string_type_template>::basic_text_exception(string_type &&text) : m_text{std::move(text)}
    {
    }

    template <class string_type_template>
    inline basic_text_exception<string_type_template>::basic_text_exception(const std::exception &e) : basic_text_exception{e.what()}
    {
    }

    template <class string_type_template>
    inline const char *basic_text_exception<string_type_template>::what() const noexcept
    {
        return m_text.c_str();
    }

    template <class traits_type_template = std::char_traits<char>, class allocator_type_template = std::allocator<char>>
    using text_exception_basic_string_char = basic_text_exception<std::basic_string<char, traits_type_template, allocator_type_template>>;
    using text_exception = basic_text_exception<>;
} // namespace tractor

// template struct numeric_code_translator;
// using using int_code_translator;
namespace tractor
{
    template <class code_type_template>
    struct numeric_code_translator
    {
    public:
        using code_type = code_type_template;
        using string_type = std::string;

        static_assert(std::is_same<typename string_type::value_type, char>::value, "the 'value_type' of 'string_type' is not 'char'");

        string_type translate(code_type code) const;
    };

    template <class code_type_template>
    inline auto numeric_code_translator<code_type_template>::translate(code_type code) const
        -> typename numeric_code_translator<code_type_template>::string_type
    {
        return std::to_string(code);
    }

    using int_code_translator = numeric_code_translator<int>;
} // namespace tractor

// tempalte struct basic_errno_code_translator;
// template using errno_code_translator_basic_string_char;
// using errno_code_translator;
namespace tractor
{
    template <class string_type_template = std::string>
    struct basic_errno_code_translator
    {
    public:
        using code_type = int;
        using string_type = string_type_template;

        string_type translate(code_type code) const;
    };

    template <class string_type_template>
    inline auto basic_errno_code_translator<string_type_template>::translate(code_type code) const
        -> typename basic_errno_code_translator<string_type_template>::string_type
    {
        return string_type{std::strerror(code)};
    }

    template <class traits_type_template = std::char_traits<char>, class allocator_type_template = std::allocator<char>>
    using errno_code_translator_basic_string_char = basic_errno_code_translator<std::basic_string<char, traits_type_template, allocator_type_template>>;
    using errno_code_translator = basic_errno_code_translator<>;
} // namespace tractor

// template class basic_code_exception;
// template using numeric_code_exception;
// using int_code_exception;
// using errno_code_exception;
namespace tractor
{
    template <class code_translator_type_template>
    class basic_code_exception : public exception_base
    {
    public:
        using code_type = typename code_translator_type_template::code_type;
        using string_type = typename code_translator_type_template::string_type;

        basic_code_exception(const code_translator_type_template &code_translator = code_translator_type_template{});
        basic_code_exception(const basic_code_exception &other) = default;
        basic_code_exception(basic_code_exception &&other) = default;
        explicit basic_code_exception(const code_type &code, const code_translator_type_template &code_translator = code_translator_type_template{});
        explicit basic_code_exception(code_type &&code, const code_translator_type_template &code_translator = code_translator_type_template{});

        virtual ~basic_code_exception() noexcept override = default;

        basic_code_exception &operator=(const basic_code_exception &) = default;
        basic_code_exception &operator=(basic_code_exception &&) = default;

        virtual const char *what() const noexcept override;
        virtual const code_type &code() const noexcept;

    protected:
        code_type m_code;
        string_type m_text;
    };

    template <class code_translator_type_template>
    inline basic_code_exception<code_translator_type_template>::basic_code_exception(const code_translator_type_template &code_translator) : basic_code_exception{code_type{}, code_translator}
    {
    }

    template <class code_translator_type_template>
    inline basic_code_exception<code_translator_type_template>::basic_code_exception(const code_type &code, const code_translator_type_template &code_translator) : m_code{code},
                                                                                                                                                                    m_text{code_translator.translate(m_code)}
    {
    }

    template <class code_translator_type_template>
    inline basic_code_exception<code_translator_type_template>::basic_code_exception(code_type &&code, const code_translator_type_template &code_translator) : m_code{std::move(code)},
                                                                                                                                                               m_text{code_translator.translate(m_code)}
    {
    }

    template <class code_translator_type_template>
    inline const char *basic_code_exception<code_translator_type_template>::what() const noexcept
    {
        return m_text.c_str();
    }

    template <class code_translator_type_template>
    inline auto basic_code_exception<code_translator_type_template>::code() const noexcept
        -> const code_type &
    {
        return m_code;
    }

    template <class code_type_template>
    using numeric_code_exception = basic_code_exception<numeric_code_translator<code_type_template>>;
    using int_code_exception = numeric_code_exception<int>;
    using errno_code_exception = basic_code_exception<errno_code_translator>;
} // namespace tractor

#endif // !defined TRACTOR_EXCEPTION_EXCEPTION_HPP
