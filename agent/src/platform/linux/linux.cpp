#include "agent/platform.hpp"
#include "agent/linux/cpuinfo.hpp"

#include <thread>
#include <chrono>

namespace platform
{
#ifdef __linux__
    CpuMetrics collect_cpu()
    {
        static CpuTimes prev = read_cpu_times();
        std::this_thread::sleep_for(std::chrono::duration<uint64_t>(1));
        CpuTimes curr = read_cpu_times();

        float usage = cpu_usage(prev, curr);
        prev = curr;

        std::vector<CpuTimes> cores_info = read_total_cpu_times();

        uint32_t cores = cpu_cores();

        CpuMetrics cm{};
        cm.cores = cores;
        cm.total_usage_percent = usage;
        return cm;
    }

    MemoryMetrics collect_memory()
    {
        return {0, 0};
    }

    DiskMetrics collect_disk()
    {
        return {0, 0};
    }
#endif
}