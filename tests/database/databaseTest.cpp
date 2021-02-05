#include <QtTest>
#include "gbt/database.h"

class databaseTest : public QObject
{
    Q_OBJECT

public:
    databaseTest();
    ~databaseTest();

private slots:
    void initTestCase();
    void cleanupTestCase();

private:
    Database db;
};

databaseTest::databaseTest()
{
    db = Database();
}

databaseTest::~databaseTest()
{

}

void databaseTest::initTestCase()
{
}

void databaseTest::cleanupTestCase()
{

}

QTEST_APPLESS_MAIN(databaseTest)

#include "databaseTest.moc"
