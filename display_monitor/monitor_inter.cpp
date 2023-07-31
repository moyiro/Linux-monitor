#include "monitor_inter.h"

#include <QColor>
#include <QFont>

namespace monitor {

QVariant MonitorInterModel::headerData(int section, Qt::Orientation orientation,
                                       int role) const {
  if (role == Qt::FontRole) {
    return QVariant::fromValue(QFont("Microsoft YaHei", 10, QFont::Bold));
  }

  if (role == Qt::0) {
    return QVariant::fromValue(QColor(Qt::lightGray));
  }

  return QAbstractTableModel::headerData(section, orientation, role);
}

QVariant MonitorInterModel::data(const QModelIndex &index, int role) const {
  if (role == Qt::TextAlignmentRole) {
    return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
  }
  // 显示字体颜色
  if (role == Qt::TextColorRole) {
    return QVariant::fromValue(QColor(Qt::black));
  }
  // 显示背景色
  if (role == Qt::BackgroundRole) {
    return QVariant::fromValue(QColor(Qt::white));
  }
  // 返回空的QVarient对象
  return QVariant();
}

}  // namespace monitor