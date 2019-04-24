#ifndef HELPBROWSER_H
#define HELPBROWSER_H

#include <QtWidgets>

class HelpBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit HelpBrowser(const QString &p_path, const QString &p_page,QWidget *parent = nullptr);
    static void showPage(const QString &p_page);
private  slots:
    void updateCaption();

private:
    QTextBrowser *textBrowser;
    QPushButton *homeButton;
    QPushButton *backButton;
    QPushButton *closeButton;
};

#endif // HELPBROWSER_H
