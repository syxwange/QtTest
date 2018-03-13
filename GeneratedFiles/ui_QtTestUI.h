/********************************************************************************
** Form generated from reading UI file 'QtTestUI.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTTESTUI_H
#define UI_QTTESTUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "copenglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_QtTestUIClass
{
public:
    QVBoxLayout *verticalLayout;
    COpenGLWidget *openGLWidget;
    QPushButton *pushButton;

    void setupUi(QWidget *QtTestUIClass)
    {
        if (QtTestUIClass->objectName().isEmpty())
            QtTestUIClass->setObjectName(QStringLiteral("QtTestUIClass"));
        QtTestUIClass->resize(1018, 642);
        verticalLayout = new QVBoxLayout(QtTestUIClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        openGLWidget = new COpenGLWidget(QtTestUIClass);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));

        verticalLayout->addWidget(openGLWidget);

        pushButton = new QPushButton(QtTestUIClass);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(QtTestUIClass);

        QMetaObject::connectSlotsByName(QtTestUIClass);
    } // setupUi

    void retranslateUi(QWidget *QtTestUIClass)
    {
        QtTestUIClass->setWindowTitle(QApplication::translate("QtTestUIClass", "QtTestUI", Q_NULLPTR));
        pushButton->setText(QApplication::translate("QtTestUIClass", "\346\222\255 \346\224\276", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtTestUIClass: public Ui_QtTestUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTTESTUI_H
