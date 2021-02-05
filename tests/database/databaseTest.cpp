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
    void test_path();

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

void databaseTest::test_path()
{
    QVERIFY(db.exists());
}

QTEST_APPLESS_MAIN(databaseTest)

#include "databaseTest.moc"
