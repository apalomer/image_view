#include <QApplication>
#include "image_view.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  ImageView* iv = new ImageView;
  iv->show();
  return app.exec();
}