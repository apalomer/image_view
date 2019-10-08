#include "image_view.h"
#include "ui_image_view.h"

#include <QAction>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QString>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QWheelEvent>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

ImageView::ImageView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageView)
{
    ui->setupUi(this);
    connect(ui->actionOpen, &QAction::triggered, this, &ImageView::onImageOpen);
    connect(ui->actionFit, &QAction::triggered, this, &ImageView::fitInView);

    ui->graphicsView->setScene(new QGraphicsScene);
    pixmap_item_ = new QGraphicsPixmapItem;
    ui->graphicsView->scene()->addItem(pixmap_item_);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
}

ImageView::~ImageView()
{
    delete ui;
}

QString type2str(int type) {
  QString r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch (depth) {
  case CV_8U:  r = "8U"; break;
  case CV_8S:  r = "8S"; break;
  case CV_16U: r = "16U"; break;
  case CV_16S: r = "16S"; break;
  case CV_32S: r = "32S"; break;
  case CV_32F: r = "32F"; break;
  case CV_64F: r = "64F"; break;
  default:     r = "User"; break;
  }

  r += "C";
  r += (chans + '0');

  return r;
}

void ImageView::onImageOpen()
{
  QString fn = QFileDialog::getOpenFileName(this, tr("Select image"), "", tr("Images (*.png *.xpm *.jpg *.tif *.tiff)"));
  if (fn.isEmpty())
    return;
  cv::Mat img = cv::imread(fn.toStdString(), cv::IMREAD_UNCHANGED);
  if (img.empty())
    return;

  QImage qimg;
  if (img.type() == CV_8UC1)
    qimg = QImage(img.data, img.cols, img.rows, int(img.step), QImage::Format_Grayscale8);
  else if (img.type() == CV_8UC3)
    qimg = QImage(img.data, img.cols, img.rows, int(img.step), QImage::Format_RGB888).rgbSwapped(); // Opencv is bgr
  else  if (img.type() == CV_8UC4)
    qimg = QImage(img.data, img.cols, img.rows, int(img.step), QImage::Format_RGBA8888).rgbSwapped(); // Opencv is bgr
  else
  {
    qDebug() << "Image type: "<< type2str(img.type()) << " not abailable";
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