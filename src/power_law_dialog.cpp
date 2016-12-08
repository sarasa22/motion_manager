#include "../include/motion_manager/power_law_dialog.hpp"

namespace motion_manager {

powerLawDialog::powerLawDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::powerLawDialog)
{
    ui->setupUi(this);
}

powerLawDialog::~powerLawDialog()
{
    delete ui;
}


void powerLawDialog::setupPlots(vector<MatrixXd> &pos, vector<MatrixXd> &vel, vector<MatrixXd> &acc, vector<vector<double> > &timesteps)
{
    const double radtodeg = 180.0/static_cast<double>(M_PI);

    vector<double> time;
    QVector<double> pos_joint1, vel_joint1, acc_joint1;
    QVector<double> pos_joint2, vel_joint2, acc_joint2;
    QVector<double> pos_joint3, vel_joint3, acc_joint3;
    QVector<double> pos_joint4, vel_joint4, acc_joint4;
    QVector<double> pos_joint5, vel_joint5, acc_joint5;
    QVector<double> pos_joint6, vel_joint6, acc_joint6;
    QVector<double> pos_joint7, vel_joint7, acc_joint7;
    QVector<double> pos_joint8, vel_joint8, acc_joint8;
    QVector<double> pos_joint9, vel_joint9, acc_joint9;
    QVector<double> pos_joint10, vel_joint10, acc_joint10;
    QVector<double> pos_joint11, vel_joint11, acc_joint11;

    for(size_t i=0; i<pos.size();++i){
        MatrixXd pos_stage = pos.at(i);
        MatrixXd vel_stage = vel.at(i);
        MatrixXd acc_stage = acc.at(i);
        vector<double> tsteps_stage = timesteps.at(i);
        double time_init;
        if(time.empty()){
            time_init=0.0;
        }else{
            time_init=time.at(time.size()-1);
        }
        vector<double> time_stage(tsteps_stage.size());
        time_stage.at(0) = time_init;

        for(int k=0;k<pos_stage.rows();++k){
            if(k>0){time_stage.at(k) = time_stage.at(k-1) + tsteps_stage.at(k-1);}
            for(int j=0;j<pos_stage.cols();++j){
                switch(j){
                case 0:// joint 1
                    pos_joint1.push_back(radtodeg*pos_stage(k,j));
                    vel_joint1.push_back(radtodeg*vel_stage(k,j));
                    acc_joint1.push_back(radtodeg*acc_stage(k,j));
                    break;
                case 1://joint 2
                    pos_joint2.push_back(radtodeg*pos_stage(k,j));
                    vel_joint2.push_back(radtodeg*vel_stage(k,j));
                    acc_joint2.push_back(radtodeg*acc_stage(k,j));
                    break;
                case 2://joint 3
                    pos_joint3.push_back(radtodeg*pos_stage(k,j));
                    vel_joint3.push_back(radtodeg*vel_stage(k,j));
                    acc_joint3.push_back(radtodeg*acc_stage(k,j));
                    break;
                case 3://joint 4
                    pos_joint4.push_back(radtodeg*pos_stage(k,j));
                    vel_joint4.push_back(radtodeg*vel_stage(k,j));
                    acc_joint4.push_back(radtodeg*acc_stage(k,j));
                    break;
                case 4://joint 5
                    pos_joint5.push_back(radtodeg*pos_stage(k,j));
                    vel_joint5.push_back(radtodeg*vel_stage(k,j));
                    acc_joint5.push_back(radtodeg*acc_stage(k,j));
                    break;
                case 5://joint 6
                    pos_joint6.push_back(radtodeg*pos_stage(k,j));
                    vel_joint6.push_back(radtodeg*vel_stage(k,j));
                    acc_joint6.push_back(radtodeg*acc_stage(k,j));
                    break;
                case 6://joint 7
                    pos_joint7.push_back(radtodeg*pos_stage(k,j));
                    vel_joint7.push_back(radtodeg*vel_stage(k,j));
                    acc_joint7.push_back(radtodeg*acc_stage(k,j));
                    break;
                case 7://joint 8
                    pos_joint8.push_back(radtodeg*pos_stage(k,j));
                    vel_joint8.push_back(radtodeg*vel_stage(k,j));
                    acc_joint8.push_back(radtodeg*acc_stage(k,j));
                    break;
                case 8://joint 9
                    pos_joint9.push_back(radtodeg*pos_stage(k,j));
                    vel_joint9.push_back(radtodeg*vel_stage(k,j));
                    acc_joint9.push_back(radtodeg*acc_stage(k,j));
                    break;
                case 9://joint 10
                    pos_joint10.push_back(radtodeg*pos_stage(k,j));
                    vel_joint10.push_back(radtodeg*vel_stage(k,j));
                    acc_joint10.push_back(radtodeg*acc_stage(k,j));
                    break;
                case 10://joint 11
                    pos_joint11.push_back(radtodeg*pos_stage(k,j));
                    vel_joint11.push_back(radtodeg*vel_stage(k,j));
                    acc_joint11.push_back(radtodeg*acc_stage(k,j));
                    break;
                }
            }
        }
        time.reserve(time_stage.size());
        std::copy (time_stage.begin(), time_stage.end(), std::back_inserter(time));
    }
    QVector<double> qtime = QVector<double>::fromStdVector(time);



}

