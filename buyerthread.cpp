#include "buyerthread.h"

#include <QRandomGenerator>
#include <QMutexLocker>

BuyerThread::BuyerThread()
{

}

BuyerThread::BuyerThread(const QStringList &sviSastojci, QMutex *mutex, QObject *parent) : QThread(parent),
    m_sviSastojci(sviSastojci),
    m_mutex(mutex)
{}

void BuyerThread::run()
{
    const auto n = int(1 + QRandomGenerator::global()->generate() % 20);
    for(int i = 1; i <= n; i++){
        msleep(1);

        QMutexLocker lock(m_mutex);
        //Насумично бира jедан састоjак од свих састоjака коjи су се jављали у рецептима.
        const auto index =QRandomGenerator::global()->generate() % m_sviSastojci.size();
        const auto randomSastojak = m_sviSastojci.at(index);
        emit sastojakOdabran(randomSastojak);
    }
}
