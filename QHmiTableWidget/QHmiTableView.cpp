#include "QHmiTableView.h"

#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QDebug>
#include "QHmiTableModel.h"

QHmiTableView::QHmiTableView(QWidget *parent)
  : QWidget(parent)
  , m_pObjModel(Q_NULLPTR)
  , m_bHHeaderVisible(true)
  , m_bVHeaderVisible(true)
  , m_fHeaderWidthPercent(-1)
  , m_fHeaderHeightPercent(-1)
  , m_nIntegerDigital(6)
  , m_nDecimalDigital(4)
  , m_ptSelected(-1, -1)
{

}

void QHmiTableView::setHeaderVisible(bool hVisible, bool vVisible)
{
  m_bHHeaderVisible = hVisible;
  m_bVHeaderVisible = vVisible;
}

void QHmiTableView::setModel(QHmiTableModel *model)
{
  m_pObjModel = model;

  m_vctHHeaderRects.resize(m_pObjModel->column());
  m_vctVHeaderRects.resize(m_pObjModel->row());
  for (int i = 0; i < m_pObjModel->row(); ++i) {
    QVector<QRectF> rects;
    rects.resize(m_pObjModel->column());
    m_vctCellRects.push_back(rects);
  }

  if (m_fHeaderHeightPercent < 0) {
    m_fHeaderHeightPercent = 1.0f / (m_pObjModel->row() + 1.0f);
  }
  if (m_fHeaderWidthPercent < 0) {
    m_fHeaderWidthPercent = 1.0f / (m_pObjModel->column() + 1.0f);
  }
}

void QHmiTableView::setHeaderHeightPercent(float percent)
{
  m_fHeaderHeightPercent = percent;
}

void QHmiTableView::setHeaderWidthPercent(float percent)
{
  m_fHeaderWidthPercent = percent;
}

void QHmiTableView::setDataPrecision(int integer, int decimal)
{
  m_nIntegerDigital = integer;
  m_nDecimalDigital = decimal;
}

void QHmiTableView::resizeEvent(QResizeEvent *)
{
  Q_ASSERT(m_pObjModel != NULL && m_pObjModel->row() > 0 && m_pObjModel->column() > 0);

  const int WIDTH = this->width();
  const int HEIGHT = this->height();


  const int SPACE_X = qMin<int>(5, WIDTH * 0.05);
  const int SPACE_Y = qMin<int>(5, HEIGHT * 0.05);
  const int HEADER_W = m_bVHeaderVisible ? WIDTH * m_fHeaderWidthPercent : 0;
  const int HEADER_H = m_bVHeaderVisible ? HEIGHT * m_fHeaderHeightPercent : 0;
  const float CELL_W = (WIDTH - 2 * SPACE_X - HEADER_W) / m_pObjModel->column();
  const float CELL_H = (HEIGHT - 2 * SPACE_Y - HEADER_H) / m_pObjModel->row();

  float fPosX = 0.0f;
  float fPosY = 0.0f;

  // horizental header
  if (m_bHHeaderVisible) {
    fPosX = SPACE_X + (m_bVHeaderVisible ? HEADER_W : 0);
    fPosY = SPACE_Y;
    const int SIZE_H_HEADER = m_vctHHeaderRects.size();
    for (int i = 0; i < SIZE_H_HEADER; ++i) {
      m_vctHHeaderRects[i] = QRectF(fPosX, fPosY, CELL_W, HEADER_H);
      fPosX += CELL_W;
    }
  }

  // vertical header
  if (m_bVHeaderVisible) {
    fPosX = SPACE_X;
    fPosY = SPACE_Y + (m_bHHeaderVisible ? HEADER_H : 0);
    const int SIZE_V_HEADER = m_vctVHeaderRects.size();
    for (int i = 0; i < SIZE_V_HEADER; ++i) {
      m_vctVHeaderRects[i] = QRectF(fPosX, fPosY, HEADER_W, CELL_H);
      fPosY += CELL_H;
    }
  }

  // data cell
  const int SIZE_ROW = m_vctCellRects.size();
  const int SIZE_COLUMN = m_vctCellRects[0].size();

  fPosY = SPACE_Y + HEADER_H;
  for (int i = 0; i < SIZE_ROW; ++i) {
    fPosX = SPACE_X + HEADER_W;
    for (int j = 0; j < SIZE_COLUMN; ++j) {
      m_vctCellRects[i][j] = QRectF(fPosX, fPosY, CELL_W, CELL_H);
      fPosX += CELL_W;
    }
    fPosY += CELL_H;
  }
}

void QHmiTableView::paintEvent(QPaintEvent *e)
{
  Q_ASSERT(m_pObjModel != NULL && m_pObjModel->row() > 0 && m_pObjModel->column() > 0);

  QPainter painter(this);
  QRect rect = e->rect();
  qDebug() << "update: " << rect;
  //if (rect == this->rect()) {
    this->drawAllRect(painter);
//  }
//  else {
//    this->drawCellRect(rect, painter);
//  }
}

