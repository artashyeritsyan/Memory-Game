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
    void gameStartFunction(bool isTwoPlayer);
    void setGameSize(int height, int width);
    void initializeButtons(QVector<Card> table);
    void updateGameScreen(QVector<Card> table);
    void cardResetCooldown();
    void winGame();

    void updateScorePanels(int steps, int score);
    void updatePlayersScores(int score1, int score2);
    void updateTurnPanel(int playerTurn);
    void setWinnerInfo(int winnerId, int score);



private slots:
    // Menu buttons
    void on_SinglePlayerBtn_clicked();
    void on_TwoPlayerBtn_clicked();
    void on_ExitButton_clicked();

    // Size choosing buttons
    void initGameSizeButtons();
    void onAnyGameSizeButtonClicked();
    void on_BackFromSizeMenu_clicked();

    // Game buttons
    void onAnyButtonClicked(bool checked);
    void on_HomeButton_clicked();
    void on_RestartButton_clicked();
    void on_RestartButton_2_clicked();
    void on_HomeButton_2_clicked();

signals:
    void startGame(EGameMode gameMode, EGameSize gameSize);
    void restartGame();
    void buttonClicked(int buttonIndex);

    void requestScreenUpdate();

private:
    void initMenu();
    void create_layout();
    void updateTime();

    void disableAllButtons();
    void enableAllButtons();

    void hideMenuButtons();
    void showMenuButtons();

    void hideGameSizeMenu();
    void showGameSizeMenu();

    void hideInfoBoard();
    void showInfoBoard();

    void hideWinGameFrame();
    void showWinGameFrame();

    int findButtonIndex(QPushButton* button);
    void removeGameCards();
    void exitToMenu();
    void gameRestartManager();
    void endGame();

private:
    int _height;
    int _width;

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
