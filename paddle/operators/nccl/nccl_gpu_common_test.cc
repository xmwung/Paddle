#include "paddle/operators/nccl/nccl_gpu_common.h"

#include <gtest/gtest.h>

#include <chrono>
#include <thread>
#include <vector>

namespace paddle {
namespace platform {

TEST(WaitGroup, wait) {
  WaitGroup wg;
  auto run_thread = [&wg](int idx) {
    wg.Add(1);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    wg.Done();
  };

  std::vector<std::thread> ths;
  constexpr const int TNUM = 5;
  for (int i = 0; i < TNUM; ++i) {
    ths.emplace_back(std::thread(run_thread, i));
  }
  wg.Wait();

  for (int i = 0; i < TNUM; ++i) {
    ths[i].join();
  }
}

}  // namespace platform
}  // namespace paddle
