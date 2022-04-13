/**
 * 一个简单的cpp程序计时器
*/
#pragma once
#include <iostream>
#include <chrono>

class CPPTimer {
private:
  std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
public:
  CPPTimer() {
    Begin();
  }

  ~CPPTimer() {
    Stop();
  }

  void Begin() {
    m_StartTimepoint = std::chrono::high_resolution_clock::now();
  }

  void Stop() {
    auto endTimePoint = std::chrono::high_resolution_clock::now();

    auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint);
    auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint);

    auto duration = end - start;
    double ms = duration.count() * 0.001;

    std::cout << duration.count() << "us (" << ms << "ms)\n";
  }

};