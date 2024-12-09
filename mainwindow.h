#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void gameStartFunction();
    void choose_card(int index);
    void compare_cards(int index_1, int index_2);

    void on_anyButton_clicked(bool checked);

    void random_card_generation();
    void create_layout();
    void updateTime();
    void endGame();


private slots:
    void on_PlayButton_clicked();

signals:

};
#endif // MAINWINDOW_H
