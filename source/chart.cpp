#include "chart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QTime>
#include <QtCore/QDebug>

Chart::Chart(sys_usage *su,QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series(0),
    m_axis(new QValueAxis),
    m_step(0),
    m_x(5),
    m_y(0)
{

    m_series = new QSplineSeries(this);
    QPen green(Qt::red);
    green.setWidth(3);
    m_series->setPen(green);
    m_series->append(m_x, m_y);

    addSeries(m_series);
    createDefaultAxes();
    setAxisX(m_axis, m_series);
    m_axis->setTickCount(5);
    axisX()->setRange(0, 10);
    axisX()->hide();
    axisY()->setRange(0,100);
}

void Chart::set_sys_usage(sys_usage *su)
{
    this->su = su ;
}

void Chart::set_metrics_type(int i)
{
    //i:1-CPU,2-MEM,3-DISK,4-NET
    metric_type = i;
    if(i==1){
        setTitle("CPU Usage(%)");
    }else if(i==2)
    {
        setTitle("Memory Usage(%)");
    }else if(i==3)
    {
        setTitle("Disk Speed(KB/s)");
        axisY()->setRange(0,1000);
    }else if(i=4)
    {
        setTitle("Net Speed(KB/s)");
        axisY()->setRange(0,1000);
    }
}

float Chart::set_m_y()
{
    if(metric_type==1)
        return su->get_cpu_usage()*100;
    else if(metric_type==2)
        return su->get_mem_usage()*100;
    else if(metric_type==3){

        return su->get_disk_usage();
    }
    else if(metric_type==4){

        return su->get_net_usage();
    }
}
Chart::~Chart()
{

}

void Chart::handleTimeout(qreal value)
{
    qreal x = plotArea().width() / m_axis->tickCount();
    qreal y = (m_axis->max() - m_axis->min()) / m_axis->tickCount();
    m_x += y;
    m_y = value;
    m_series->append(m_x, m_y);
    scroll(x, 0);
}
