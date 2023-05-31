#pragma once

#ifndef MDIDOCUMENT_H
#define MDIDOCUMENT_H

#include <QTextEdit>

class MDIDocument: public QTextEdit
{
    Q_OBJECT

public:
    MDIDocument(QWidget* pwgt = 0);
    ~MDIDocument();

signals:
    void changeWindowTitle(QString);

public slots:
    void slotLoad  ();
    void slotSave  ();
    void slotSaveAs();

private:
    QString m_strFileName;
};

#endif // MDIDOCUMENT_H
