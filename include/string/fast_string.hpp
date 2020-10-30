#if !defined TRACTOR_STRING_FAST_STRING_HPP
#define TRACTOR_STRING_FAST_STRING_HPP

#include <array>
#include <stdexcept>
// for std::string
#include <string>
// for std::allocator
#include <memory>

namespace tractor
{
    template <class char_type_template, size_t max_size_template, class traits_type_template = std::char_traits<char_type_template>>
    class basic_stack_string
    {
    public:
        using char_type = char_type_template;
        using array_type = std::array<char_type, max_size_template + 1>;

        using value_type = char_type;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = value_type &;
        using const_reference = const value_type &;
        using pointer = value_type *;
        using const_pointer = const value_type *;
        using iterator = typename array_type::iterator;
        using const_iterator = typename array_type::const_iterator;
        using reverse_iterator = typename array_type::reverse_iterator;
        using const_reverse_iterator = typename array_type::const_reverse_iterator;

    public:
        // constructors
        basic_stack_string() noexcept
        {
            m_size = size_type();
            m_array[m_size] = char_type();
        }
        basic_stack_string(size_type count, char_type c)
        {
            if (count > static_max_size())
            {
                throw std::length_error{"'count' too large"};
            }

            for (size_type i = size_type(); i < count; ++i)
            {
                m_array[i] = c;
            }

            m_size = count;
            m_array[m_size] = char_type();
        }
        basic_stack_string(const basic_stack_string &other, size_type pos, size_type count)
        {
            if (pos > other.size())
            {
                throw std::out_of_range("'pos' out of range");
            }

            size_type real_count = size_type();
            for (size_type i = size_type(); i < count && pos + i < other.size(); ++i, ++real_count)
            {
                m_array[i] = other[pos + i];
            }

            m_size = real_count;
            m_array[m_size] = char_type();
        }
        basic_stack_string(const basic_stack_string &other, size_type pos)
        {
            if (pos > other.size())
            {
                throw std::out_of_range("'pos' out of range");
            }

            size_type real_count = size_type();
            for (size_type i = size_type(); pos + i < other.size(); ++i, ++real_count)
            {
                m_array[i] = other[pos + i];
            }

            m_size = real_count;
            m_array[m_size] = char_type();
        }
        basic_stack_string(const_pointer s, size_type count)
        {
            if (count > static_max_size())
            {
                throw std::length_error{"'count' too large"};
            }

            for (size_type i = size_type(); i < count; ++i)
            {
                m_array[i] = s[i];
            }

            m_size = count;
            m_array[m_size] = char_type();
        }
        basic_stack_string(const_pointer s)
        {
            size_type real_count = size_type();
            for (const_pointer current = s; *current != char_type(); ++current, ++real_count)
            {
                if (!(real_count < static_max_size()))
                {
                    throw std::length_error{"input size too large"};
                }

                m_array[real_count] = *current;
            }

            m_size = real_count;
            m_array[m_size] = char_type();
        }
        template <class input_iterator_template>
        basic_stack_string(input_iterator_template first, input_iterator_template last)
        {
            using input_iterator = input_iterator_template;

            size_type real_count = size_type();
            for (input_iterator current = first; current != last; ++current, ++real_count)
            {
                if (!(real_count < static_max_size()))
                {
                    throw std::length_error{"input size too large"};
                }

                m_array[real_count] = *current;
            }

            m_size = real_count;
            m_array[m_size] = char_type();
        }
        basic_stack_string(std::initializer_list<char_type> ilist)
        {
            using input_iterator = typename std::initializer_list<char_type>::iterator;

            size_type count = ilist.size();
            if (count > static_max_size())
            {
                throw std::length_error{"input size too large"};
            }

            size_type real_count = size_type();
            for (input_iterator current = ilist.begin(); current != ilist.end(); ++current, ++real_count)
            {
                m_array[real_count] = *current;
            }

            m_size = count;
            m_array[m_size] = char_type();
        }

        basic_stack_string(const basic_stack_string &other) = default;
        basic_stack_string(basic_stack_string &&other) = default;

        // destructor
        ~basic_stack_string() = default;

        // assign
        basic_stack_string &operator=(const basic_stack_string &) noexcept = default;
        basic_stack_string &operator=(basic_stack_string &&) noexcept = default;

        // element access
        reference at(size_type pos)
        {
            if (pos >= size())
            {
                throw std::out_of_range("'pos' out of range");
            }

            return m_array[pos];
        }
        const_reference at(size_type pos) const
        {
            if (pos >= size())
            {
                throw std::out_of_range("'pos' out of range");
            }

            return m_array[pos];
        }

        reference operator[](size_type position) { return m_array[position]; }
        const_reference operator[](size_type position) const { return m_array[position]; }

        reference front() { return m_array[0]; }
        const_reference front() const { return m_array[0]; }

        reference back() { return m_array[size() - 1]; }
        const_reference back() const { return m_array[size() - 1]; }

        pointer data() noexcept { return &m_array.front(); }
        const_pointer data() const noexcept { return &m_array.front(); }

        const_pointer c_str() const noexcept { return data(); }

        // iterators
        iterator begin() noexcept { return m_array.begin(); }
        const_iterator begin() const noexcept { return cbegin(); }
        const_iterator cbegin() const noexcept { return m_array.cbegin(); }

        iterator end() noexcept { return begin() + size(); }
        const_iterator end() const noexcept { return cend(); }
        const_iterator cend() const noexcept { return cbegin() + size(); }

        reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
        const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }

        reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
        const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

        // capacity
        bool empty() const noexcept { return size() == size_type(); }

        size_type size() const noexcept { return m_size; }
        size_type length() const noexcept { return size(); }

        static size_type static_max_size() noexcept { return max_size_template; }
        size_type max_size() const noexcept { return max_size_template; }

        void reserve(size_type new_capacity)
        {
            if (new_capacity > static_max_size())
            {
                throw std::length_error{"'new_capacity' too large"};
            }
        }
        void reserve() {}

        size_type capacity() const noexcept { return max_size_template; }

        void shrink_to_fit() {}

        // operations
        void push_back(char_type c)
        {
        }

    protected:
        array_type m_array;
        size_type m_size;
    };

    template <size_t array_size>
    using stack_string = basic_stack_string<char, array_size>;
} // namespace tractor

#endif // !defined TRACTOR_STRING_FAST_STRING_HPP
