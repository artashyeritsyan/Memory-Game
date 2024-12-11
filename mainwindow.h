#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "card.h"
#include "enums.h"
#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QPushButton>

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
    void setGameSize(int height, int width);
    void initializeButtons(QVector<Card> table);
    void gameStartFunction();
    void updateGameScreen(QVector<Card> table);

    void cardResetCooldown();

private slots:
    // Menu buttons
    void on_TwoPlayerBtn_clicked();
    void on_ExitButton_clicked();
    void on_SinglePlayerBtn_clicked();

    // Size choosing buttons
    void initGameSizeButtons();
    void onAnyGameSizeButtonClicked();
    void on_BackFromSizeMenu_clicked();

    // Game buttons
    void on_anyButton_clicked(bool checked);
    int findButtonIndex(QPushButton* button);

    void on_HomeButton_clicked();

signals:
    void startGame(EGameMode gameMode, EGameSize gameSize);
    void buttonClicked(int buttonIndex);
    void exitSelected();
    // void twoPlayerSelected();

    void requestScreenUpdate();

private:
    void hideMenuButtons();
    void showMenuButtons();

    void hideGameSizeMenu();
    void showGameSizeMenu();

    void choose_card(int index);
    void compare_cards(int index_1, int index_2);
    void random_card_generation();
    void create_layout();
    void updateTime();
    void endGame();

    void disableAllButtons();
    void enableAllButtons();

    void removeGameWidgets();

    void exitToMenu();

    // void connectSizeMenuButtons();

private:
    int _height;
    int _width;

    int score = 0;
    int steps = 0;

    QVBoxLayout* _buttonsLayout;
    QVector<QPushButton*> _buttons;
    QVector<QString> images;

    QTimer* timer;

    int elapsedTime = 0;

    EGameMode _gameMode;
    EGameSize _gameSize;

    const int CARDCOOLDOWN = 900;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
