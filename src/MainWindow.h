//
// Created by Maxim on 13.06.2022.
//

#ifndef SEARCH_ENGINE_MAINWINDOW_H
#define SEARCH_ENGINE_MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QProcess>
#include <QDesktopServices>
#include <exception>
#include <ctime>
#include "ui_UI.h"
#include "ImplSearchClasses.h"


class MainWindow : public QMainWindow
{
public:
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr) : QMainWindow(parent), ui(new Ui::MainWindow()), pImpl(std::make_unique<Impl>())
    {
        ui->setupUi(this);
    };
    ~MainWindow()
    {
        delete ui;
    }

public slots:
    void showMore()
    {
        ui->resultList->clear();

        ui->show_more_btn->setEnabled(false);

        if(pImpl->sS->search_result.empty())
        {
            logger("No results!", ui);
            ui->show_more_btn->setEnabled(true);
            return;
        }

        for(size_t it{0}, end = pImpl->cJ->GetResponsesLimit(), endOfResult{pImpl->sS->search_result.size()};
            it < end && it < endOfResult; ++it)
        {
            try {
                makeItem(ui->resultList, pImpl->sS->search_result[it].filePath.c_str());
            }
            catch(std::exception& exc)
            {
                ui->servMessages->setMarkdown(ui->servMessages->toMarkdown() += exc.what());
            }
        }

        ui->show_more_btn->setEnabled(true);
    };

    void find()
    {
        ui->search_btn->setEnabled(false);

        ui->resultList->clear();
        pImpl->sS->search(ui->queryLine->text().toStdString(), ui);

        if(pImpl->sS->search_result.empty())
        {
            logger("No results!", ui);
            ui->search_btn->setEnabled(true);
            return;
        }

        for(size_t it{0}, end = pImpl->cJ->GetResponsesLimit(), endOfResult{pImpl->sS->search_result.size()};
            it < end && it < endOfResult; ++it)
        {
            try {
                makeItem(ui->resultList, pImpl->sS->search_result[it].filePath.c_str());
            }
            catch(std::exception& exc)
            {
                ui->servMessages->setMarkdown(ui->servMessages->toMarkdown() += exc.what());
            }
        }

        ui->search_btn->setEnabled(true);
    };

    void updateDocBase()
    {
        ui->UDB_btn->setEnabled(false);
        pImpl->sS->updateInvertedIndex(pImpl->cJ->GetNamesDocuments(), ui);
        ui->UDB_btn->setEnabled(true);
    };

    void sm_hideShow() //Скрыть/показать сервисные сообщения
    {
        if(ui->servMessages->isHidden())
        {
            ui->servMessages->show();
        }
        else
        {
            ui->servMessages->hide();
        }
    }

    void sm_clear() //Очистка сервисных сообщений
    {
        ui->servMessages->clear();
    }

    static void logger(const QString& message, Ui::MainWindow* ui)
    {
        char buffer[25];
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        const char* format = "%d.%m.%Y %H:%M:%S";
        strftime(buffer, 25, format, now);

        ui->servMessages->setMarkdown(ui->servMessages->toMarkdown() + "[" + buffer + "]" + " " + message);
    }

private: //private methods

    void makeItem(QListWidget* lstWgt, QString filePath)
    {
        auto* wgt = new QWidget;
        QLayout* l = new QHBoxLayout;

        auto* lineEdit = new QLineEdit(filePath);
        lineEdit->setReadOnly(true);

        l->addWidget(lineEdit);

        auto* btn = new QPushButton("Open file");

        QObject::connect(btn, &QPushButton::clicked, [filePath]()
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
        });

        l->addWidget(btn);
        wgt->setLayout(l);

        auto* item = new QListWidgetItem(lstWgt);
        item->setSizeHint(wgt->sizeHint());
        lstWgt->setItemWidget(item, wgt);
    }

private: //private fields
    Ui::MainWindow* ui;
    std::unique_ptr<Impl> pImpl;
};

#endif //SEARCH_ENGINE_MAINWINDOW_H

#include "MainWindow.moc"