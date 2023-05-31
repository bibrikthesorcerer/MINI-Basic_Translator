#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QMainWindow>
#include <QMenu>
#include <QMdiArea>
#include "mdidocument.h"
#include "SynthBlock/synth_block.h"
#include "LexBlock/lex_block.h"
#include <QSignalMapper>

class Translator : public QMainWindow
{
    Q_OBJECT

public:
    Translator(QWidget *parent = nullptr);
    ~Translator();

private slots:
    void slotChangedWindowTitle(QString);

    void slotNewDocument       (        );
    void slotLoad              (        );
    void slotSave              (        );
    void slotSaveAs            (        );
    void slotAbout             (        );
    void slotWindows           (        );
    void slotSetActiveSubWindow(QObject*);

    void slotTranslate();

private:
    QMdiArea* m_workArea;
    QMenu* m_menuWindows;
    QSignalMapper* m_sigMapper;

    MDIDocument* m_docProgram = nullptr;
    MDIDocument* m_docTranslate = nullptr;

    Lex_block* m_ADAM;
    BF_grammar* m_EVA;
private:
    MDIDocument* createNewDocument();
    void createMyDocuments();
};

#endif // TRANSLATOR_H
