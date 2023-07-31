#include "monitor_widget.h"

namespace monitor {

MonitorWidget::MonitorWidget(QWidget *parent) {}

QWidget *MonitorWidget::ShowAllMonitorWidget(const std::string &name) {
  QWidget *widget = new QWidget();
  // stack窗口布局
  stack_menu_ = new QStackedLayout();
  stack_menu_->addWidget(InitCpuMonitorWidget());
  stack_menu_->addWidget(InitSoftIrqMonitorWidget());
  stack_menu_->addWidget(InitMemMonitorWidget());
  stack_menu_->addWidget(InitNetMonitorWidget());
  //
  QGridLayout *layout = new QGridLayout(this);
  layout->addWidget(InitButtonMenu(name), 1, 0);
  layout->addLayout(stack_menu_, 2, 0);
  //
  widget->setLayout(layout);
  return widget;
}

QWidget *MonitorWidget::InitButtonMenu(const std::string &name) {
  // char *name = getenv("USER");
  // 创建4个按钮
  QPushButton *cpu_button =
      new QPushButton(QString::fromStdString(name) + "_cpu", this);
  QPushButton *soft_irq_button =
      new QPushButton(QString::fromStdString(name) + "_soft_irq", this);
  QPushButton *mem_button =
      new QPushButton(QString::fromStdString(name) + "_mem", this);
  QPushButton *net_button =
      new QPushButton(QString::fromStdString(name) + "_net", this);
  // 设置按键的字体
  QFont *font = new QFont("Microsoft YaHei", 15, 40);
  cpu_button->setFont(*font);
  soft_irq_button->setFont(*font);
  mem_button->setFont(*font);
  net_button->setFont(*font);
  // 按键布局
  QHBoxLayout *layout = new QHBoxLayout();
  layout->addWidget(cpu_button);
  layout->addWidget(soft_irq_button);
  layout->addWidget(mem_button);
  layout->addWidget(net_button);
  // 见布局放在QWidge对象中 并返回
  QWidget *widget = new QWidget();
  widget->setLayout(layout);

  connect(cpu_button, SIGNAL(clicked()), this, SLOT(ClickCpuButton()));
  connect(soft_irq_button, SIGNAL(clicked()), this, SLOT(ClickSoftIrqButton()));
  connect(mem_button, SIGNAL(clicked()), this, SLOT(ClickMemButton()));
  connect(net_button, SIGNAL(clicked()), this, SLOT(ClickNetButton()));

  return widget;
}

QWidget *MonitorWidget::InitCpuMonitorWidget() {
  // 创建CPU监控的窗口（包括CPU负载、CPU状态两个标签和表格）
  QWidget *widget = new QWidget();
  // 创建CPU负载标签
  QLabel *cpu_load_label = new QLabel(this);
  cpu_load_label->setText(tr("Monitor CpuLoad:"));
  cpu_load_label->setFont(QFont("Microsoft YaHei", 10, 40));
  // 创建CPU负载表格
  cpu_load_monitor_view_ = new QTableView;
  cpu_load_model_ = new CpuLoadModel;                 // CPU负载数据模型
  cpu_load_monitor_view_->setModel(cpu_load_model_);  // 将模型放在表格中
  cpu_load_monitor_view_->show();                     // 展示表格
  // 创建CPU状态标签
  QLabel *cpu_stat_label = new QLabel(this);
  cpu_stat_label->setText(tr("Monitor CpuStat:"));
  cpu_stat_label->setFont(QFont("Microsoft YaHei", 10, 40));
  // 创建CPU状态表格
  cpu_stat_monitor_view_ = new QTableView;
  cpu_stat_model_ = new CpuStatModel;
  cpu_stat_monitor_view_->setModel(cpu_stat_model_);
  cpu_stat_monitor_view_->show();
  // 网格化布局
  QGridLayout *layout = new QGridLayout();
  // 布局
  layout->addWidget(cpu_load_label, 3, 0);
  layout->addWidget(cpu_load_monitor_view_, 4, 0, 2, 2);

  layout->addWidget(cpu_stat_label, 1, 0, 1, 1);
  layout->addWidget(cpu_stat_monitor_view_, 2, 0, 1, 2);
  // 将窗口设置为这个布局
  widget->setLayout(layout);
  return widget;
}

QWidget *MonitorWidget::InitSoftIrqMonitorWidget() {
  // 创建用于放软中断监控的窗口
  QWidget *widget = new QWidget();
  // 标签
  QLabel *monitor_label = new QLabel(this);
  monitor_label->setText(tr("Monitor softirq:"));
  monitor_label->setFont(QFont("Microsoft YaHei", 10, 40));
  // 表格和模型
  monitor_view_ = new QTableView;
  monitor_model_ = new MonitorBaseModel;
  QSortFilterProxyModel *sort_proxy = new QSortFilterProxyModel(this);  // 排序
  sort_proxy->setSourceModel(monitor_model_);  // monitor_model_设为源模型
  monitor_view_->setModel(sort_proxy);         // NOTE!
  monitor_view_->setSortingEnabled(true);
  monitor_view_->show();  // NOTE!
  // 布局
  QGridLayout *layout = new QGridLayout();
  layout->addWidget(monitor_label, 1, 0);
  layout->addWidget(monitor_view_, 2, 0, 1, 2);

  widget->setLayout(layout);
  return widget;
}

QWidget *MonitorWidget::InitMemMonitorWidget() {
  QWidget *widget = new QWidget();

  QLabel *mem_label = new QLabel(this);
  mem_label->setText(tr("Monitor mem:"));
  mem_label->setFont(QFont("Microsoft YaHei", 10, 40));

  mem_monitor_view_ = new QTableView;
  mem_model_ = new MemModel;
  mem_monitor_view_->setModel(mem_model_);
  mem_monitor_view_->show();

  QGridLayout *layout = new QGridLayout();

  layout->addWidget(mem_label, 1, 0);
  layout->addWidget(mem_monitor_view_, 2, 0, 1, 1);

  widget->setLayout(layout);
  return widget;
}

QWidget *MonitorWidget::InitNetMonitorWidget() {
  QWidget *widget = new QWidget();

  QLabel *net_label = new QLabel(this);
  net_label->setText(tr("Monitor net:"));
  net_label->setFont(QFont("Microsoft YaHei", 10, 40));

  net_monitor_view_ = new QTableView;
  net_model_ = new NetModel;
  net_monitor_view_->setModel(net_model_);
  net_monitor_view_->show();  // 这一行是不是可以删除

  QGridLayout *layout = new QGridLayout();

  layout->addWidget(net_label, 1, 0);
  layout->addWidget(net_monitor_view_, 2, 0, 1, 1);

  widget->setLayout(layout);
  return widget;
}

void MonitorWidget::UpdateData(
    const monitor::proto::MonitorInfo &monitor_info) {
  monitor_model_->UpdateMonitorInfo(monitor_info);
  cpu_load_model_->UpdateMonitorInfo(monitor_info);
  cpu_stat_model_->UpdateMonitorInfo(monitor_info);
  mem_model_->UpdateMonitorInfo(monitor_info);
  net_model_->UpdateMonitorInfo(monitor_info);
}

void MonitorWidget::ClickCpuButton() { stack_menu_->setCurrentIndex(0); }
void MonitorWidget::ClickSoftIrqButton() { stack_menu_->setCurrentIndex(1); }
void MonitorWidget::ClickMemButton() { stack_menu_->setCurrentIndex(2); }
void MonitorWidget::ClickNetButton() { stack_menu_->setCurrentIndex(3); }
}  // namespace monitor
