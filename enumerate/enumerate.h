//
// enumerate.h
// enumerate
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

#ifndef ENUMERATE_ENUMERATE_H
#define ENUMERATE_ENUMERATE_H

#ifdef __cplusplus
#define ENUMERATE_EXTERN extern "C"
#else
#define ENUMERATE_EXTERN
#endif

//! Project version number for future.
ENUMERATE_EXTERN double enumerateVersionNumber;

//! Project version string for future.
ENUMERATE_EXTERN const unsigned char enumerateVersionString[];

#include <enumerate/enumerate.hpp>

#endif // ENUMERATE_ENUMERATE_H
