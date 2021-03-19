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

    void test_runMigration();

private:
    QString dir_path;
};

databaseTest::databaseTest() { }

databaseTest::~databaseTest() { }

void databaseTest::initTestCase()
{
    QTemporaryDir dir;
    dir.setAutoRemove(false);
    dir_path = dir.path();
    qDebug() << "Temporary directory: " + dir_path;
}

void databaseTest::cleanupTestCase() { }

void databaseTest::test_databaseDefaultPath()
{
    Database::open();

    QVERIFY(Database::isOpen());
    Database::close();
}

void databaseTest::test_databaseCustomPath()
{
    Database::open(dir_path + "/test_db.sqlite3");
    QVERIFY(Database::isOpen());
    Database::close();
}

void databaseTest::test_runMigration()
{
    Database::open(dir_path + "/test_runMigration.sqlite3");
    Database::update_schema();
    QVERIFY(Database::schemaVersion() == 1);
    Database::close();
}

QTEST_APPLESS_MAIN(databaseTest)

#include "databaseTest.moc"
