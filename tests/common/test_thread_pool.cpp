
#include <task_thread_pool.hpp>

#include <atomic>
#include <chrono>
#include <thread>

#include <catch.hpp>
using namespace ssp4cpp::common;

TEST_CASE("ThreadPool executes simple tasks", "[threadpool]")
{

    std::cout << "\n";
    std::atomic<int> counter{0};
    // {
        ThreadPool pool(2);
        auto f1 = pool.enqueue([&]
                               { counter++; });
        auto f2 = pool.enqueue([&]
                               { counter += 2; });
        f1.get();
        f2.get();
    // }
    REQUIRE(counter == 3);
}

TEST_CASE("ThreadPool handles many tasks", "[threadpool]")
{
    std::atomic<int> sum{0};
    // {
        ThreadPool pool(4);
        std::vector<std::future<void>> futures;
        for (int i = 0; i < 100; ++i)
        {
            futures.push_back(pool.enqueue([&sum, i]
                                           { sum += i; }));
        }
        for (auto &f : futures)
            f.get();
    // }
    REQUIRE(sum == 4950); // sum 0..99
}

TEST_CASE("ThreadPool supports void and non-void tasks", "[threadpool]")
{
    std::future<int> f1;
    std::future<void> f2;
    // {
        ThreadPool pool(2);
        f1 = pool.enqueue([]
                          { return 42; });
        f2 = pool.enqueue([] {});
    // }
    REQUIRE(f1.get() == 42);
    f2.get(); // should not throw
}

TEST_CASE("ThreadPool can handle tasks with delay", "[threadpool]")
{
    std::future<int> f;
    using namespace std::chrono_literals;
    // {
        ThreadPool pool(2);
        f = pool.enqueue([]
                         {
            std::this_thread::sleep_for(50ms);
            return 7; });
    // }
    REQUIRE(f.get() == 7);
}
