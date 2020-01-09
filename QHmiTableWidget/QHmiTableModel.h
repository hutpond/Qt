#ifndef QHMITABLEMODEL_H
#define QHMITABLEMODEL_H

#include <QObject>
#include <QVector>
#include <QStringList>
#include <QSharedPointer>

class QHmiTableModel : public QObject
{
  Q_OBJECT

  struct Data
  {
    bool m_bChanged;
    double m_dData;
    Data()
    {
      m_bChanged = false;
      m_dData = 0.0;
    }
  };

public:
  explicit QHmiTableModel(QObject *parent = nullptr);

  void setRowColumn(const int, const int);
  const int row() const;
  const int column() const;

  void setHHeader(const QStringList &);
  void setVHeader(const QStringList &);
  const QStringList & hHeader() const;
  const QStringList & vHeader() const;

  void setData(int, int, double, bool = false);
  double data(int, int) const;

signals:

private:
  QStringList m_hHeaderStrings;
  QStringList m_vHeaderStrings;
  QVector<QVector<QSharedPointer<Data>>> m_vctDatas;
};

#endif // QHMITABLEMODEL_H
