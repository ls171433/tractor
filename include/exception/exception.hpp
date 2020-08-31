#if !defined TRACTOR_EXCEPTION_EXCEPTION_HPP



// for std::exception
#include <exception>
// for std::string
#include <string>



namespace tractor
{
    class text_exception : public std::exception
    {
    public:
        text_exception();
        text_exception(const text_exception& other);
        text_exception(text_exception&& other);
        text_exception(const std::string& text);
        text_exception(const std::exception& e);

        virtual ~text_exception() noexcept;

        text_exception& operator=(const text_exception&);
        text_exception& operator=(text_exception&&);

        virtual const char* what() noexcept;

    protected:
        std::string m_text;
    };
}



#endif // !defined TRACTOR_EXCEPTION_EXCEPTION_HPP
