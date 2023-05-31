#include <QtWidgets>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QTextStream>
#include <QTextEdit>
#include "translator.h"

Translator::Translator(QWidget *parent)
    : QMainWindow(parent)
{
    QAction* pactOpen = new QAction("Open File", 0);
    pactOpen->setText("&Open...");
    pactOpen->setShortcut(QKeySequence("CTRL+O"));
    pactOpen->setToolTip("Open Document");
    pactOpen->setStatusTip("Open an existing file");
    pactOpen->setWhatsThis("Open an existing file");
    pactOpen->setIcon(QPixmap("::/rsc/imgs/fileopen.png"));
    connect(pactOpen, SIGNAL(triggered()), SLOT(slotLoad()));

    QAction* pactSave = new QAction("Save File", 0);
    pactSave->setText("&Save");
    pactSave->setShortcut(QKeySequence("CTRL+S"));
    pactSave->setToolTip("Save Document");
    pactSave->setStatusTip("Save the file to disk");
    pactSave->setWhatsThis("Save the file to disk");
    pactSave->setIcon(QPixmap("::/rsc/imgs/filesave.png"));
    connect(pactSave, SIGNAL(triggered()), SLOT(slotSave()));

    QAction* pactTranslate = new QAction("Translate", 0);
    pactTranslate->setText("&Translate");
    pactTranslate->setShortcut(QKeySequence("CTRL+T"));
    pactTranslate->setToolTip("Translate document from MINI-BASIC to Assembler");
    pactTranslate->setStatusTip("Translate document from MINI-BASIC to Assembler");
    pactTranslate->setWhatsThis("Translate document from MINI-BASIC to Assembler");
    connect(pactTranslate, SIGNAL(triggered()), SLOT(slotTranslate()));

    QToolBar* ptbFile = new QToolBar("File Operations");
    ptbFile->addAction(pactOpen);
    ptbFile->addAction(pactSave);
    ptbFile->addAction(pactTranslate);
    addToolBar(Qt::TopToolBarArea, ptbFile);

    QMenu* pmnuFile = new QMenu("&File");
    pmnuFile->addAction(pactOpen);
    pmnuFile->addAction(pactSave);
    pmnuFile->addAction("Save &As...", this, SLOT(slotSaveAs()));
    pmnuFile->addAction(pactTranslate);
    pmnuFile->addSeparator();
    pmnuFile->addAction("&Quit",
                        QKeySequence("CTRL+Q"),
                        qApp,
                        SLOT(closeAllWindows())
                        );
    menuBar()->addMenu(pmnuFile);

    QMenu* pmnuHelp = new QMenu("&Help");
    pmnuHelp->addAction("&About", Qt::Key_F1, this, SLOT(slotAbout()));
    menuBar()->addMenu(pmnuHelp);

    m_workArea = new QMdiArea;
    m_workArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_workArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(m_workArea);

    statusBar()->showMessage("Ready", 3000);

    createMyDocuments();
}

Translator::~Translator()
{
    delete[] m_ADAM;
    delete[] m_EVA;
}

/*//////////////////////////////////////////////////////////////*/
void Translator::createMyDocuments()
{
    m_docProgram = new MDIDocument;
    m_docTranslate = new MDIDocument;

    m_workArea->addSubWindow(m_docProgram, Qt::CustomizeWindowHint | Qt::Tool | Qt::WindowTitleHint);
    m_docProgram->setAttribute(Qt::WA_DeleteOnClose);
    m_docProgram->setWindowTitle("Your Program");
    m_docProgram->setWindowIcon(QPixmap(":/rsc/imgs/filenew.png"));
    m_docProgram->setPlainText("Load file with program");
    connect(m_docProgram, SIGNAL(changeWindowTitle(QString)), SLOT(slotChangedWindowTitle(QString)));

    m_workArea->addSubWindow(m_docTranslate, Qt::CustomizeWindowHint | Qt::Tool | Qt::WindowTitleHint);

    m_docTranslate->setAttribute(Qt::WA_DeleteOnClose);
    m_docTranslate->setReadOnly(true);
    m_docTranslate->setWindowTitle("Translate");
    m_docTranslate->setWindowIcon(QPixmap(":/rsc/imgs/filenew.png"));
    connect(m_docTranslate, SIGNAL(changeWindowTitle(QString)), SLOT(slotChangedWindowTitle(QString)));

    m_docProgram->setMinimumSize(m_workArea->size().rwidth() - 50, m_workArea->size().rheight());
    m_docTranslate->setMinimumSize(m_workArea->size().rwidth() - 50, m_workArea->size().rheight());
}

