#include "figurestable.h"
#include "ui_figurestable.h"

FiguresTable::FiguresTable(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FiguresTable)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}

FiguresTable::~FiguresTable()
{
    delete ui;
}

void FiguresTable::add(QString name, int x1, int y1, int x2, int y2) {
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(name));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(x1)));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(y1)));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(x2)));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(y2)));


}

void FiguresTable::removeLast() {
    int rowCount = ui->tableWidget->rowCount();
    if (rowCount > 0) {
        ui->tableWidget->removeRow(rowCount - 1);
    }
}

void FiguresTable::on_tableWidget_itemSelectionChanged() {
    QList<int> rows;
    QModelIndexList selectedIndexes = ui->tableWidget->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) return;

    for (const QModelIndex& index : selectedIndexes) {
        rows.append(index.row());
    }

    emit selectionChanged(rows);
}

void FiguresTable::on_deleteButton_clicked() {
    QModelIndexList selectedIndexes = ui->tableWidget->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) return;


    QList<int> rows;
    for (const QModelIndex& index : selectedIndexes) {
        rows.append(index.row());
    }

    for(int i = 1; i < rows.size(); i++) {
        for(int j = i; j > 0; j--) {
            if(rows[j] > rows[j - 1]) {
                int temp = rows[j - 1];
                rows[j - 1] = rows[j];
                rows[j] = temp;

            } else {
                break;
            }
        }
    }
    for (int row : rows) {
        ui->tableWidget->removeRow(row);
        emit shapeDeleted(row);
}
}

