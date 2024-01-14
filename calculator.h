#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButton();
    void ChangeNumberSign();
    void GetMemory();
    void SetMemory();
    void ClearMemory();
    void ClearAll();

private:
    Ui::Calculator *ui;
    bool CheckIfNumber(QString);
};
#endif // CALCULATOR_H
