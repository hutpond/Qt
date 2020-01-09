#include "QHmiTableView.h"

#include <QPainter>
#include <QPen>
#include "QHmiTableModel.h"

QHmiTableView::QHmiTableView(QWidget *parent)
  : QWidget(parent)
  , m_pObjModel(Q_NULLPTR)
  , m_bHHeaderVisible(true)
  , m_bVHeaderVisible(true)

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
}

void QHmiTableView::resizeEvent(QResizeEvent *)
{
  Q_ASSERT(m_pObjModel != NULL && m_pObjModel->row() > 0 && m_pObjModel->column() > 0);

  const int WIDTH = this->width();
  const int HEIGHT = this->height();

  const int ROWS = m_pObjModel->row() + (m_bVHeaderVisible ? 1 : 0);
  const int COLUMNS = m_pObjModel->column() + (m_bHHeaderVisible ? 1 : 0);

  const int SPACE_X = qMin<int>(5, WIDTH * 0.05);
  const int SPACE_Y = qMin<int>(5, HEIGHT * 0.05);
  const float CELL_W = (WIDTH - 2 * SPACE_X) / COLUMNS;
  const float CELL_H = (HEIGHT - 2 * SPACE_Y) / ROWS;

  float fPosX = 0.0f;
  float fPosY = 0.0f;

  // horizental header
  if (m_bHHeaderVisible) {
    fPosX = SPACE_X + (m_bVHeaderVisible ? CELL_W : 0);
    fPosY = SPACE_Y;
    const int SIZE_H_HEADER = m_vctHHeaderRects.size();
    for (int i = 0; i < SIZE_H_HEADER; ++i) {
      m_vctHHeaderRects[i] = QRectF(fPosX, fPosY, CELL_W, CELL_H);
      fPosX += CELL_W;
    }
  }

  // vertical header
  if (m_bVHeaderVisible) {
    fPosX = SPACE_X;
    fPosY = SPACE_Y + (m_bHHeaderVisible ? CELL_H : 0);
    const int SIZE_V_HEADER = m_vctVHeaderRects.size();
    for (int i = 0; i < SIZE_V_HEADER; ++i) {
      m_vctVHeaderRects[i] = QRectF(fPosX, fPosY, CELL_W, CELL_H);
      fPosY += CELL_H;
    }
  }

  // data cell
  const int SIZE_ROW = m_vctCellRects.size();
  const int SIZE_COLUMN = m_vctCellRects[0].size();

  fPosY = SPACE_Y + (m_bHHeaderVisible ? CELL_H : 0);
  for (int i = 0; i < SIZE_ROW; ++i) {
    fPosX = SPACE_X + (m_bVHeaderVisible ? CELL_W : 0);
    for (int j = 0; j < SIZE_COLUMN; ++j) {
      m_vctCellRects[i][j] = QRectF(fPosX, fPosY, CELL_W, CELL_H);
      fPosX += CELL_W;
    }
    fPosY += CELL_H;
  }
}

void QHmiTableView::paintEvent(QPaintEvent *)
{
  Q_ASSERT(m_pObjModel != NULL && m_pObjModel->row() > 0 && m_pObjModel->column() > 0);

  QPainter painter(this);
  QPen pen;
  pen.setWidth(2);
  pen.setColor(Qt::black);
  painter.setPen(pen);

  // first cell
  if (m_bHHeaderVisible && m_bVHeaderVisible) {
    QRectF rectf(
          m_vctVHeaderRects[0].x(),
        m_vctHHeaderRects[0].y(),
        m_vctHHeaderRects[0].width(),
        m_vctHHeaderRects[0].height()
        );
    painter.drawRect(rectf);
  }

  // horizental header
  if (m_bHHeaderVisible) {
    const int SIZE_H_HEADER = m_vctHHeaderRects.size();
    for (int i = 0; i < SIZE_H_HEADER; ++i) {
      painter.drawRect(m_vctHHeaderRects[i]);
    }
  }

  // vertical header
  if (m_bVHeaderVisible) {
    const int SIZE_V_HEADER = m_vctVHeaderRects.size();
    for (int i = 0; i < SIZE_V_HEADER; ++i) {
      painter.drawRect(m_vctVHeaderRects[i]);
    }
  }

  // data cell
  const int SIZE_ROW = m_vctCellRects.size();
  const int SIZE_COLUMN = m_vctCellRects[0].size();
  for (int i = 0; i < SIZE_ROW; ++i) {
    for (int j = 0; j < SIZE_COLUMN; ++j) {
      painter.drawRect(m_vctCellRects[i][j]);
    }
  }
}
