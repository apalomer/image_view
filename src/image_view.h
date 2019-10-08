#ifndef IMAGE_VIEW_H
#define IMAGE_VIEW_H

#include <QMainWindow>
#include "image_view_exports.h"

class QGraphicsPixmapItem;

namespace Ui {
class ImageView;
}

class IMAGE_VIEW_EXPORT ImageView : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageView(QWidget *parent = nullptr);
    ~ImageView();

private slots:

  void onImageOpen();
  void fitInView();

private:
    Ui::ImageView *ui;
    QGraphicsPixmapItem* pixmap_item_ = nullptr;
};

#endif // IMAGE_VIEW_H
