#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QInputDialog>
#include <QDir>
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
    void endgame();//signal game has ended
    void finished();
private slots:
    void setGame();//start game
    void setHand();//update hand
    void setDouble();//double down
    void setOutput();//output to text(temporary)
    void setStand();//dont not allow player to get more cards
    void setEndgame();//output results reset game
    void setFinished();



private:
    RandomPlayer player;
    RandomPlayer player2;
    Dealer dealer;
    std::vector <Hand*> handptrs;
    Ui::MainWindow *ui;
    QTextEdit *text;
};

#endif // MAINWINDOW_H
