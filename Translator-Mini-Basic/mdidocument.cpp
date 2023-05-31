#include "mdidocument.h"
#include <QtWidgets>
#include <QDebug>

MDIDocument::MDIDocument(QWidget* pwgt /*=0*/) : QTextEdit(pwgt)
{
    connect(this, &QObject::destroyed, [](){qDebug("destroyed");});
}

MDIDocument::~MDIDocument()
{
}

void MDIDocument::slotLoad()
{
    QString str = QFileDialog::getOpenFileName();

    if(str.isEmpty())
        return;

    QFile file(str);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);

        QGuiApplication::setOverrideCursor(Qt::WaitCursor);
        setPlainText(stream.readAll());
        QGuiApplication::restoreOverrideCursor();

        file.close();

        m_strFileName = str;
        emit changeWindowTitle(m_strFileName);
    }
    else
    {
        qDebug() << "File didn't open!";
    }
}

void MDIDocument::slotSave()
{
    if(m_strFileName.isEmpty())
    {
        slotSaveAs();
        return;
    }

    QFile file(m_strFileName);
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream(&file) << toPlainText();
        file.close();
        emit changeWindowTitle(m_strFileName);
    }
    else
    {
        qDebug() << "File didn't open!";
    }
}

void MDIDocument::slotSaveAs()
{
    QString str = QFileDialog::getSaveFileName(0, m_strFileName);
    if(!str.isEmpty())
    {
        m_strFileName = str;
        slotSave();
    }
}
