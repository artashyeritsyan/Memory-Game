// #include "screen.h"

// Screen::Screen(QWidget *parent)
//     : QMainWindow{parent}
// {}


// void Screen::on_PlayButton_clicked()
// {
//     for (int i = 0; i < ui->MenuLayout->count(); ++i) {
//         auto item = ui->MenuLayout->itemAt(i);
//         item->widget()->hide();
//     }

//     gameStartFunction();
// }

// void Screen::random_card_generation() {
//     for (int i = 0; i < (_height * _width); ++i) {
//         QPushButton* button = new QPushButton;

//         // button->setGeometry(0, 0, 90, 120);
//         button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
//         button->setStyleSheet("");

//         button->setFlat(true);

//         button->setCheckable(true);
//         connect(button, &QPushButton::clicked, this, &Screen::on_anyButton_clicked);

//         _table.push_back(button);
//     }


//     QVector<QString> imageAssignments;
//     for (int i = 0; i < 14; ++i) {
//         imageAssignments.push_back(images[i]);
//         imageAssignments.push_back(images[i]);
//     }

//     std::random_shuffle(imageAssignments.begin(), imageAssignments.end());

//     for (int i = 0; i < _table.size(); ++i) {
//         _table[i]->setStyleSheet("QPushButton {border-image: url(:/assets/Xmas/Assets/advent-calendar/blows.png);}" +
//                                  QString("QPushButton:checked {border-image: %1;}").arg(imageAssignments[i]));
//     }

// }

// void Screen::create_layout() {
//     QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->widgets_frame->layout());
//     if (!layout) {
//         layout = new QVBoxLayout(ui->widgets_frame);
//         ui->widgets_frame->setLayout(layout);
//     }

//     int k = 0;
//     for (int i = 0; i < _height; ++i) {
//         QHBoxLayout* tempLayout = new QHBoxLayout(ui->widgets_frame);
//         for (int j = 0; j < _width; ++j) {
//             tempLayout->addWidget(_table[k++]);
//         }

//         layout->insertLayout(i, tempLayout);
//     }
// }
