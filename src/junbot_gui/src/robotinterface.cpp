#include "robotinterface.h"
#include "ui_robotinterface.h"

RobotInterface::RobotInterface(int argc, char **argv, QWidget *parent)
  :QMainWindow(parent)
  ,ui(new Ui::RobotInterface)
  ,m_qnode(argc, argv)
{
  ui->setupUi(this);

  // read configuration file
  readSettings();
//  initUis();

//  ui->view_logging->setModel(m_qnode.loggingModel());

  // Setting signal and slot
//  connections();
}

RobotInterface::~RobotInterface()
{
  delete ui;
}

void RobotInterface::readSettings()
{
  QSettings settings("junbot_gui", "settings");
  restoreGeometry(settings.value("geometry").toByteArray());
  restoreState(settings.value("windowState").toByteArray());
  m_masterUrl =
      settings.value("connect/master_url", QString("http://192.168.1.2:11311/"))
          .toString();
  m_hostUrl =
      settings.value("connect/host_url", QString("192.168.1.3")).toString();
  m_useEnviorment =
      settings.value("connect/use_enviorment", bool(false)).toBool();
  m_autoConnect = settings.value("connect/auto_connect", bool(false)).toBool();
  m_turnLightThre =
      settings.value("connect/lineEdit_turnLightThre", double(0.1)).toDouble();
  if (settings.value("main/show_mode", "control").toString() == "control") {
    m_showMode = AppEnums::QDisplayMode::Control;
  } else {
    m_showMode = AppEnums::QDisplayMode::Robot;
  }
}

void RobotInterface::writeSettings()
{
  QSettings windows_setting("junbot_gui", "windows");
  windows_setting.clear();
  windows_setting.setValue("WindowGeometry/x", this->x());
  windows_setting.setValue("WindowGeometry/y", this->y());
  windows_setting.setValue("WindowGeometry/width", this->width());
  windows_setting.setValue("WindowGeometry/height", this->height());
}

void RobotInterface::closeEvent(QCloseEvent *event)
{
  writeSettings();
  QMainWindow::closeEvent(event);
}

void RobotInterface::initUis()
{
  // Time dynamic display
  m_timerCurrentTime = new QTimer;
  m_timerCurrentTime->setInterval(100);
  m_timerCurrentTime->start();
  // ui.centralwidget->hide();

  // view scene loading
  m_qgraphicsScene = new QGraphicsScene();

  m_qgraphicsScene->clear();

  m_roboItem = new QRobotItem();

  m_qgraphicsScene->addItem(m_roboItem);

  ui->mapView->setScene(m_qgraphicsScene);
}