void QHmiTableView::drawAllRect(QPainter &painter)
{
  painter.save();

  QPen pen;
  pen.setWidth(2);
  pen.setColor(Qt::lightGray);
  painter.setPen(pen);

  // first cell
  if (m_bHHeaderVisible && m_bVHeaderVisible) {
    QRectF rectf(
          m_vctVHeaderRects[0].x(),
        m_vctHHeaderRects[0].y(),
        m_vctVHeaderRects[0].width(),
        m_vctHHeaderRects[0].height()
        );
    painter.drawRect(rectf);
  }

  // horizental header
  if (m_bHHeaderVisible) {
    const int SIZE_H_HEADER = m_vctHHeaderRects.size();
    const QStringList strHeaders = m_pObjModel->hHeader();
    for (int i = 0; i < SIZE_H_HEADER; ++i) {
      pen.setColor(Qt::lightGray);
      painter.setPen(pen);
      painter.drawRect(m_vctHHeaderRects[i]);

      pen.setColor(Qt::black);
      painter.setPen(pen);
      painter.drawText(m_vctHHeaderRects[i], Qt::AlignCenter, strHeaders[i]);
    }
  }

  // vertical header
  if (m_bVHeaderVisible) {
    const int SIZE_V_HEADER = m_vctVHeaderRects.size();
    const QStringList strHeaders = m_pObjModel->vHeader();
    for (int i = 0; i < SIZE_V_HEADER; ++i) {
      pen.setColor(Qt::lightGray);
      painter.setPen(pen);
      painter.drawRect(m_vctVHeaderRects[i]);

      pen.setColor(Qt::black);
      painter.setPen(pen);
      painter.drawText(m_vctVHeaderRects[i], Qt::AlignCenter, strHeaders[i]);
    }
  }

  // data cell
  const int SIZE_ROW = m_vctCellRects.size();
  const int SIZE_COLUMN = m_vctCellRects[0].size();
  const int SPACE_X = 10;
  const int SIGN_W = 20;
  for (int i = 0; i < SIZE_ROW; ++i) {
    for (int j = 0; j < SIZE_COLUMN; ++j) {
      pen.setColor(Qt::lightGray);
      painter.setPen(pen);
      painter.drawRect(m_vctCellRects[i][j]);

      pen.setColor(Qt::black);
      painter.setPen(pen);
      QRect rectf = QRect(
            m_vctCellRects[i][j].x() + SPACE_X,
            m_vctCellRects[i][j].y(),
            SIGN_W,
            m_vctCellRects[i][j].height());
      QString text = (m_pObjModel->data(i, j) >= 0 ? "+" : "-");
      painter.drawText(rectf, Qt::AlignVCenter | Qt::AlignLeft, text);

      text = QString("%1").arg(
            qAbs(m_pObjModel->data(i, j)), -1, 'f', m_nDecimalDigital);
      rectf = QRect(
                  m_vctCellRects[i][j].x() + SPACE_X + SIGN_W,
                  m_vctCellRects[i][j].y(),
                  m_vctCellRects[i][j].width() - 2 * SPACE_X - SIGN_W,
                  m_vctCellRects[i][j].height());
      painter.drawText(rectf, Qt::AlignVCenter | Qt::AlignRight, text);
    }
  }

  // select
  if (m_ptSelected.x() >= 0 && m_ptSelected.y() >= 0) {
    int i = m_ptSelected.x();
    int j = m_ptSelected.y();
    pen.setWidth(2);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawRect(m_vctCellRects[i][j]);
    QRect rectf = QRect(
          m_vctCellRects[i][j].x() + SPACE_X,
          m_vctCellRects[i][j].y(),
          SIGN_W,
          m_vctCellRects[i][j].height());

    pen.setColor(Qt::black);
    painter.setPen(pen);
    QString text = (m_pObjModel->data(i, j) >= 0 ? "+" : "-");
    painter.drawText(rectf, Qt::AlignVCenter | Qt::AlignLeft, text);

    pen.setColor(Qt::black);
    painter.setPen(pen);
    text = QString("%1").arg(
          qAbs(m_pObjModel->data(i, j)), -1, 'f', m_nDecimalDigital);
    rectf = QRect(
          m_vctCellRects[i][j].x() + SPACE_X + SIGN_W,
          m_vctCellRects[i][j].y(),
          m_vctCellRects[i][j].width() - 2 * SPACE_X - SIGN_W,
          m_vctCellRects[i][j].height());
    painter.drawText(rectf, Qt::AlignVCenter | Qt::AlignRight, text);
  }

  painter.restore();
}

