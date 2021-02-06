#include <QtTest>

class settingsTest : public QObject
{
    Q_OBJECT

public:
    settingsTest();
    ~settingsTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
};

settingsTest::settingsTest() { }

settingsTest::~settingsTest() { }

void settingsTest::initTestCase()
{
    qDebug("Test case initialized.");
}

void settingsTest::cleanupTestCase() { }

void settingsTest::test_case1()
{
    qDebug("Test");
}

QTEST_APPLESS_MAIN(settingsTest)

#include "settingsTest.moc"
