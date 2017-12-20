//
//  enumerate.hpp
//  enumerate
//
// Created by Mathieu Garaud on 14/12/2017.
//
// MIT License
//
// Copyright © 2017 Pretty Simple
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#ifndef ENUMERATE_ENUMERATE_HPP
#define ENUMERATE_ENUMERATE_HPP

#include <iterator>
#include <type_traits>
#include <utility>

namespace ps
{
    template<class T, class I>
    struct wrapper_indexed_iterator
    {
        typename T::size_type index;
        I iterator;
    };

    template<class T, class I>
    class indexed_iterator
    {
        wrapper_indexed_iterator<T, I> _warp;
    public:
        using size_type = typename T::size_type;
        using value_type = wrapper_indexed_iterator<T, I>;
        using difference_type = std::ptrdiff_t;
        using pointer = wrapper_indexed_iterator<T, I>*;
        using reference = wrapper_indexed_iterator<T, I>&;
        using iterator_category = std::random_access_iterator_tag;

        indexed_iterator() =default;
        indexed_iterator(const indexed_iterator&) =default;
        indexed_iterator& operator=(const indexed_iterator&) =default;
        indexed_iterator(indexed_iterator&&) noexcept =default;
        indexed_iterator& operator=(indexed_iterator&&) noexcept =default;
        ~indexed_iterator() =default;

        inline reference operator*()
        {
            return _warp;
        }

        inline indexed_iterator& operator++()
        {
            ++_warp.iterator;
            ++_warp.index;
            return *this;
        }
        inline indexed_iterator operator++(int)
        {
            indexed_iterator<T, I> tmp(*this);
            ++(*this);
            return tmp;
        }

        inline indexed_iterator& operator--()
        {
            --_warp.iterator;
            --_warp.index;
            return *this;
        }
        inline indexed_iterator operator--(int)
        {
            indexed_iterator<T, I> tmp(*this);
            --(*this);
            return tmp;
        }

        inline bool operator==(const indexed_iterator& rhs) const
        {
            return _warp.iterator == rhs._warp.iterator;
        }
        inline bool operator!=(const indexed_iterator& rhs) const
        {
            return _warp.iterator != rhs._warp.iterator;
        }

        inline bool operator<(const indexed_iterator& rhs) const
        {
            return _warp.iterator < rhs._warp.iterator;
        }
        inline bool operator>(const indexed_iterator& rhs) const
        {
            return _warp.iterator > rhs._warp.iterator;
        }
        inline bool operator<=(const indexed_iterator& rhs) const
        {
            return _warp.iterator <= rhs._warp.iterator;
        }
        inline bool operator>=(const indexed_iterator& rhs) const
        {
            return _warp.iterator >= rhs._warp.iterator;
        }

        indexed_iterator& operator+(difference_type n) const
        {
            indexed_iterator<T, I> tmp(*this);
            tmp += n;
            return tmp;
        }
        inline indexed_iterator& operator+=(difference_type n)
        {
            _warp.iterator += n;
            _warp.index += n;
            return *this;
        }
        indexed_iterator& operator-(difference_type n) const
        {
            return *this + (-n);
        }
        indexed_iterator& operator-=(difference_type n)
        {
            *this += -n;
            return *this;
        }

        reference operator[](difference_type n)
        {
            return *(*this + n);
        }
    protected:
        template<class U>
        friend class indexed_container;

        explicit indexed_iterator(size_type index, I&& it) : _warp{index, std::forward<I>(it)}
        {
        }
    };
    
    template<class C>
    class indexed_container
    {
        static_assert(std::is_reference<C>::value, "Make sure that we are not copying the original container");

        C _container;
        using _Type = typename std::remove_reference<C>::type;

    public:
        using value_type = typename _Type::value_type;
        using allocator_type = typename _Type::allocator_type;
        using size_type = typename _Type::size_type;
        using difference_type = typename _Type::difference_type;
        using reference = typename _Type::reference;
        using const_reference = typename _Type::const_reference;
        using pointer = typename _Type::pointer;
        using const_pointer = typename _Type::const_pointer;
        using iterator = indexed_iterator<_Type, typename _Type::iterator>;
        using const_iterator = indexed_iterator<_Type, typename _Type::const_iterator>;
        using reverse_iterator = indexed_iterator<_Type, typename _Type::reverse_iterator>;
        using const_reverse_iterator = indexed_iterator<_Type, typename _Type::const_reverse_iterator>;

        indexed_container() =default;
        indexed_container(const indexed_container&) =default;
        indexed_container& operator=(const indexed_container&) =default;
        indexed_container(indexed_container&&) noexcept =default;
        indexed_container& operator=(indexed_container&&) noexcept =default;
        ~indexed_container() =default;

        inline iterator begin() noexcept
        {
            return iterator(0, _container.begin());
        }
        inline const_iterator begin() const noexcept
        {
            return const_iterator(0, _container.begin());
        }
        inline const_iterator cbegin() const noexcept
        {
            return const_iterator(0, _container.cbegin());
        }

        inline iterator end() noexcept
        {
            return iterator(_container.size(), _container.end());
        }
        inline const_iterator end() const noexcept
        {
            return const_iterator(_container.size(), _container.end());
        }
        inline const_iterator cend() const noexcept
        {
            return const_iterator(_container.size(), _container.cend());
        }

        inline reverse_iterator rbegin() noexcept
        {
            return reverse_iterator(_container.size()-1, _container.rbegin());
        }
        inline const_reverse_iterator rbegin() const noexcept
        {
            return const_reverse_iterato(_container.size()-1, _container.rbegin());
        }
        inline const_reverse_iterator crbegin() const noexcept
        {
            return const_reverse_iterator(_container.size()-1, _container.crbegin());
        }

        inline reverse_iterator rend() noexcept
        {
            return reverse_iterator(0, _container.rend());
        }
        inline const_reverse_iterator rend() const noexcept
        {
            return const_reverse_iterator(0, _container.rend());
        }
        inline const_reverse_iterator crend() const noexcept
        {
            return const_reverse_iterator(0, _container.crend());
        }

    protected:
        template<class T>
        friend const indexed_container<const T&> enumerate(const T&) noexcept;
        template<class T>
        friend indexed_container<T&> enumerate(T&) noexcept;

        explicit indexed_container(C container) : _container(container)
        {
        }
    };

    template<class C>
    const indexed_container<const C&> enumerate(const C& container) noexcept
    {
        using traits = std::iterator_traits<decltype(std::begin(std::declval<C>()))>;
        static_assert(std::is_same<typename traits::iterator_category, std::random_access_iterator_tag>::value, "");

        return indexed_container<const C&>(container);
    }

    template<class C>
    indexed_container<C&> enumerate(C& container) noexcept
    {
        using traits = std::iterator_traits<decltype(std::begin(std::declval<C>()))>;
        static_assert(std::is_same<typename traits::iterator_category, std::random_access_iterator_tag>::value, "");

        return indexed_container<C&>(container);
    }

}

#endif // ENUMERATE_ENUMERATE_HPP
