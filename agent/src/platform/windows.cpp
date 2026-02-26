#include "agent/platform.hpp"

namespace platform
{
#ifdef _WIN32
    CpuMetrics collect_cpu()
    {
        return {0.0f, 0};
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