void QHmiTableView::drawCellRect(const QRect &rect, QPainter &painter)
{
  painter.save();

  QPen pen;
  pen.setWidth(2);
  pen.setColor(Qt::lightGray);
  painter.setPen(pen);

  // first cell
  if (m_bHHeaderVisible && m_bVHeaderVisible) {
    QRectF rectf(
          m_vctVHeaderRects[0].x(),
        m_vctHHeaderRects[0].y(),
        m_vctHHeaderRects[0].width(),
        m_vctHHeaderRects[0].height()
        );
    if (rect.contains(rectf.toRect())) {
      painter.drawRect(rectf);
    }
  }

  // horizental header
  if (m_bHHeaderVisible) {
    const int SIZE_H_HEADER = m_vctHHeaderRects.size();
    const QStringList strHeaders = m_pObjModel->hHeader();
    for (int i = 0; i < SIZE_H_HEADER; ++i) {
      if (rect.contains(m_vctHHeaderRects[i].toRect())) {
        painter.drawRect(m_vctHHeaderRects[i]);
        painter.drawText(m_vctHHeaderRects[i], Qt::AlignCenter, strHeaders[i]);
      }
    }
  }

  // vertical header
  if (m_bVHeaderVisible) {
    const int SIZE_V_HEADER = m_vctVHeaderRects.size();
    const QStringList strHeaders = m_pObjModel->vHeader();
    for (int i = 0; i < SIZE_V_HEADER; ++i) {
      if (rect.contains(m_vctVHeaderRects[i].toRect())) {
        painter.drawRect(m_vctVHeaderRects[i]);
        painter.drawText(m_vctVHeaderRects[i], Qt::AlignCenter, strHeaders[i]);
      }
    }
  }

  // data cell
  const int SIZE_ROW = m_vctCellRects.size();
  const int SIZE_COLUMN = m_vctCellRects[0].size();
  const int SPACE_X = 10;
  const int SIGN_W = 20;
  for (int i = 0; i < SIZE_ROW; ++i) {
    for (int j = 0; j < SIZE_COLUMN; ++j) {
      if (rect.contains(m_vctCellRects[i][j].toRect())) {
        pen.setWidth(2);
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawRect(m_vctCellRects[i][j]);

        pen.setColor(Qt::black);
        painter.setPen(pen);
        QRect rectf = QRect(
              m_vctCellRects[i][j].x() + SPACE_X,
              m_vctCellRects[i][j].y(),
              SIGN_W,
              m_vctCellRects[i][j].height());
        QString text = (m_pObjModel->data(i, j) >= 0 ? "+" : "-");
        painter.drawText(rectf, Qt::AlignVCenter | Qt::AlignLeft, text);

        text = QString("%1").arg(
              qAbs(m_pObjModel->data(i, j)), -1, 'f', m_nDecimalDigital);
        rectf = QRect(
              m_vctCellRects[i][j].x() + SPACE_X + SIGN_W,
              m_vctCellRects[i][j].y(),
              m_vctCellRects[i][j].width() - 2 * SPACE_X - SIGN_W,
              m_vctCellRects[i][j].height());
        painter.drawText(rectf, Qt::AlignVCenter | Qt::AlignRight, text);
      }
    }
  }

  int i = m_ptSelected.x();
  int j = m_ptSelected.y();
  if (i >= 0 && j >= 0 && rect.contains(m_vctCellRects[i][j].toRect())) {
    pen.setWidth(4);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawRect(m_vctCellRects[i][j]);

    pen.setColor(Qt::black);
    painter.setPen(pen);
    QRect rectf = QRect(
          m_vctCellRects[i][j].x() + SPACE_X,
          m_vctCellRects[i][j].y(),
          SIGN_W,
          m_vctCellRects[i][j].height());
    QString text = (m_pObjModel->data(i, j) >= 0 ? "+" : "-");
    painter.drawText(rectf, Qt::AlignVCenter | Qt::AlignLeft, text);

    text = QString("%1").arg(
          qAbs(m_pObjModel->data(i, j)), -1, 'f', m_nDecimalDigital);
    rectf = QRect(
          m_vctCellRects[i][j].x() + SPACE_X + SIGN_W,
          m_vctCellRects[i][j].y(),
          m_vctCellRects[i][j].width() - 2 * SPACE_X - SIGN_W,
          m_vctCellRects[i][j].height());
    painter.drawText(rectf, Qt::AlignVCenter | Qt::AlignRight, text);
  }

  painter.restore();
}

void QHmiTableView::mousePressEvent(QMouseEvent *e)
{
  if (Qt::LeftButton == e->button()) {
    QPointF ptf = e->localPos();
    const int ROW = m_vctCellRects.size();
    const int COLUMN = m_vctCellRects[0].size();
    for (int i = 0; i < ROW; ++i) {
      for (int j = 0; j < COLUMN; ++j) {
        QPoint pt = QPoint(i, j);
        if (m_vctCellRects[i][j].contains(ptf) && m_ptSelected != pt) {
          QPoint ptOld = m_ptSelected;
          m_ptSelected = pt;
          if (ptOld.x() >= 0 && ptOld.y() >= 0) {
            QRect rect = m_vctCellRects[ptOld.x()][ptOld.y()].toRect();
            qDebug() << "old: " << rect;
            //this->update(rect);
          }
          QRect rect = m_vctCellRects[i][j].toRect();
          qDebug() << "new: " << rect;
          this->update();
          emit selected(i, j);
          return;
        }
      }
    }
  }
}
