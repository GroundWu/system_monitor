#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtWidgets/QWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QDir>
#include <QFile>
#include <QtCore/QTimer>
#include "chart.h"
#include <QTextStream>
#include <QIODevice>

QT_BEGIN_NAMESPACE
class QPushButton;
class QCheckBox;
class QLabel;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class MainWidget: public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private Q_SLOTS:
    void update_ui();
    void stop();
    void start();

private:
    QPushButton *createStartButton() const;
    QPushButton *createStopButton() const;
    QCheckBox *createLOGBOX() const;
    void connectSignals();
    Chart *createCPUChart() const;
    Chart *createMEMChart() const;
    Chart *createDISKChart() const;
    Chart *createNETChart() const;
    void create_open_log_file(QString path="./Log");

private:
    sys_usage *su;
    QList<QChartView *> m_charts;
    //log
    QList<QString> time_l;
    QList<float> cpu_l;
    QList<float> mem_l;
    QList<float> disk_l;
    QList<float> net_l;


    QPushButton *start_button;
    QPushButton *stop_button;
    QCheckBox * is_log;

    QLabel *r1;
    QLabel *r2;

    QTimer m_timer;
    bool is_start;
    QFile *log_file;
};

#endif // MAINWIDGET_H