void powerLawDialog::plotJoint(QCustomPlot *plot, QString title, QVector<double> &time, QVector<double> &pos, QVector<double> &vel, QVector<double> &acc)
{
    plot->plotLayout()->clear();
    plot->clearGraphs();
    plot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom)); // period as decimal separator and comma as thousand separator
    QCPAxisRect *wideAxisRect = new QCPAxisRect(plot);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor(Qt::red));
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor(Qt::darkGreen));
    QCPMarginGroup *marginGroup = new QCPMarginGroup(plot);
    wideAxisRect->setMarginGroup(QCP::msLeft | QCP::msRight, marginGroup);
    // move newly created axes on "axes" layer and grids on "grid" layer:
    for (QCPAxisRect *rect : plot->axisRects())
    {
      for (QCPAxis *axis : rect->axes())
      {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
      }
    }

    plot->plotLayout()->addElement(0,0, new QCPPlotTitle(plot,title));
    plot->plotLayout()->addElement(1, 0, wideAxisRect);

    // position
    plot->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft));
    plot->graph(0)->setPen(QPen(Qt::blue));
    plot->graph(0)->setName("[deg]");
    plot->graph(0)->valueAxis()->setTickLabelColor(Qt::blue);
    plot->graph(0)->keyAxis()->setLabel("time [s]");
    plot->graph(0)->setData(time, pos);
    plot->graph(0)->valueAxis()->setRange(*std::min_element(pos.begin(), pos.end()),
                                                      *std::max_element(pos.begin(), pos.end()));
    plot->graph(0)->rescaleAxes();

    // velocity
    plot->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft,1));
    plot->graph(1)->setPen(QPen(Qt::red));
    plot->graph(1)->setName("[deg/s]");
    plot->graph(1)->valueAxis()->setTickLabelColor(Qt::red);
    plot->graph(1)->keyAxis()->setLabel("time [s]");
    plot->graph(1)->setData(time, vel);
    plot->graph(1)->valueAxis()->setRange(*std::min_element(vel.begin(), vel.end()),
                                                      *std::max_element(vel.begin(), vel.end()));
    plot->graph(1)->rescaleAxes();

    // acceleration
    plot->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft,2));
    plot->graph(2)->setPen(QPen(Qt::darkGreen));
    plot->graph(2)->setName("[deg/s^2]");
    plot->graph(2)->valueAxis()->setTickLabelColor(Qt::darkGreen);
    plot->graph(2)->keyAxis()->setLabel("time [s]");
    plot->graph(2)->setData(time, acc);
    plot->graph(2)->valueAxis()->setRange(*std::min_element(acc.begin(), acc.end()),
                                                      *std::max_element(acc.begin(), acc.end()));
    plot->graph(2)->rescaleAxes();

    // legend
    QCPLegend *legend = new QCPLegend();
    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    plot->plotLayout()->addElement(2, 0, subLayout);
    subLayout->setMargins(QMargins(5, 0, 5, 5));
    subLayout->addElement(0, 0, legend);
    // set legend's row stretch factor very small so it ends up with minimum height:
    plot->plotLayout()->setRowStretchFactor(2, 0.001);
    legend->setLayer("legend");
    QFont legendFont = font();  // start out with MainWindow's font..
    legendFont.setPointSize(9); // and make a bit smaller for legend
    legend->setFont(legendFont);
    legend->addElement(0,0,new QCPPlottableLegendItem(legend,plot->graph(0)));
    legend->addElement(0,1,new QCPPlottableLegendItem(legend,plot->graph(1)));
    legend->addElement(0,2,new QCPPlottableLegendItem(legend,plot->graph(2)));

    // interactions
    connect(plot->graph(0)->valueAxis(), SIGNAL(rangeChanged(QCPRange)), plot->graph(1)->valueAxis(), SLOT(setRange(QCPRange)));
    connect(plot->graph(0)->valueAxis(), SIGNAL(rangeChanged(QCPRange)), plot->graph(2)->valueAxis(), SLOT(setRange(QCPRange)));
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);


    plot->replot();
}




} // namespace motion_manager