/*//////////////////////////////////////////////////////////////*/

void Translator::slotTranslate()
{
    m_ADAM = new Lex_block(m_docProgram->windowTitle().toStdString());
    m_ADAM->parse();
    if (m_ADAM->get_errorsFlag() == false)
    {
        m_EVA = new BF_grammar("./grammar.txt", m_ADAM->get_lexem_list());
        m_EVA->synth_analize();
        if (!m_EVA->get_errorFlag())
            m_docTranslate->setPlainText(m_EVA->m_outputStr);
        else
            m_docTranslate->setPlainText("Synth block met error!");
    }
    else
         m_docTranslate->setPlainText("Lex block met error!");
}

/*//////////////////////////////////////////////////////////////*/

void Translator::slotNewDocument()
{
    MDIDocument* doc = createNewDocument();
    doc->show();
}

MDIDocument* Translator::createNewDocument()
{
    MDIDocument* doc = new MDIDocument;
    m_workArea->addSubWindow(doc, Qt::CustomizeWindowHint | Qt::Tool | Qt::WindowTitleHint);
    doc->setAttribute(Qt::WA_DeleteOnClose);
    doc->setWindowTitle("Unnamed Document");
    doc->setWindowIcon(QPixmap(":/rsc/imgs/filenew.png"));
    connect(doc, SIGNAL(changeWindowTitle(QString)), SLOT(slotChangedWindowTitle(QString)));

    return doc;
}

void Translator::slotChangedWindowTitle(QString str)
{
    qobject_cast<MDIDocument*>(sender())->setWindowTitle(str);
}

void Translator::slotLoad()
{
    statusBar()->showMessage("Loading...");
    m_docProgram->slotLoad();
    m_docTranslate->setPlainText("");
    statusBar()->showMessage("Successfully loaded.", 2000);
}

void Translator::slotSave()
{
    m_docProgram->slotSave();
    statusBar()->showMessage("Successfully saved.", 2000);
}

void Translator::slotSaveAs()
{
    statusBar()->showMessage("Saving...");
    m_docProgram->slotSaveAs();
    statusBar()->showMessage("Successfully saved.", 2000);
}

void Translator::slotAbout()
{
    QMessageBox::about(this, "Application", "Translate from MINI-BASIC to ASSembler");
}

void Translator::slotWindows()
{
    m_menuWindows->clear();

    QAction* pact = m_menuWindows->addAction("&Cascade",
                                             m_workArea,
                                             SLOT(cascadeSubWindows())
                                             );
    pact->setEnabled(!m_workArea->subWindowList().isEmpty());

    pact = m_menuWindows->addAction("&Tile",
                                    m_workArea,
                                    SLOT(tileSubWindows())
                                    );
    pact->setEnabled(!m_workArea->subWindowList().isEmpty());

    m_menuWindows->addSeparator();

    QList<QMdiSubWindow*> listDoc = m_workArea->subWindowList();
    for (int i = 0; i < listDoc.size(); ++i)
    {
        pact = m_menuWindows->addAction(listDoc.at(i)->windowTitle());
        pact->setCheckable(true);
        pact->setChecked(m_workArea->activeSubWindow() == listDoc.at(i));
        connect(pact, SIGNAL(triggered()), m_sigMapper, SLOT(map()));
        m_sigMapper->setMapping(pact, listDoc.at(i));
    }
}

void Translator::slotSetActiveSubWindow(QObject* obj)
{
    if (obj) {
        m_workArea->setActiveSubWindow(qobject_cast<QMdiSubWindow*>(obj));
    }
}
