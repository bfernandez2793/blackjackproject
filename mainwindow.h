#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>
#include <QInputDialog>
#include <QHBoxLayout>
#include "card.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void Reset_Game(std::list<QLabel*>::iterator begin, std::list<QLabel*>::iterator end);
    ~MainWindow();
signals:
    void hand_changed();//signal when hand has changed
    void dealer_hand_changed();
    void dealerStart();
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
    void setDealerHand();//set the Dealers Hand
    void setDealerStart();
    void setFinished();



private:
    RandomPlayer player;
    //RandomPlayer player2;
    Dealer dealer;
    std::vector <Hand*> handptrs;
    QPixmap picture;
    QHBoxLayout *verticalPicsLayout;
    QHBoxLayout *verticalPicsLayout2;
    Ui::MainWindow *ui;
    QTextEdit *text;
    int mcards1,mcards2;
    std::string mDealerInitCard;
    std::list<QLabel*> mPlayingCards;
};

#endif // MAINWINDOW_H
