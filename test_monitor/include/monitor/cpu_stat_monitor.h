#pragma once

#include <string>
#include <unordered_map>

#include "monitor/monitor_inter.h"
#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

namespace monitor {
class CpuStatMonitor : public MonitorInter {
  struct CpuStat {
    std::string cpu_name; 
    float user; // 用户使用率
    float system; // 系统使用率
    float idle; // 空闲时间
    float nice; // 用户态在低优先级花费的cpu时间
    float io_wait; // 
    float irq; // 硬中断
    float soft_irq; // 软中断
    float steal; 
    float guest;
    float guest_nice;
  };

 public:
  CpuStatMonitor() {}
  void UpdateOnce(monitor::proto::MonitorInfo* monitor_info);
  void Stop() override {}

 private:
  std::unordered_map<std::string, struct CpuStat> cpu_stat_map_;
};

}  // namespace monitor
