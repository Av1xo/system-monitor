#pragma once
#include "metrics.hpp"

namespace platform
{
    CpuMetrics collect_cpu();
    MemoryMetrics collect_memory();
    DiskMetrics collect_disk();
}