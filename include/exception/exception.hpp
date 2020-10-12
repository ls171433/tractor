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

    public:
        basic_text_exception() : basic_text_exception{"tractor::basic_text_exception"} {}
        explicit basic_text_exception(const string_type &text) : m_text{text} {}
        explicit basic_text_exception(string_type &&text) : m_text{std::move(text)} {}
        explicit basic_text_exception(const std::exception &e) : basic_text_exception{e.what()} {}

        basic_text_exception(const basic_text_exception &) = default;
        basic_text_exception(basic_text_exception &&) = default;

        virtual ~basic_text_exception() noexcept override = default;

        basic_text_exception &operator=(const basic_text_exception &) = default;
        basic_text_exception &operator=(basic_text_exception &&) = default;

        virtual const char *what() const noexcept override { return m_text.c_str(); }

    protected:
        string_type m_text;
    };

    template <class traits_type_template = std::char_traits<char>, class allocator_type_template = std::allocator<char>>
    using text_exception_basic_string_char = basic_text_exception<std::basic_string<char, traits_type_template, allocator_type_template>>;
    using text_exception = basic_text_exception<>;
} // namespace tractor

// template struct basic_code_translator
namespace tractor
{
    template <class code_type_template = int, class string_type_template = std::string>
    struct basic_code_translator
    {
    public:
        using code_type = code_type_template;
        using string_type = string_type_template;

        static_assert(std::is_same<typename string_type::value_type, char>::value, "the 'value_type' of 'string_type' is not 'char'");

    public:
        virtual string_type translate(const code_type &code) const { return string_type{"tractor::basic_code_translator"}; }
    };
} // namespace tractor

// template struct numeric_code_translator;
// using int_code_translator;
namespace tractor
{
    template <class code_type_template>
    struct numeric_code_translator : public basic_code_translator<code_type_template>
    {
    public:
        using parent_type = basic_code_translator<code_type_template>;
        using typename parent_type::code_type;
        using typename parent_type::string_type;

    public:
        virtual string_type translate(const code_type &code) const override { return std::to_string(code); }
    };

    using int_code_translator = numeric_code_translator<int>;
} // namespace tractor

// tempalte struct basic_errno_code_translator;
// template using errno_code_translator_basic_string_char;
// using errno_code_translator;
namespace tractor
{
    template <class string_type_template = std::string>
    struct basic_errno_code_translator : public basic_code_translator<int, string_type_template>
    {
    public:
        using parent_type = basic_code_translator<int, string_type_template>;
        using typename parent_type::code_type;
        using typename parent_type::string_type;

    public:
        virtual string_type translate(const code_type &code) const override { return string_type{std::strerror(code)}; }
    };

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
    class basic_code_exception : public basic_text_exception<typename code_translator_type_template::string_type>
    {
    public:
        using parent_type = basic_text_exception<typename code_translator_type_template::string_type>;
        using typename parent_type::string_type;

        using code_translator_type = code_translator_type_template;
        using code_type = typename code_translator_type::code_type;

    public:
        basic_code_exception() : basic_code_exception(code_type{}, code_translator_type{}) {}
        explicit basic_code_exception(const code_type &code) : basic_code_exception(code, code_translator_type{}) {}
        explicit basic_code_exception(code_type &&code) : basic_code_exception(std::move(code), code_translator_type{}) {}
        explicit basic_code_exception(const code_translator_type_template &code_translator) : basic_code_exception(code_type{}, code_translator) {}
        basic_code_exception(const code_type &code, const code_translator_type_template &code_translator)
            : parent_type{code_translator.translate(code)}, m_code{code} {}
        basic_code_exception(code_type &&code, const code_translator_type_template &code_translator)
            : parent_type{code_translator.translate(code)}, m_code{std::move(code)} {}

        basic_code_exception(const basic_code_exception &other) = default;
        basic_code_exception(basic_code_exception &&other) = default;

        virtual ~basic_code_exception() noexcept override = default;

        basic_code_exception &operator=(const basic_code_exception &) = default;
        basic_code_exception &operator=(basic_code_exception &&) = default;

        virtual const code_type &code() const noexcept { return m_code; }

    protected:
        code_type m_code;
    };

    template <class code_type_template>
    using numeric_code_exception = basic_code_exception<numeric_code_translator<code_type_template>>;
    using int_code_exception = numeric_code_exception<int>;
    using errno_code_exception = basic_code_exception<errno_code_translator>;
} // namespace tractor

#endif // !defined TRACTOR_EXCEPTION_EXCEPTION_HPP
