#include <QTimer>
#include <QObject>
#include "Network.hpp"

class Worker : public QObject
{
    Q_OBJECT

    public:
        Worker(QObject *parent = nullptr);
        virtual ~Worker();

    private slots:
        void doWork();

    private:
        QTimer timer;
};