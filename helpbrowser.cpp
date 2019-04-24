#include "helpbrowser.h"

HelpBrowser::HelpBrowser(const QString &p_path, const QString &p_page, QWidget *parent) : QWidget(parent)
{
    textBrowser = new QTextBrowser(this);
      homeButton = new QPushButton(tr("&Home"), this);
      backButton = new QPushButton(tr("&Back"), this);
      closeButton = new QPushButton(tr("Close"), this);
     // closeButton=>sets
      closeButton->setShortcut(tr("Esc"));

      QVBoxLayout *mainLayout = new QVBoxLayout(this);
     // QHBoxLayout *buttonLayout = new QHBoxLayout((QWidget*)mainLayout);
      QHBoxLayout *buttonLayout = new QHBoxLayout();
      buttonLayout->addWidget(homeButton);
      buttonLayout->addWidget(backButton);
      buttonLayout->addStretch(1);
      buttonLayout->addWidget(closeButton);
      mainLayout->addLayout(buttonLayout);
      mainLayout->addWidget(textBrowser);

      connect(homeButton, SIGNAL(clicked()),
              textBrowser, SLOT(home()));
      connect(backButton, SIGNAL(clicked()),
              textBrowser, SLOT(backward()));
      connect(closeButton, SIGNAL(clicked()),
              this, SLOT(close()));
      connect(textBrowser, SIGNAL(sourceChanged(const QUrl&)),
              this, SLOT(updateCaption()));

      textBrowser->setSearchPaths({p_path});

      //textBrowser->mimeSourceFactory()->addFilePath(p_path);
      textBrowser->setSource(p_page);
}


void HelpBrowser::updateCaption()
{
  setWindowTitle(tr("Help: %1").arg(textBrowser->documentTitle()));
}


void HelpBrowser::showPage(const QString &page)
{
  QString path = qApp->applicationDirPath() + "/doc";
  qDebug()<<"application path "<<path;
  HelpBrowser *browser = new HelpBrowser(path, page);
  browser->resize(500, 400);
  browser->show();
}
