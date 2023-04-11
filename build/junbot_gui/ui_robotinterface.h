/********************************************************************************
** Form generated from reading UI file 'robotinterface.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROBOTINTERFACE_H
#define UI_ROBOTINTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RobotInterface
{
public:
    QWidget *centralwidget;
    QWidget *control_btn;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *forward;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *r_left;
    QPushButton *stop;
    QPushButton *r_right;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *back;
    QWidget *logo_widget;
    QLabel *label_logo;
    QGraphicsView *mapView;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_time;
    QProgressBar *progressBar;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_status;
    QLabel *label_power;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *RobotInterface)
    {
        if (RobotInterface->objectName().isEmpty())
            RobotInterface->setObjectName(QString::fromUtf8("RobotInterface"));
        RobotInterface->resize(990, 600);
        centralwidget = new QWidget(RobotInterface);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        control_btn = new QWidget(centralwidget);
        control_btn->setObjectName(QString::fromUtf8("control_btn"));
        control_btn->setGeometry(QRect(10, 30, 361, 291));
        verticalLayoutWidget = new QWidget(control_btn);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 341, 271));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        forward = new QPushButton(verticalLayoutWidget);
        forward->setObjectName(QString::fromUtf8("forward"));
        forward->setMinimumSize(QSize(64, 64));
        forward->setMaximumSize(QSize(64, 64));
        forward->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/image/data/images/up.png);}\n"
"QPushButton{border:none;}\n"
"QPushButton:pressed{border-image: url(:/image/data/images/up_2.png);}"));

        horizontalLayout->addWidget(forward, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        r_left = new QPushButton(verticalLayoutWidget);
        r_left->setObjectName(QString::fromUtf8("r_left"));
        r_left->setMinimumSize(QSize(64, 64));
        r_left->setMaximumSize(QSize(64, 16777215));
        r_left->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/image/data/images/left.png);}\n"
"QPushButton{border:none;}\n"
"QPushButton:pressed{border-image: url(:/image/data/images/left_2.png);}"));

        horizontalLayout_2->addWidget(r_left, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        stop = new QPushButton(verticalLayoutWidget);
        stop->setObjectName(QString::fromUtf8("stop"));
        stop->setMinimumSize(QSize(64, 64));
        stop->setMaximumSize(QSize(64, 16777215));
        stop->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/image/data/images/stop.png);}\n"
"QPushButton{border:none;}\n"
"QPushButton:pressed{border-image: url(:/image/data/images/stop-2.png);}"));

        horizontalLayout_2->addWidget(stop, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        r_right = new QPushButton(verticalLayoutWidget);
        r_right->setObjectName(QString::fromUtf8("r_right"));
        r_right->setMinimumSize(QSize(64, 64));
        r_right->setMaximumSize(QSize(64, 64));
        r_right->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/image/data/images/right.png);}\n"
"QPushButton{border:none;}\n"
"QPushButton:pressed{border-image: url(:/image/data/images/right_2.png);}"));

        horizontalLayout_2->addWidget(r_right, 0, Qt::AlignHCenter|Qt::AlignVCenter);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        back = new QPushButton(verticalLayoutWidget);
        back->setObjectName(QString::fromUtf8("back"));
        back->setMinimumSize(QSize(64, 64));
        back->setMaximumSize(QSize(64, 64));
        back->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/image/data/images/down.png);}\n"
"QPushButton{border:none;}\n"
"QPushButton:pressed{border-image: url(:/image/data/images/down_2.png);}"));

        horizontalLayout_3->addWidget(back);


        verticalLayout->addLayout(horizontalLayout_3);

        logo_widget = new QWidget(centralwidget);
        logo_widget->setObjectName(QString::fromUtf8("logo_widget"));
        logo_widget->setGeometry(QRect(20, 330, 351, 201));
        label_logo = new QLabel(logo_widget);
        label_logo->setObjectName(QString::fromUtf8("label_logo"));
        label_logo->setGeometry(QRect(0, 10, 341, 251));
        mapView = new QGraphicsView(centralwidget);
        mapView->setObjectName(QString::fromUtf8("mapView"));
        mapView->setGeometry(QRect(420, 120, 541, 431));
        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(420, 39, 251, 71));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_time = new QLabel(verticalLayoutWidget_2);
        label_time->setObjectName(QString::fromUtf8("label_time"));

        verticalLayout_2->addWidget(label_time);

        progressBar = new QProgressBar(verticalLayoutWidget_2);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy);
        progressBar->setMaximumSize(QSize(150, 16777215));
        progressBar->setValue(24);

        verticalLayout_2->addWidget(progressBar);

        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(690, 39, 271, 71));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_status = new QLabel(verticalLayoutWidget_3);
        label_status->setObjectName(QString::fromUtf8("label_status"));

        verticalLayout_4->addWidget(label_status);

        label_power = new QLabel(verticalLayoutWidget_3);
        label_power->setObjectName(QString::fromUtf8("label_power"));

        verticalLayout_4->addWidget(label_power);

        RobotInterface->setCentralWidget(centralwidget);
        menubar = new QMenuBar(RobotInterface);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 990, 19));
        RobotInterface->setMenuBar(menubar);
        statusbar = new QStatusBar(RobotInterface);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        RobotInterface->setStatusBar(statusbar);

        retranslateUi(RobotInterface);

        QMetaObject::connectSlotsByName(RobotInterface);
    } // setupUi

    void retranslateUi(QMainWindow *RobotInterface)
    {
        RobotInterface->setWindowTitle(QApplication::translate("RobotInterface", "MainWindow", nullptr));
        forward->setText(QString());
        r_left->setText(QString());
        stop->setText(QString());
        r_right->setText(QString());
        back->setText(QString());
        label_logo->setText(QString());
        label_time->setText(QApplication::translate("RobotInterface", "Time: ", nullptr));
        label_status->setText(QApplication::translate("RobotInterface", "Status: ", nullptr));
        label_power->setText(QApplication::translate("RobotInterface", "Power: ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RobotInterface: public Ui_RobotInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROBOTINTERFACE_H
