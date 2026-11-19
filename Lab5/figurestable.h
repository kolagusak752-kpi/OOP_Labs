#pragma once

#include <QDialog>

namespace Ui {
class FiguresTable;
}

class FiguresTable : public QDialog
{
    Q_OBJECT
public:
    explicit FiguresTable(QWidget *parent = nullptr);
    ~FiguresTable();

    void add(QString name, int x1, int y1, int x2, int y2);
    void removeLast();
    void clear();

private:
    Ui::FiguresTable *ui;

signals:
    void selectionChanged(QList<int> selectedRows);
    void shapeDeleted(int row);

private slots:
    void on_tableWidget_itemSelectionChanged();
    void on_deleteButton_clicked();
};


