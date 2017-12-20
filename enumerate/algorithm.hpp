//
//  algorithm.hpp
//  enumerate
//
// Created by Mathieu Garaud on 20/12/2017.
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

#ifndef ENUMERATE_ALGORITHM_HPP
#define ENUMERATE_ALGORITHM_HPP

#include <iterator>
#include <type_traits>

namespace ps
{
    template<class Range, class Function>
    inline Function for_enumerate(Range&& r, Function&& f)
    {
        using traits = std::iterator_traits<decltype(std::begin(std::declval<Range>()))>;
        static_assert(std::is_same<typename traits::iterator_category, std::random_access_iterator_tag>::value, "");

        for(typename std::decay_t<Range>::size_type i = 0; i < r.size(); ++i)
        {
            f(i, r[i]);
        }
        return f;
    }
}

#endif // ENUMERATE_ALGORITHM_HPP
