#include <QApplication>
#include "image_view.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  ImageView* iv = new ImageView;
  iv->show();
  if (argc > 1)
    iv->loadImageByName(QString::fromStdString(argv[1]));
  return app.exec();
}