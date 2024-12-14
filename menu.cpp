// #include "menu.h"

// Menu::Menu(QWidget* parent) : QMainWindow(parent) {
//     QWidget* centralWidget = new QWidget(this);
//     setCentralWidget(centralWidget);

//     QVBoxLayout* layout = new QVBoxLayout(centralWidget);

//     QPushButton* singlePlayerBtn = new QPushButton("Single Player", this);
//     QPushButton* twoPlayerBtn = new QPushButton("Two Player", this);
//     QPushButton* difficultyBtn = new QPushButton("Difficulty", this);
//     QPushButton* scoresBtn = new QPushButton("Scores", this);
//     QPushButton* exitBtn = new QPushButton("Exit", this);

//     layout->addWidget(singlePlayerBtn);
//     layout->addWidget(twoPlayerBtn);
//     layout->addWidget(difficultyBtn);
//     layout->addWidget(scoresBtn);
//     layout->addWidget(exitBtn);

//     connect(singlePlayerBtn, &QPushButton::clicked, this, &Menu::startSinglePlayer);
//     connect(twoPlayerBtn, &QPushButton::clicked, this, &Menu::startTwoPlayer);
//     connect(difficultyBtn, &QPushButton::clicked, this, &Menu::showDifficultyMenu);
//     connect(scoresBtn, &QPushButton::clicked, this, &Menu::showScores);
//     connect(exitBtn, &QPushButton::clicked, this, &Menu::exitGame);
// }
