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

void ResourceGenerator::scan(QString prefix, QString root)
{
    m_prefix = prefix;
    QQueue<QString> queue;
    queue.enqueue(root);
    m_files.clear();
    QDir rootDir(root);

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
                m_files << rootDir.relativeFilePath(info.absoluteFilePath());
            }
        }
    }

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

    QDomElement qresource = doc.createElement("qresource");
    qresource.setAttribute("prefix", m_prefix);
    root.appendChild(qresource);

    foreach (QString file, m_files) {
        QDomElement tag = doc.createElement("file");
        QDomText text = doc.createTextNode(file);

        tag.appendChild(text);
        qresource.appendChild(tag);
    }

    m_text = doc.toString(4);
}
