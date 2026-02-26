#pragma once
#include <cstdint>
#include <vector>

struct CpuMetrics
{
    float total_usage_percent;
    uint32_t cores;
    std::vector<float> cores_usage_percent; 
};

struct MemoryMetrics
{
    uint64_t used_mb;
    uint64_t total_md;
};

struct DiskMetrics
{
    uint64_t used_gb;
    uint64_t total_gd;
};

struct MetricsSnapshot
{
    uint64_t timestamp;
    CpuMetrics cpu;
    MemoryMetrics memory;
    DiskMetrics disk;
};