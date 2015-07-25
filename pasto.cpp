#include <QClipboard>
#include "pasto.h"
#include "editor.h"

#define TOTAL_BAHASA 15
#define TOTAL_WAKTU_HABIS 5

struct Bahasa
{
    QString id;
    QString display;
};

struct WaktuHabis
{
    QString display;
    QString detik;
};

static const Bahasa bahasa[] =
{
    { "cpp",     "C++" },
    { "csharp",  "C#" },
    { "css",     "CSS" },
    { "delphi",  "Delphi" },
    { "groovy",  "Groovy" },
    { "java",    "Java" },
    { "jscript", "JavaScript" },
    { "perl",    "Perl" },
    { "php",     "PHP" },
    { "plain",   "Teks Biasa" },
    { "python",  "Python" },
    { "ruby",    "Ruby" },
    { "sql",     "SQL" },
    { "vb",      "Visual Basic" },
    { "xml",     "XML/HTML" }
};

static const WaktuHabis waktuHabis[] =
{
    { "Tidak Pernah", "0" },
    { "10 Menit",     "600" },
    { "1 Jam",        "3600" },
    { "1 Hari",       "86400" },
    { "1 Bulan",      "2592000" }
};

Pasto::Pasto(QWidget *parent) : QMainWindow(parent)
{
    editor = new Editor;

    alamatURL = new QLineEdit;
    alamatURL->setReadOnly(true);

    lblAlamatURL = new QLabel(tr("Alamat URL:"));
    lblAlamatURL->setBuddy(alamatURL);

    cbPrivate = new QCheckBox("Private");

    cboPilihBahasa = new QComboBox;
    lblPilihBahasa = new QLabel(tr("Pilih Bahasa:"));
    lblPilihBahasa->setBuddy(cboPilihBahasa);

    cboWaktuHabis = new QComboBox;
    lblWaktuHabis = new QLabel(tr("Waktu Habis:"));
    lblWaktuHabis->setBuddy(cboWaktuHabis);

    btnUpload = new QPushButton(tr("Upload"));
    btnCopyURL = new QPushButton(tr("Copy Alamat URL..."));

    manager = new QNetworkAccessManager;

    connect(btnUpload, SIGNAL(clicked()), this, SLOT(upload()));
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(uploadSelesai(QNetworkReply*)));
    connect(btnCopyURL, SIGNAL(clicked()), this, SLOT(copyAlamatURL()));

    for (int i = 0; i < TOTAL_BAHASA; i++)
    {
        cboPilihBahasa->addItem(bahasa[i].display);
    }
    for (int i = 0; i < TOTAL_WAKTU_HABIS; i++)
    {
        cboWaktuHabis->addItem(waktuHabis[i].display);
    }

    splitter = new QSplitter;
    splitter->setOrientation(Qt::Vertical);

    QWidget* widget = new QWidget;
    QGridLayout* gridLayout = new QGridLayout;
    gridLayout->addWidget(cbPrivate, 0, 0);
    gridLayout->addWidget(lblPilihBahasa, 1, 0);
    gridLayout->addWidget(cboPilihBahasa, 1, 1);
    gridLayout->addWidget(lblWaktuHabis, 2, 0);
    gridLayout->addWidget(cboWaktuHabis, 2, 1);
    gridLayout->addWidget(btnUpload, 3, 0);
    gridLayout->addWidget(lblAlamatURL, 5, 0);
    gridLayout->addWidget(alamatURL, 6, 0);
    gridLayout->addWidget(btnCopyURL, 7, 0);
    widget->setLayout(gridLayout);

    splitter->addWidget(editor);
    splitter->addWidget(widget);

    setCentralWidget(splitter);
    setWindowTitle(tr("Pasto"));
}

Pasto::~Pasto()
{
}

void Pasto::upload()
{
    QNetworkRequest request(QUrl("http://paste.strictfp.com/index.php"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QByteArray data;
    QUrlQuery param;

    param.addQueryItem("paste", editor->toPlainText());
    param.addQueryItem("language", bahasa[cboPilihBahasa->currentIndex()].id);
    param.addQueryItem("submit", "Upload");
    param.addQueryItem("expires", waktuHabis[cboWaktuHabis->currentIndex()].detik);

    if (cbPrivate->checkState() == Qt::Checked)
    {
        param.addQueryItem("private", "Private");
    }

    data = param.query(QUrl::FullyEncoded).toUtf8();

    manager->post(request, data);
}

void Pasto::uploadSelesai(QNetworkReply* balasan)
{
    if (balasan->error() == QNetworkReply::NoError)
    {
        QMessageBox::information(this, "Upload Berhasil", "Alamat URL sudah bisa dicopy");
    }
    else
    {
        QMessageBox::warning(this, "Upload Gagal", balasan->errorString());
        return;
    }

    QString url = "http://paste.strictfp.com/" + balasan->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl().toString();
    alamatURL->setText(url);
}

void Pasto::copyAlamatURL()
{
    QApplication::clipboard()->setText(alamatURL->text());
}
