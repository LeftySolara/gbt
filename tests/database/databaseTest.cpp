#include <QtTest>
#include <QTemporaryDir>
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

    void test_databaseDefaultPath();
    void test_databaseCustomPath();

private:
    Database db;
};

databaseTest::databaseTest() { }

databaseTest::~databaseTest() { }

void databaseTest::initTestCase() { }

void databaseTest::cleanupTestCase() { }

void databaseTest::test_databaseDefaultPath()
{
    Database db = Database();

    QVERIFY(db.isOpen());
    db.close();
}

void databaseTest::test_databaseCustomPath()
{
    QTemporaryDir dir;
    qDebug() << "Temporary directory: " + dir.path();
    if (dir.isValid()) {
        Database db = Database(dir.path() + "/test_db.sqlite3");
        QVERIFY(db.isOpen());
        db.close();
    }
}

QTEST_APPLESS_MAIN(databaseTest)

#include "databaseTest.moc"
