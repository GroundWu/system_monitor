#include "main_widget.h"

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtCore/QTime>
#include <QDateTime>


MainWidget::MainWidget(QWidget *parent):
    QWidget (parent),
    su(new sys_usage()),
    start_button(createStartButton()),
    stop_button(createStopButton()),
    is_log(createLOGBOX()),
    r1(new QLabel("CPU Usage:\t\nMemory Usage:\t")),
    r2(new QLabel("Disk Speed:\t\nNet Speed:\t")),
    is_start(0)
{
    connectSignals();

    QGridLayout *baseLayout = new QGridLayout();
    QHBoxLayout *settingLayout = new QHBoxLayout();
    settingLayout->addWidget(start_button);
    settingLayout->addWidget(stop_button);
    settingLayout->addWidget(new QLabel("Log:"));
    settingLayout->addWidget(is_log);
    settingLayout->addStretch();

    baseLayout->addLayout(settingLayout,1,0);

    QLabel *title = new QLabel("System Monitor");
    QFont ft;
    ft.setPointSize(18);
    title->setFont(ft);
    baseLayout->addWidget(title,0,1);

    //create charts
    QChartView *chartView;

    chartView = new QChartView(createCPUChart());
    chartView->setRenderHint(QPainter::Antialiasing);
    baseLayout->addWidget(chartView, 2, 0);
    m_charts << chartView;

    baseLayout->addWidget(r1,2,2);


    chartView = new QChartView(createMEMChart());
    chartView->setRenderHint(QPainter::Antialiasing);
    baseLayout->addWidget(chartView, 2, 1);
    m_charts << chartView;


    chartView = new QChartView(createDISKChart());
    chartView->setRenderHint(QPainter::Antialiasing);
    baseLayout->addWidget(chartView, 3, 0);
    m_charts << chartView;

    chartView = new QChartView(createNETChart());
    chartView->setRenderHint(QPainter::Antialiasing);
    // Funny things happen if the pie slice labels do not fit the screen, so we ignore size policy
    chartView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    baseLayout->addWidget(chartView, 3, 1);
    m_charts << chartView;

    baseLayout->addWidget(r2,3,2);

    setLayout(baseLayout);

    if(is_start==0)
        stop_button->setEnabled(false);


}

void MainWidget::connectSignals()
{
    connect(&m_timer,&QTimer::timeout,this,&MainWidget::update_ui);
    m_timer.setInterval(1000);
    connect(start_button,&QPushButton::clicked,this,&MainWidget::start);
    connect(stop_button,&QPushButton::clicked,this,&MainWidget::stop);
}

MainWidget::~MainWidget()
{

}

QPushButton* MainWidget::createStartButton() const
{
    QPushButton *b = new QPushButton();
    b->setText("start");
    return b;
}

QPushButton* MainWidget::createStopButton() const
{
    QPushButton *b = new QPushButton();
    b->setText("stop");
    return b;
}

QCheckBox* MainWidget::createLOGBOX() const
{
    QCheckBox* c = new QCheckBox();
    return c;
}

Chart* MainWidget::createCPUChart() const
{
    Chart *chart = new Chart(su);
    chart->set_metrics_type(1);
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    return chart;
}

Chart* MainWidget::createMEMChart() const
{
    Chart *chart = new Chart(su);
    chart->set_metrics_type(2);
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    return chart;
}

Chart* MainWidget::createDISKChart() const
{
    Chart *chart = new Chart(su);
    chart->set_metrics_type(3);
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    return chart;
}

Chart* MainWidget::createNETChart() const
{
    Chart *chart = new Chart(su);
    chart->set_metrics_type(4);
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    return chart;
}

void MainWidget::update_ui()
{
    float cpu = su->get_cpu_usage();
    float mem = su->get_mem_usage();
    float disk = su->get_disk_usage();
    float net = su->get_net_usage();

    QString s1 =QString("CPU Usage: %1%\nMemory Usage: %2%").arg(QString::number(cpu*100,'f',2)).arg(QString::number(mem*100,'f',2));
    QString s2 = QString("Disk Speed: %1 KB/s \nNet Speed: %2 KB/s ").arg(disk).arg(net);
    r1->setText(s1);
    r2->setText(s2);

    static_cast<Chart*>(m_charts[0]->chart())->handleTimeout(cpu*100);
    static_cast<Chart*>(m_charts[1]->chart())->handleTimeout(mem*100);
    static_cast<Chart*>(m_charts[2]->chart())->handleTimeout(disk);
    static_cast<Chart*>(m_charts[3]->chart())->handleTimeout(net);

    //
    if(is_log->isChecked()){
        QDateTime cur = QDateTime::currentDateTime();
        QString cur_date = cur.toString("yyyy-MM-dd hh:mm:ss");
        time_l.append(cur_date);
        cpu_l.append(cpu);
        mem_l.append(mem);
        disk_l.append(disk);
        net_l.append(net);
    }

}

void MainWidget::start()
{
    if(is_start==0){

        is_start=1;
        start_button->setEnabled(0);
        stop_button->setEnabled(1);

        if(is_log->isChecked()){
            time_l.clear();
            cpu_l.clear();
            mem_l.clear();
            disk_l.clear();
            net_l.clear();
        }

        m_timer.start();
    }
}

void MainWidget::stop()
{
    if(is_start==1){
        is_start=0;
        stop_button->setEnabled(0);
        start_button->setEnabled(1);
        if(is_log->isChecked()){
            create_open_log_file();
        }
         m_timer.stop();
    }
}

void MainWidget::create_open_log_file(QString path)
{
    QString file;
    QDir *folder = new QDir();
    bool exist = folder->exists(path);
    if(!exist){
        folder->mkdir(path);
    }
    QDateTime cur = QDateTime::currentDateTime();
    QString cur_date = cur.toString("yyyy-MM-dd-hh-mm-ss");
    file = path+"/"+cur_date+".csv";
    QFile *f = new QFile(file);
    if(f->open(QIODevice::WriteOnly|QIODevice::Text)){
        // write logfile title
        QString str = QString("%1,%2,%3,%4,%5\n").arg("Time").arg("CPU Usage").arg("Memory Usage").arg("Disk Speed").arg("Net Speed");
        QTextStream out(f);
        out<<str;
        for(int i=0;i<time_l.size();i++){
            QString data  = QString("%1,%2,%3,%4,%5\n").arg(time_l[i]).arg(cpu_l[i]).arg(mem_l[i]).arg(disk_l[i]).arg(net_l[i]);
            out<<data;
        }
    }
    f->close();
}

