#ifndef RESOURCEGENERATOR_H
#define RESOURCEGENERATOR_H

#include <QString>
#include <QStringList>
#include <QMap>

class ResourceGenerator
{
public:
    ResourceGenerator();

    void scan(QString prefix, QString path);

    QString text() const;

    bool save(const QString& path);

    QString root() const;

    void setRoot(const QString &root);

private:
    void generateText();

    QString m_text;
    QString m_root;
    QMap<QString, QStringList> m_files;
};

#endif // RESOURCEGENERATOR_H
