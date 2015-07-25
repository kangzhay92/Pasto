#ifndef PASTO_H
#define PASTO_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtNetwork>

class Editor;

class Pasto : public QMainWindow
{
    Q_OBJECT

public:
    Pasto(QWidget *parent = 0);
    ~Pasto();

private slots:
    void upload();
    void uploadSelesai(QNetworkReply* balasan);
    void copyAlamatURL();

private:
    Editor* editor;
    QLineEdit* alamatURL;
    QCheckBox* cbPrivate;
    QSplitter* splitter;
    QComboBox* cboPilihBahasa;
    QComboBox* cboWaktuHabis;
    QPushButton* btnUpload;
    QPushButton* btnCopyURL;
    QNetworkAccessManager* manager;
    QLabel* lblPilihBahasa;
    QLabel* lblWaktuHabis;
    QLabel* lblAlamatURL;
};

#endif // PASTO_H
