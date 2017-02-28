#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLCDNumber>
#include <QTextEdit>
#include "card.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void hand_changed();//signal when hand has changed
    void bust();//signal when player has bust
private slots:
  void setHand();//update hand
  void setGame();//start game
  void setOutput();//output to text(temporary)
  void setStand();//dont not allow player to get more cards

private:
    RandomPlayer *player;
    Ui::MainWindow *ui;
    QLCDNumber *mnumberer;
    QTextEdit *text;
};

#endif // MAINWINDOW_H
