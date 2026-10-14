#pragma once

#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include "shapeobjectseditor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:

    void on_line_triggered();

    void on_rectangle_triggered();

    void on_back_triggered();

    void on_color_triggered();

    void on_ellipse_triggered();

    void on_point_triggered();

private:
    Ui::MainWindow *ui;
    ShapeObjectsEditor *manager;
};


