#ifndef TESTRUNNER_H
#define TESTRUNNER_H

#include <QObject>
#include <QQmlEngine>
#include <functional>
/// Multiple test case runner

class TestRunner
{
public:
    TestRunner();
    ~TestRunner();

    /// Add a QObject test suite
    void add(QObject* object);

    /// Add Qt Quick test suite
    void add(const QString& path);

    /// Add a QObject test suite
    template <typename T> void add();

    /// Execute test case with arguments
    bool exec(QStringList arguments);

    /// Add a import path for Qt Quick Test suite
    void addImportPath(const QString& path);

    /// Return no. of test objects added
    int count() const;

    /// The current arguments
    QStringList arguments() const;

    /// Get the default instance of TestRunner (The first declared TestRunner)
    static TestRunner* defautInstance();

    QVariantMap config() const;

    /// Set config variables that will be passed to QML application via TestRunner singleton object
    void setConfig(const QVariantMap &config);

    typedef void (*Callback)(QQmlEngine* engine);

    /// Set a callback to be invoked when a QQmlEngine start
    void setEngineHook(Callback func);

    void setGallery(std::function<bool(const QStringList&)> function);

    std::function<bool(const QStringList&)> gallery() const;

protected:
    virtual void execEngineHook(QQmlEngine* engine);

private:
    void add(QVariant value);

    // Run QTest
    bool run(QObject* object, const QStringList& arguments);

    // Run Qt Quick Tests
    bool run(QString path, const QStringList& arguments);

    bool runGallery(const QStringList& arguments);

    QVariantList m_testObjects;

    QStringList m_importPaths;

    QStringList m_arguments;

    QVariantMap m_config;

    Callback m_engineHook;

    std::function<bool(const QStringList &) > m_gallery;
};


template <typename T>
void TestRunner::add()
{
    add(new T());
}

#endif // TESTRUNNER_H
