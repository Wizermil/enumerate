//
//  enumerateTests.m
//  enumerateTests
//
//  Created by Mathieu Garaud on 14/12/2017.
//  Copyright © 2017 Pretty Simple. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <enumerate/enumerate.h>
#include <vector>
#include <iostream>
#include <cmath>

struct A {
    A() : data(0) {
        std::cout << "A()" << '\n';
    }
    A(int dat) : data(dat) {
        std::cout << "A()" << '\n';
    }
    A(const A& rhs) {
        std::cout << "A(const A&)" << '\n';
        data = rhs.data;
    }
    A& operator=(const A& rhs) {
        std::cout << "operator=(const A&)" << '\n';
        data = rhs.data;
        return *this;
    }
    A(A&& rhs) noexcept {
        std::cout << "A(A&&)" << '\n';
        data = rhs.data;
    }
    A& operator=(A&& rhs) noexcept {
        std::cout << "operator=(A&&)" << '\n';
        data = rhs.data;
        return *this;
    }
    ~A() {
        std::cout << "~A()" << '\n';
    }

    int data;
};

@interface enumerateTests : XCTestCase

@end

@implementation enumerateTests

- (void)testExample {
    const std::vector<int> v0 {1, 2, 3};

    int i = 0;
    for (const auto& val : ps::enumerate(v0))
    {
        XCTAssertEqual(i++, val.index);
    }

    std::vector<int> v1 {1, 2, 3};
    int j = 0;
    for (const auto& val : ps::enumerate(v1))
    {
        XCTAssertEqual(j++, val.index);
        XCTAssertEqual(j, *val.iterator);
    }
    for (auto& val : ps::enumerate(v1))
    {
        *val.iterator *= 2;
    }

    std::vector<A*> v2;
    v2.reserve(3);
    v2.emplace_back(new A(1));
    v2.emplace_back(new A(2));
    v2.emplace_back(new A(3));

    int k = 0;
    for (const auto& val : ps::enumerate(v2))
    {
        XCTAssertEqual(k++, val.index);
        XCTAssertEqual(k, (*val.iterator)->data);
        delete (*val.iterator);
    }

    std::cout << '\n';

    std::vector<std::unique_ptr<A>> v3;
    v3.reserve(3);
    v3.emplace_back(std::make_unique<A>(1));
    v3.emplace_back(std::make_unique<A>(2));
    v3.emplace_back(std::make_unique<A>(3));

    int l = 0;
    for (const auto& val : ps::enumerate(v3))
    {
        XCTAssertEqual(l++, val.index);
        XCTAssertEqual(l, (*val.iterator)->data);
    }
}

static constexpr std::size_t num_sample = 500000000;

- (void)testForRange {
    [self measureMetrics:[self class].defaultPerformanceMetrics automaticallyStartMeasuring:NO forBlock:^{
        std::vector<std::size_t> data;
        data.reserve(num_sample);
        for (std::size_t i = 0; i < num_sample; ++i)
        {
            data.emplace_back(i);
        }

        std::size_t total = 0;
        std::size_t index = 0;

        [self startMeasuring];
        for (const auto& val : data)
        {
            total += val * ++index;
        }
        [self stopMeasuring];

        std::cout << total << '\n';
    }];
}

- (void)testForRaw {
    [self measureMetrics:[self class].defaultPerformanceMetrics automaticallyStartMeasuring:NO forBlock:^{
        std::vector<std::size_t> data;
        data.reserve(num_sample);
        for (std::size_t i = 0; i < num_sample; ++i)
        {
            data.emplace_back(i);
        }

        std::size_t total = 0;

        [self startMeasuring];
        for (std::size_t index = 0; index < num_sample; ++index)
        {
            total += data[index] * index;
        }
        [self stopMeasuring];

        std::cout << total << '\n';
    }];
}

- (void)testForEnumerate {
    [self measureMetrics:[self class].defaultPerformanceMetrics automaticallyStartMeasuring:NO forBlock:^{
        std::vector<std::size_t> data;
        data.reserve(num_sample);
        for (std::size_t i = 0; i < num_sample; ++i)
        {
            data.emplace_back(i);
        }

        std::size_t total = 0;

        [self startMeasuring];
        for (const auto& val : ps::enumerate(data))
        {
            total += *val.iterator * val.index;
        }
        [self stopMeasuring];

        std::cout << total << '\n';
    }];
}

@end
