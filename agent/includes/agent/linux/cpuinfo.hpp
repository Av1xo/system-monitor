#pragma once

#include "agent/metrics.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
#include <iostream>
#include <vector>

namespace platform
{

struct CpuTimes
{
    uint64_t user, nice, system, idle, iowait;
    uint64_t irq, softirq, steal;
};

uint32_t cpu_cores()
{
    std::ifstream file("/proc/cpuinfo");
    uint32_t cores = 0;
    std::string line;

    while (std::getline(file, line))
    {
        if (line.rfind("processor", 0) == 0)
            cores++;
    }

    return cores;
}

std::vector<CpuTimes> read_total_cpu_times()
{
    std::ifstream file("/proc/stat");
    if (!file)
        return {};
    
    std::string line;
    std::vector<CpuTimes> cores_times{};
    cores_times.reserve(static_cast<size_t>(32));

    while (std::getline(file, line))
    {
        if (line.rfind("cpu", 0) != 0)
            break;

        std::istringstream iss(line);
        std::string label;

        CpuTimes t{};
        if 
        (!(  
            iss >> label
                >> t.user >> t.nice >> t.system >> t.idle
                >> t.iowait >> t.irq >> t.softirq >> t.steal
        ))
        {
            break;
        }

        cores_times.push_back(t);
    }

    // [cpu, cpu0, cpu1, cpu2 ... cpu[total_cores - 1]]
    return cores_times;
}

CpuTimes read_cpu_times()
{
    std::ifstream file("/proc/stat");
    std::string line;
    std::getline(file, line);

    std::istringstream iss(line);
    std::string cpu;

    CpuTimes t{};
    iss >> cpu
        >> t.user >> t.nice >> t.system >> t.idle
        >> t.iowait >> t.irq >> t.softirq >> t.steal;

    return t;
}

float cpu_usage(const CpuTimes& a, const CpuTimes& b)
{
    uint64_t idle_a = a.idle + a.iowait;
    uint64_t idle_b = b.idle + b.iowait;

    uint64_t total_a =
        a.user + a.nice + a.system + idle_a +
        a.irq + a.softirq + a.steal;

    uint64_t total_b =
        b.user + b.nice + b.system + idle_b +
        b.irq + b.softirq + b.steal;

    uint64_t delta_total = total_b - total_a;
    uint64_t delta_idle = idle_b - idle_a;

    if (delta_total == 0) return 0.0f;

    return (1.0f - (float)delta_idle / delta_total) * 100.f;
}

class CpuUsageCalculator
{
public:
    CpuUsageCalculator() = default;

    CpuUsageCalculator(const CpuUsageCalculator&) = delete;
    CpuUsageCalculator& operator=(const CpuUsageCalculator&) = delete;

    CpuUsageCalculator(CpuUsageCalculator&&) = default;
    CpuUsageCalculator& operator=(CpuUsageCalculator&&) = default;

    CpuMetrics update(const std::vector<CpuTimes>& curr);
private:
    std::vector<CpuTimes> prev_;
};
}