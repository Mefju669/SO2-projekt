#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QThread>
#include <QMetaObject>
#include <iostream>
#include "RAMClass.h"
#include "DiskSpaceClass.h"
#include "StaticData.h"
#include "CPUClass.h"
#include "ReadingMethods.h"
#include "MonitorWorker.h""
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QWidget window;
    window.setWindowTitle("System Monitor");
    window.setGeometry(100, 100, 750, 550);
    window.setStyleSheet("background-color: white;");

    QVBoxLayout *mainLayout = new QVBoxLayout(&window);
    QHBoxLayout *centerLayout = new QHBoxLayout();

    QLabel *ramLabel = new QLabel(&window);
    ramLabel->setStyleSheet("color: red;"); // RAM label is red
    centerLayout->addWidget(ramLabel);

    QLabel *diskLabel = new QLabel(&window);
    diskLabel->setStyleSheet("color: green;"); // Disk label is green
    diskLabel->setContentsMargins(10, 0, 10, 0);
    centerLayout->addWidget(diskLabel);

    // Create chart for CPU and RAM usage
    QChart *chart = new QChart();
    chart->setTitle("CPU, RAM & Disk Utilization Over Time");
    chart->createDefaultAxes();

    QLineSeries *cpuSeries = new QLineSeries();
    cpuSeries->setName("CPU Usage");
    cpuSeries->setColor(Qt::blue); // CPU series is blue
    chart->addSeries(cpuSeries);

    QLineSeries *ramSeries = new QLineSeries();
    ramSeries->setName("RAM Usage");
    ramSeries->setColor(Qt::red); // RAM series is red
    chart->addSeries(ramSeries);

    QLineSeries *diskSeries = new QLineSeries();
    diskSeries->setName("Disk Usage");
    diskSeries->setColor(Qt::green); // Disk series is green
    chart->addSeries(diskSeries);

    // Set up the axes
    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(0, 60); // Display 60 seconds of data
    axisX->setLabelFormat("%d s");
    axisX->setTitleText("Time (s)");

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 100); // Set the maximum to 100% utilization
    axisY->setLabelFormat("%d%%");
    axisY->setTitleText("Usage (%)");

    chart->setAxisX(axisX);
    chart->setAxisY(axisY);

    // Set series for CPU, RAM, and Disk
    chart->setAxisX(axisX, cpuSeries);
    chart->setAxisY(axisY, cpuSeries);
    chart->setAxisX(axisX, ramSeries);
    chart->setAxisY(axisY, ramSeries);
    chart->setAxisX(axisX, diskSeries);
    chart->setAxisY(axisY, diskSeries);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Add the chart view to the center layout
    centerLayout->addWidget(chartView);

    // Add the center layout to the main layout
    mainLayout->addLayout(centerLayout);

    // Add process and cycles labels under the chart
    QLabel *processLabel = new QLabel(&window);
    processLabel->setStyleSheet("color: blue;");
    mainLayout->addWidget(processLabel);
    QLabel *cyclesLabel = new QLabel(&window);
    cyclesLabel->setStyleSheet("color: blue;");
    mainLayout->addWidget(cyclesLabel);

    // Set alignment to center for labels
    processLabel->setAlignment(Qt::AlignCenter);
    cyclesLabel->setAlignment(Qt::AlignCenter);

    // Start monitoring threads...

    window.setLayout(mainLayout);
    window.show();

    ReadingMethods readingMethods;
    CPUClass cpuClass;
    RAMClass ramClass;
    DiskSpaceClass diskSpaceClass;
    StaticData staticData;

    auto startLabelMonitoringInThread = [&](void (MonitorWorker::*monitorFunction)(QLabel*), QLabel* label) {
        QThread* thread = new QThread;
        MonitorWorker* worker = new MonitorWorker(cpuClass, ramClass, diskSpaceClass, staticData, readingMethods);
        worker->moveToThread(thread);

        QObject::connect(thread, &QThread::started, worker, [=]() { (worker->*monitorFunction)(label); });
        QObject::connect(thread, &QThread::finished, worker, &QObject::deleteLater);
        QObject::connect(thread, &QThread::finished, thread, &QObject::deleteLater);

        thread->start();
    };

    auto startSeriesMonitoringInThread = [&](void (MonitorWorker::*monitorFunction)(QLineSeries*), QLineSeries* series) {
        QThread* thread = new QThread;
        MonitorWorker* worker = new MonitorWorker(cpuClass, ramClass, diskSpaceClass, staticData, readingMethods);
        worker->moveToThread(thread);

        QObject::connect(thread, &QThread::started, worker, [=]() { (worker->*monitorFunction)(series); });
        QObject::connect(thread, &QThread::finished, worker, &QObject::deleteLater);
        QObject::connect(thread, &QThread::finished, thread, &QObject::deleteLater);

        thread->start();
    };

    startLabelMonitoringInThread(&MonitorWorker::monitorProcesses, processLabel);
    startLabelMonitoringInThread(&MonitorWorker::monitorCycles, cyclesLabel);
    startSeriesMonitoringInThread(&MonitorWorker::monitorCPU, cpuSeries);
    startSeriesMonitoringInThread(&MonitorWorker::monitorRAM, ramSeries);
    startSeriesMonitoringInThread(&MonitorWorker::monitorDiskSpace, diskSeries);

    return a.exec();
}
