#include <catch.hpp>


#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>
#include <execution>
 

namespace execution = std::execution;

 
std::chrono::milliseconds measure([[maybe_unused]] auto policy, std::vector<std::uint64_t> v)
{
    const auto start = std::chrono::steady_clock::now();
    std::sort(policy, v.begin(), v.end());
    const auto finish = std::chrono::steady_clock::now();
    return  std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
}

TEST_CASE("Check parallel speed", "[Environment]") {
    std::vector<std::uint64_t> v(1'000'000);
    std::mt19937 gen {std::random_device{}()};
    std::ranges::generate(v, gen);
 
    auto seq = measure(execution::seq, v);
    auto unseq = measure(execution::unseq, v);
    auto par_unseq = measure(execution::par_unseq, v);
    auto par = measure(execution::par, v);

    std::cout << "seq: " << seq << " unseq: " << unseq << " par_unseq: " << par_unseq << " par: " << par << std::endl;

}
