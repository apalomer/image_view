#include "image_view.h"
#include "ui_image_view.h"

#include <QAction>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QString>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QWheelEvent>

ImageView::ImageView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageView)
{
    ui->setupUi(this);
    connect(ui->actionOpen, &QAction::triggered, this, &ImageView::onImageOpen);
    connect(ui->actionFit, &QAction::triggered, this, &ImageView::fitInView);
    setWindowIcon(QIcon(":/image_view.png"));

    ui->graphicsView->setScene(new QGraphicsScene);
    pixmap_item_ = new QGraphicsPixmapItem;
    ui->graphicsView->scene()->addItem(pixmap_item_);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
}

ImageView::~ImageView()
{
    delete ui;
}

void ImageView::onImageOpen()
{
  QString fn = QFileDialog::getOpenFileName(this, tr("Select image"), "", tr("Images (*.png *.xpm *.jpg *.cjpg *.tif *.tiff)"));
  if (fn.isEmpty())
    return;
  loadImageByName(fn);
}

void ImageView::loadImageByName(QString fn)
{
  QImage qimg;
  if (fn.endsWith(".cjpg"))
    qimg = QImage(fn, "jpg");
  else
    qimg = QImage(fn);
  if (qimg.isNull())
  {
    qDebug() << "Error loading image "<< fn;
    return;
  }
  QPixmap qpxmp = QPixmap::fromImage(qimg);
  pixmap_item_->setPixmap(qpxmp);
  fitInView();
}

void ImageView::fitInView()
{
  ui->graphicsView->fitInView(ui->graphicsView->scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
}