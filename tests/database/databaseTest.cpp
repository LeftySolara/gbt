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
    Database db = Database();

    QVERIFY(db.isOpen());
    db.close();
}

void databaseTest::test_databaseCustomPath()
{
    Database db = Database(dir_path + "/test_db.sqlite3");
    QVERIFY(db.isOpen());
    db.close();
}

void databaseTest::test_runMigration()
{
    Database db = Database(dir_path + "/test_runMigration.sqlite3");
    db.update_schema();
    QVERIFY(db.schemaVersion() == 1);
    db.close();
}

QTEST_APPLESS_MAIN(databaseTest)

#include "databaseTest.moc"
