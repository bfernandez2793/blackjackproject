#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmapCache>


MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow),player(100)
{
    setFixedSize(400, 400);
    ui->setupUi(this);
    ui->hitButton->setEnabled(false);//cannot use before a game has begun
    ui->standButton->setEnabled(false);//cannot use before a game has begun
    ui->doubleButton->setEnabled(false);//cannot use before a game has begun
    QObject::connect(ui->startButton,SIGNAL(clicked(bool)),this,SLOT(setGame()));//when start button is clicked initialized the game
    QObject::connect(ui->hitButton,SIGNAL(clicked(bool)),this,SLOT(setHand()));//update hand button
    QObject::connect(ui->standButton,SIGNAL(clicked(bool)),this,SLOT(setStand()));//update hand button
    QObject::connect(ui->doubleButton,SIGNAL(clicked(bool)),this,SLOT(setDouble()));//allow player double down
    QObject::connect(this,SIGNAL(bust()),this,SLOT(setStand()));//if bust dont allow the player to get more cards
    QObject::connect(this,SIGNAL(dealer_hand_changed()),this,SLOT(setDealerHand()));
    QObject::connect(this,SIGNAL(dealerStart()),this,SLOT(setDealerStart()));
    QObject::connect(this,SIGNAL(hand_changed()),this,SLOT(setOutput()));//update any change in the players hand
    QObject::connect(this,SIGNAL(endgame()),this,SLOT(setEndgame()));//output the results of the game
    QObject::connect(this,SIGNAL(finished()),this,SLOT(setFinished()));
    handptrs.push_back(&player);
   // handptrs.push_back(&player2);

    verticalPicsLayout=new QHBoxLayout(ui->cardLabel);
    verticalPicsLayout2=new QHBoxLayout(ui->cardLabel_2);

    //mcards2 = 0;
   // mcards1 = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setGame()
{
    //reset cards before any new game
    for(size_t j = 0; j < mDealerCards.size(); ++j)
        delete mDealerCards[j];
    mcards1=0;
    mDealerCards.clear();
    for(size_t j = 0; j < mPlayerCards.size(); ++j)
        delete mPlayerCards[j];
    mcards2=0;
    mPlayerCards.clear();
    //initializing the game for one player
    ui->standButton->setEnabled(true);
    ui->hitButton->setEnabled(true);
    ui->doubleButton->setEnabled(true);
    ui->startButton->setEnabled(false);
    ui->textBrowser->setText("");
    player.bet() = QInputDialog::getInt(this, tr("Place your bet"),tr("Bet:"),0,0,player.money(),1);
    player.update_hand();
    emit hand_changed();
    player.update_hand();
    emit hand_changed();
    dealer.update_hand();
    emit dealer_hand_changed();
    dealer.update_hand();
    emit dealer_hand_changed();
    ui->textBrowser->insertPlainText("\nCash: $" + QString::number(player.money()) +"\nPlayer 0:");
    if(player.blackjack()||dealer.blackjack())
        emit endgame();
}
void MainWindow::setHand()
{
    //anytime the hit button is hit update the players hand and check
    //if the the hand is bust
    player.update_hand();
    emit hand_changed();
    if (player.size() != 2)
        ui->doubleButton->setEnabled(false);
    if(player.bust())
        emit bust();
}
void MainWindow::setDealerHand()
{
    //set the dealers hand
    if(dealer.size() == 1)
    {
        picture.load("back.png");//initially only one card is visible to the players
        ++mcards1;
        mDealerInitCard = dealer.get_card_name();

        QLabel *picLabel = new QLabel(ui->cardLabel_2);
        mDealerCards.push_back(picLabel);
        picLabel->setScaledContents(true);
        picLabel->setPixmap(picture);
        ui->cardLabel_2->resize(mcards1*75,100);
        verticalPicsLayout2->addWidget(picLabel);
    }
    else
    {
        picture.load(QString::fromStdString(dealer.get_card_name())+".png");
        ++mcards1;
        QLabel *picLabel = new QLabel(ui->cardLabel_2);
        mDealerCards.push_back(picLabel);
        picLabel->setScaledContents(true);
        picLabel->setPixmap(picture);
        ui->cardLabel_2->resize(mcards1*75,100);
        verticalPicsLayout2->addWidget(picLabel);
    }

}
void MainWindow::setOutput()
{
    //anytime the players hand get updated, then update the players hand on the screen
    picture.load(QString::fromStdString(player.get_card_name())+".png");
    ++mcards2;
    QLabel *picLabel = new QLabel(ui->cardLabel);
    mPlayerCards.push_back(picLabel);
    picLabel->setScaledContents(true);
    picLabel->setPixmap(picture);
    ui->cardLabel->resize(mcards2*75,100);
    verticalPicsLayout->addWidget(picLabel);
    ui->textBrowser->insertPlainText(QString::number(player.value_of_hand())+" ");
}
void MainWindow::setDouble()
{
    //If the player doubles down and has enough cash then perform the following
    if(player.money() >= 2*player.bet())
    {
        player.update_hand();
        player.bet() = 2*player.bet();
        emit hand_changed();
        emit dealerStart();
        emit endgame();
    }
}
void MainWindow::setStand()
{
    //when the player stands then the dealer begins play
    emit dealerStart();
    emit endgame();
}
void MainWindow::setDealerStart()
{
   //get another card if player did not bust
    while ((dealer.Hard_hand() < 17) && (!player.bust()))
    {//continue to get cards as long as hard count is under 17
        if (dealer.Soft_hand() <= 21 && dealer.Soft_hand() >= 17)
            break; //if dealer has a soft count that is >= 17 or <=21, stop getting cards
        else
        {
            dealer.update_hand();
            emit dealer_hand_changed();
        }
    }
}
void MainWindow::setEndgame()
{
    picture.load(QString::fromStdString(mDealerInitCard)+".png");
    mDealerCards[0]->setPixmap(picture);
    ui->hitButton->setEnabled(false);
    ui->standButton->setEnabled(false);
    ui->doubleButton->setEnabled(false);
    //after play has ended output results
    ui->textBrowser->insertPlainText("\nDealer: " + QString::number(dealer.value_of_hand())) ;

    int i = 0;
    for(auto& x: handptrs)
    {
        if (x->bust())
        {
            x->money() -= x->bet();
            ui->textBrowser->insertPlainText("\nPlayer" + QString::number(i) +" Bust!! Dealer Wins!! Cash: $" + QString::number(x->money()));
        }
        else if (dealer.bust())
        {
            x->money() += x->bet();
            ui->textBrowser->insertPlainText("\nDealer Bust!! Player " + QString::number(i) +" Wins!! Cash: $" + QString::number(x->money()));
        }
        else if (x->value_of_hand() < dealer.value_of_hand())
        {
            x->money() -= x->bet();
            ui->textBrowser->insertPlainText("\nDealer Wins!! Cash: $" + QString::number(x->money()));
        }
        else if (x->value_of_hand() > dealer.value_of_hand())
        {
            x->money() += x->bet();
            ui->textBrowser->insertPlainText("\nPlayer " + QString::number(i) +" Wins!! Cash: $" + QString::number(x->money()));
        }
        else
            ui->textBrowser->insertPlainText("\nTie!!");
        x->reset();
        ++i;
    }
    dealer.reset();
    ui->startButton->setText("Restart");
    ui->startButton->setEnabled(true);
    if(handptrs[0]->money() == 0)
        emit finished();
    //delete verticalPicsLayout->layout();
    QPixmapCache::clear();
}
void MainWindow::setFinished(){

    ui->hitButton->setEnabled(false);
    ui->standButton->setEnabled(false);
    ui->doubleButton->setEnabled(false);
    ui->startButton->setEnabled(false);
    /*Create lambda function to sort final cash amounts*/
}
