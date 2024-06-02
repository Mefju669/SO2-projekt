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
#include "MonitorWorker.h"
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Create the main window for the system monitor
    QWidget window;
    window.setWindowTitle("System Monitor");
    window.setGeometry(100, 100, 750, 550);
    window.setStyleSheet("background-color: white;");

    // Main layout to hold all widgets
    QVBoxLayout *mainLayout = new QVBoxLayout(&window);
    QHBoxLayout *centerLayout = new QHBoxLayout();

    // Create RAM label
    QLabel *ramLabel = new QLabel(&window);
    ramLabel->setStyleSheet("color: red;");
    centerLayout->addWidget(ramLabel);

    // Create Disk label
    QLabel *diskLabel = new QLabel(&window);
    diskLabel->setStyleSheet("color: green;");
    diskLabel->setContentsMargins(10, 0, 10, 0);
    centerLayout->addWidget(diskLabel);

    // Create chart to display CPU, RAM, and Disk utilization
    QChart *chart = new QChart();
    chart->setTitle("CPU, RAM & Disk Utilization Over Time");
    chart->createDefaultAxes();

    // Create and configure CPU series
    QLineSeries *cpuSeries = new QLineSeries();
    cpuSeries->setName("CPU Usage");
    cpuSeries->setColor(Qt::blue);
    chart->addSeries(cpuSeries);

    // Create and configure RAM series
    QLineSeries *ramSeries = new QLineSeries();
    ramSeries->setName("RAM Usage");
    ramSeries->setColor(Qt::red);
    chart->addSeries(ramSeries);

    // Create and configure Disk series
    QLineSeries *diskSeries = new QLineSeries();
    diskSeries->setName("Disk Usage");
    diskSeries->setColor(Qt::green);
    chart->addSeries(diskSeries);

    // Configure X axis for the chart
    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(0, 60);
    axisX->setLabelFormat("%d s");
    axisX->setTitleText("Time (s)");

    // Configure Y axis for the chart
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 100);
    axisY->setLabelFormat("%d%%");
    axisY->setTitleText("Usage (%)");

    // Set axes for each series
    chart->setAxisX(axisX);
    chart->setAxisY(axisY);
    chart->setAxisX(axisX, cpuSeries);
    chart->setAxisY(axisY, cpuSeries);
    chart->setAxisX(axisX, ramSeries);
    chart->setAxisY(axisY, ramSeries);
    chart->setAxisX(axisX, diskSeries);
    chart->setAxisY(axisY, diskSeries);

    // Create a chart view and add it to the center layout
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    centerLayout->addWidget(chartView);

    // Add the center layout to the main layout
    mainLayout->addLayout(centerLayout);

    // Create and configure process and cycles labels
    QLabel *processLabel = new QLabel(&window);
    processLabel->setStyleSheet("color: blue;");
    mainLayout->addWidget(processLabel);
    QLabel *cyclesLabel = new QLabel(&window);
    cyclesLabel->setStyleSheet("color: blue;");
    mainLayout->addWidget(cyclesLabel);

    processLabel->setAlignment(Qt::AlignCenter);
    cyclesLabel->setAlignment(Qt::AlignCenter);

    // Set main layout and show the window
    window.setLayout(mainLayout);
    window.show();

    // Create instances of necessary classes for monitoring
    ReadingMethods readingMethods;
    CPUClass cpuClass;
    RAMClass ramClass;
    DiskSpaceClass diskSpaceClass;
    StaticData staticData;

    // Helper function to start label monitoring in a separate thread
    auto startLabelMonitoringInThread = [&](void (MonitorWorker::*monitorFunction)(QLabel*), QLabel* label) {
        QThread* thread = new QThread;
        MonitorWorker* worker = new MonitorWorker(cpuClass, ramClass, diskSpaceClass, staticData, readingMethods);
        worker->moveToThread(thread);

        QObject::connect(thread, &QThread::started, worker, [=]() { (worker->*monitorFunction)(label); });
        QObject::connect(thread, &QThread::finished, worker, &QObject::deleteLater);
        QObject::connect(thread, &QThread::finished, thread, &QObject::deleteLater);

        thread->start();
    };

    // Helper function to start series monitoring in a separate thread
    auto startSeriesMonitoringInThread = [&](void (MonitorWorker::*monitorFunction)(QLineSeries*), QLineSeries* series) {
        QThread* thread = new QThread;
        MonitorWorker* worker = new MonitorWorker(cpuClass, ramClass, diskSpaceClass, staticData, readingMethods);
        worker->moveToThread(thread);

        QObject::connect(thread, &QThread::started, worker, [=]() { (worker->*monitorFunction)(series); });
        QObject::connect(thread, &QThread::finished, worker, &QObject::deleteLater);
        QObject::connect(thread, &QThread::finished, thread, &QObject::deleteLater);

        thread->start();
    };

    // Start monitoring processes, cycles, and utilization in separate threads
    startLabelMonitoringInThread(&MonitorWorker::monitorProcesses, processLabel);
    startLabelMonitoringInThread(&MonitorWorker::monitorCycles, cyclesLabel);
    startSeriesMonitoringInThread(&MonitorWorker::monitorCPU, cpuSeries);
    startSeriesMonitoringInThread(&MonitorWorker::monitorRAM, ramSeries);
    startSeriesMonitoringInThread(&MonitorWorker::monitorDiskSpace, diskSeries);

    return a.exec();
}
