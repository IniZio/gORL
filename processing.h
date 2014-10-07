#ifndef PROCESSING_H
#define PROCESSING_H

#include <QDialog>
#include <QMessageBox>
#include <QDesktopServices>

namespace Ui {
class Processing;
}

class Processing : public QDialog
{
    Q_OBJECT

public:
    explicit Processing(QWidget *parent = 0);
    ~Processing();

    void process_data();

private slots:
    void on_next_clicked();

private:
    Ui::Processing *ui;
};

#endif // PROCESSING_H
