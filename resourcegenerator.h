#ifndef RESOURCEGENERATOR_H
#define RESOURCEGENERATOR_H

#include <QString>
#include <QStringList>

class ResourceGenerator
{
public:
    ResourceGenerator();

    void scan(QString prefix, QString root, QString path);

    QString text() const;

    bool save(const QString& path);

private:
    void generateText();

    QString m_prefix;
    QStringList m_files;
    QString m_text;
};

#endif // RESOURCEGENERATOR_H
