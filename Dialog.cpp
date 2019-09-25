#include "Dialog.h"
#include "ui_Dialog.h"
#include <QRandomGenerator>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_btnGenerate_clicked()
{
    QString __reg3 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    QString __reg6;

    switch (ui->comboBox->currentIndex()) {
    case 0:     //����
    case 1:     //��ѧ
    case 2:     //Ӣ��
    case 3:     //����
    case 4:     //��ѧ
    case 5:     //����
        __reg6 = "GL";      //�������
        break;
    default:    //���Ρ���ʷ������
        __reg6 = "GW";      //�����Ŀ�
    }

    auto genSn = [=]() -> QString {
        //        QRandomGenerator rand;

        QString sn;
        for (int i = 0; i < 14; i++) {
            quint32 iPos = quint32(QRandomGenerator::global()->bounded(36));
            sn += __reg3.at(iPos);
        }
//        qDebug() << QStringLiteral("����ע���룺") << sn;
        return sn;
    };

    auto chkSn = [=](QString __reg7) -> bool {
        quint8 __reg5 = 0;
        quint8 __reg4 = 0;
        quint8 __reg2 = 0;
        while (__reg2 < __reg6.length()) {
            __reg5 = __reg5 + __reg3.indexOf(__reg6.at(__reg2));
            __reg5 = __reg5 % __reg3.length();
            ++__reg2;
        }
        //        qDebug() << "__reg5:" << __reg5;
        __reg2 = 0;
        while (__reg2 < __reg7.length()) {
            __reg4 = __reg4 + __reg3.indexOf(__reg7.at(__reg2));
            __reg4 = __reg4 % __reg3.length();
            ++__reg2;
        }

        //        qDebug() << "__reg4:" << __reg4;

        if (__reg5 != __reg4) {
            return false;
        }
        return true;
    };

    QString reg7;
    do {
        reg7 = genSn();

    } while (!chkSn(reg7));

    QString strSN = __reg6 + reg7.mid(0, 2) + "-" + reg7.mid(2, 4) + "-" + reg7.mid(6, 4) + "-"
                    + reg7.mid(10, 4);

    qDebug() << QStringLiteral("��Ч��ע���룺") << strSN;
    ui->edSN1->setText( __reg6 + reg7.mid(0,2) );
    ui->edSN2->setText( reg7.mid(2,4) );
    ui->edSN3->setText( reg7.mid(6,4) );
    ui->edSN4->setText( reg7.mid(10,4) );
}
