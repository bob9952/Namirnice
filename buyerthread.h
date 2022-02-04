#ifndef BUYERTHREAD_H
#define BUYERTHREAD_H

#include <QThread>
#include <QStringList>
#include <QMutex>
#include "recipe.h"

class BuyerThread : public QThread
{
    Q_OBJECT
public:
    BuyerThread();
    BuyerThread(const QStringList &sviSastojci,QMutex *mutex, QObject *parent = nullptr);
signals:
 void sastojakOdabran(const QString &);

private:

    QStringList m_sviSastojci;
    QMutex *m_mutex;
    // QThread interface
protected:
    void run();
};

#endif // BUYERTHREAD_H
