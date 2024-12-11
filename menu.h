// #ifndef MENU_H
// #define MENU_H


// #include <QMainWindow>
// #include <QPushButton>
// #include <QVBoxLayout>
// #include <QWidget>

// QT_BEGIN_NAMESPACE
// namespace Ui {
// class Menu;
// }
// QT_END_NAMESPACE

// class Menu : public QMainWindow {
//     Q_OBJECT

// private:
//     Ui::Menu *ui;

// public:
//     Menu(QWidget* parent = nullptr) : QMainWindow(parent), ui(new Ui::Menu) {
//         ui->setupUi(this);

//         QWidget* centralWidget = new QWidget(this);
//         setCentralWidget(centralWidget);

//         QVBoxLayout* layout = new QVBoxLayout(centralWidget);

//         QPushButton* singlePlayerBtn = new QPushButton("Single Player", this);
//         QPushButton* twoPlayerBtn = new QPushButton("Two Player", this);
//         QPushButton* difficultyBtn = new QPushButton("Difficulty", this);
//         QPushButton* scoresBtn = new QPushButton("Scores", this);
//         QPushButton* exitBtn = new QPushButton("Exit", this);

//         layout->addWidget(singlePlayerBtn);
//         layout->addWidget(twoPlayerBtn);
//         layout->addWidget(difficultyBtn);
//         layout->addWidget(scoresBtn);
//         layout->addWidget(exitBtn);

//         connect(singlePlayerBtn, &QPushButton::clicked, this, &Menu::startSinglePlayer);
//         connect(twoPlayerBtn, &QPushButton::clicked, this, &Menu::startTwoPlayer);
//         connect(difficultyBtn, &QPushButton::clicked, this, &Menu::showDifficultyMenu);
//         connect(scoresBtn, &QPushButton::clicked, this, &Menu::showScores);
//         connect(exitBtn, &QPushButton::clicked, this, &Menu::exitGame);
//     }

// signals:
//     void singlePlayerSelected();
//     void twoPlayerSelected();
//     void difficultySelected();
//     void scoresSelected();
//     void exitSelected();

// private slots:

//     void on_TwoPlayerBtn_clicked() {
//         for (int i = 0; i < ui->MenuLayout->count(); ++i) {
//             auto item = ui->MenuLayout->itemAt(i);
//             item->widget()->hide();
//         }

//         // gameStartFunction()
//     }

//     void on_SinglePlayerBtn_clicked() {

//     }

//     void startSinglePlayer() {
//         emit singlePlayerSelected();
//     }

//     void startTwoPlayer() {
//         emit twoPlayerSelected();
//     }

//     void showDifficultyMenu() {
//         emit difficultySelected();
//     }

//     void showScores() {
//         emit scoresSelected();
//     }

//     void exitGame() {
//         emit exitSelected();
//     }
// };

// #endif // MENU_H
