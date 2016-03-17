#include <QDir>
#include <QFileInfo>
#include <QQueue>
#include <QtCore>
#include <QDomDocument>
#include <QFile>
#include "resourcegenerator.h"

ResourceGenerator::ResourceGenerator()
{
}

void ResourceGenerator::scan(QString prefix, QString path)
{
    QQueue<QString> queue;
    queue.enqueue(path);

    QString root = m_root;

    if (root.isEmpty()) {
        root = path;
    }

    QDir rootDir(root);
    QStringList files;

    while (queue.size() > 0) {

        QString current = queue.dequeue();
        QDir dir(current);
        QFileInfoList infos = dir.entryInfoList(QStringList(),QDir::AllEntries);

        for (int i = 0 ; i < infos.size();i++) {
            QFileInfo info = infos.at(i);
            if (info.fileName() == "." || info.fileName() == "..")
                continue;

            if (info.isDir()) {
                queue.enqueue(info.absoluteFilePath());
            } else {
                files << rootDir.relativeFilePath(info.absoluteFilePath());
            }
        }
    }

    QStringList tmp = m_files[prefix];
    tmp.append(files);
    m_files[prefix] = tmp;

    generateText();
}

QString ResourceGenerator::text() const
{
    return m_text;
}

bool ResourceGenerator::save(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(m_text.toLocal8Bit());

    file.close();

    return true;
}

void ResourceGenerator::generateText()
{
    QDomDocument doc;
    QDomElement root = doc.createElement("RCC");
    doc.appendChild(root);

    QMapIterator<QString, QStringList> iter(m_files);
    while (iter.hasNext()) {
        iter.next();

        QStringList list = iter.value();
        QString prefix = iter.key();

        QDomElement qresource = doc.createElement("qresource");
        root.appendChild(qresource);
        qresource.setAttribute("prefix", prefix);

        foreach (QString file, list) {
            QDomElement tag = doc.createElement("file");
            QDomText text = doc.createTextNode(file);

            tag.appendChild(text);
            qresource.appendChild(tag);
        }
    }

    m_text = doc.toString(4);
}

QString ResourceGenerator::root() const
{
    return m_root;
}

void ResourceGenerator::setRoot(const QString &root)
{
    m_root = root;
}
