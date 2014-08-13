#include "infodialog.h"
#include "ui_infodialog.h"
#include "QtWebKitWidgets/QWebView"
#include "QUrl"

InfoDialog::InfoDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::InfoDialog)
{
    ui->setupUi(this);
}

InfoDialog::~InfoDialog()
{
    delete ui;
}

void InfoDialog::on_twitterBtn_clicked()
{
    QWebView* webView = new QWebView();
    webView->setAttribute(Qt::WA_DeleteOnClose, true);
    webView->load(QUrl("http://twitter.com/share?text=Ich spiele gerad QT Mau Mau! github.com/pFriesch/qtMauMau"));
    // webView->load(QUrl("http://google.de/"));
    webView->show();
}
