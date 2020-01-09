#include "QHmiTableModel.h"

QHmiTableModel::QHmiTableModel(QObject *parent)
  : QObject(parent)
{

}

void QHmiTableModel::setRowColumn(const int row, int const column)
{
  Q_ASSERT(row > 0 && column > 0);
  m_vctDatas.clear();
  for (int i = 0; i < row; ++i) {
    QVector<QSharedPointer<Data>> datas;
    for (int j = 0; j < column; ++j) {
      QSharedPointer<Data> data(new Data);
      datas.push_back(data);
    }
    m_vctDatas.push_back(datas);
  }

  for (int i = 0; i < column; ++i) {
    m_hHeaderStrings.push_back(QString::number(i));
  }
  for (int i = 0; i < row; ++i) {
    m_vHeaderStrings.push_back(QString::number(i));
  }
}

const int QHmiTableModel::row() const
{
  Q_ASSERT(m_vctDatas.size() > 0 && m_vctDatas[0].size() > 0);
  return m_vctDatas.size();
}

const int QHmiTableModel::column() const
{
  Q_ASSERT(m_vctDatas.size() > 0 && m_vctDatas[0].size() > 0);
  return m_vctDatas[0].size();
}

void QHmiTableModel::setHHeader(const QStringList &headers)
{
  Q_ASSERT(m_vctDatas.size() == headers.size());
  m_hHeaderStrings = headers;
}

void QHmiTableModel::setVHeader(const QStringList &headers)
{
  Q_ASSERT(m_vctDatas.size() > 0 && m_vctDatas[0].size() == headers.size());
  m_vHeaderStrings = headers;
}

const QStringList & QHmiTableModel::hHeader() const
{
  return m_hHeaderStrings;
}

const QStringList & QHmiTableModel::vHeader() const
{
  return m_vHeaderStrings;
}


void QHmiTableModel::setData(int row, int column, double data, bool changed)
{
  Q_ASSERT(row >= 0 && column >= 0 && row < this->row() && column < this->column());
  m_vctDatas[row][column]->m_dData = data;
  m_vctDatas[row][column]->m_bChanged = changed;
}

double QHmiTableModel::data(int row, int column) const
{
  Q_ASSERT(row >= 0 && column >= 0 && row < this->row() && column < this->column());
  return m_vctDatas[row][column]->m_dData;
}


