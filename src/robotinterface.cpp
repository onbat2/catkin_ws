#include "robotinterface.h"
#include "ui_robotinterface.h"

RobotInterface::RobotInterface(int argc, char **argv, QWidget *parent)
  :QMainWindow(parent)
  ,ui(new Ui::RobotInterface)
  ,m_qnode(argc, argv)
{
  ui->setupUi(this);

  ui->location_A->setStyleSheet("background-image: url(:/image/data/images/nocolor_button.png)");


  // read configuration file
  readSettings();
  initUis();

  // Setting signal and slot
  connections();
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

void RobotInterface::showNoMasterMessage()
{
  QMessageBox msgBox;
  msgBox.setText("Couldn't find the ros master.");
  msgBox.exec();
  close();
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

//  m_qgraphicsScene->addItem(m_roboItem);

  ui->mapViz->setScene(m_qgraphicsScene);

  //need more ?
}

bool RobotInterface::connectMaster(QString master_ip, QString ros_ip)
{
  CONSOLE << "Connect ?";

  if (!m_qnode.init(master_ip.toStdString(), ros_ip.toStdString())) {
    return false;
    } else {
    readSettings();
    return true;
  }
}

void RobotInterface::slot_batteryState(sensor_msgs::BatteryState msg)
{
  ui->label_power->setText(QString::number(msg.voltage).mid(0, 5) + "V");
  double percentage = msg.percentage;
  ui->progressBar->setValue(percentage > 100 ? 100 : percentage);

  if (percentage <= 20) {
    ui->progressBar->setStyleSheet(
          "QProgressBar::chunk {background-color: red;width: 20px;} QProgressBar "
          "{border: 2px solid grey;border-radius: 5px;text-align: center;}");
  }
  else {
    ui->progressBar->setStyleSheet(
          "QProgressBar {border: 2px solid grey;border-radius: 5px;text-align: "
          "center;}");
  }
}

void RobotInterface::slot_rosShutdown()
{
  slot_updateRobotStatus(AppEnums::QRobotStatus::None);
}

void RobotInterface::slot_cmd_control()
{
  QPushButton *btn = qobject_cast<QPushButton *>(sender());
  char key = btn->text().toStdString()[0];
  QString button_key = btn->objectName();

  float liner = ui->horizontalSlider_linear->value() * 0.01;
  float turn = ui->horizontalSlider_turn->value() * 0.01;
  bool is_all = false;

  CONSOLE << "Key: " << key;
  CONSOLE << "Name: " << button_key;

  CONSOLE << "nice";

  if(button_key == "forward"){
    // forward
    m_qnode.move_base(is_all ? 'I' : 'i', liner, turn);
    CONSOLE << "my forward: " << liner;
  } else if(button_key == "back"){
    // backward
    m_qnode.move_base(is_all ? '<' : ',', liner, turn);
    CONSOLE << "my backward: " << liner;
  } else if (button_key == "r_left") {
    // rotate left
    m_qnode.move_base(is_all ? 'J' : 'j', liner, turn);
    CONSOLE << "left_value: ";
  } else if (button_key == "r_right") {
    // rotate right
    m_qnode.move_base(is_all ? 'L' : 'l', liner, turn);
    CONSOLE << "right_value: ";
  } else {
    // stop
    m_qnode.move_base(is_all ? 'K' : 'k', liner, turn);
  }
}

void RobotInterface::slot_buttonChangeColorA()
{
//  ui->location_A->setStyleSheet("background-color: red");
}

void RobotInterface::slot_buttonChangeColorB()
{
  ui->location_B->setStyleSheet("background-color: yellow");
}

void RobotInterface::slot_buttonChangeColorC()
{
  ui->location_C->setStyleSheet("background-color: blue");
}

void RobotInterface::slot_dis_connect()
{
  ros::shutdown();
  slot_rosShutdown();
  emit signalDisconnect();
  this->close();
}

void RobotInterface::slot_updateRobotStatus(AppEnums::QRobotStatus status)
{
  switch (status) {
  case AppEnums::QRobotStatus::None: {
    QTimer::singleShot(100, [this]() {
      ui->pushButton_status->setIcon(
            QIcon(":/image/data/images/status/status_none.png"));
      m_roboItem->setRobotColor(AppEnums::QRobotColor::Blue);
    });
  } break;
  case AppEnums::QRobotStatus::Normal: {
    QTimer::singleShot(200, [this]() {
      ui->pushButton_status->setIcon(
            QIcon(":/image/data/images/status/status_normal.png"));
      m_roboItem->setRobotColor(AppEnums::QRobotColor::Blue);
    });
  } break;
  case AppEnums::QRobotStatus::Error: {
    QTimer::singleShot(300, [this]() {
      ui->pushButton_status->setIcon(
            QIcon(":/image/data/images/status/status_error.png"));
      m_roboItem->setRobotColor(AppEnums::QRobotColor::Red);
    });
  } break;
  case AppEnums::QRobotStatus::Warning: {
    QTimer::singleShot(400, [this]() {
      ui->pushButton_status->setIcon(
            QIcon(":/image/data/images/status/status_warn.png"));
      m_roboItem->setRobotColor(AppEnums::QRobotColor::Yellow);
    });
  } break;
  }
}

void RobotInterface::connections()
{
  connect(&m_qnode, &QNode::rosShutdown, this, &RobotInterface::slot_rosShutdown);
  connect(&m_qnode, &QNode::Master_shutdown, this, &RobotInterface::slot_rosShutdown);

  connect(m_timerCurrentTime, &QTimer::timeout, [=]() {
    ui->label_time->setText(
          QDateTime::currentDateTime().toString("  hh:mm:ss  "));
  });

  // Robot status
  connect(&m_qnode, &QNode::updateRobotStatus, this, &RobotInterface::slot_updateRobotStatus);

  // Robot battery
  connect(&m_qnode, &QNode::batteryState, this, &RobotInterface::slot_batteryState);

  // Bind the speed control buttons
  connect(ui->back, SIGNAL(clicked()), this, SLOT(slot_cmd_control()));
  connect(ui->r_left, SIGNAL(clicked()), this, SLOT(slot_cmd_control()));
  connect(ui->stop, SIGNAL(clicked()), this, SLOT(slot_cmd_control()));
  connect(ui->forward, SIGNAL(clicked()), this, SLOT(slot_cmd_control()));
  connect(ui->r_right, SIGNAL(clicked()), this, SLOT(slot_cmd_control()));

  connect(ui->location_A, SIGNAL(clicked()), this, SLOT(slot_buttonChangeColorA()));
  connect(ui->location_B, SIGNAL(clicked()), this, SLOT(slot_buttonChangeColorB()));
  connect(ui->location_C, SIGNAL(clicked()), this, SLOT(slot_buttonChangeColorC()));
}

void RobotInterface::display_rviz()
{
  QSettings settings("junbot_gui", "Displays");
  bool Grid_enable = settings.value("Grid/enable", bool(true)).toBool();
  double Grid_count = settings.value("Grid/count", double(20)).toDouble();

  bool Map_enable = settings.value("Map/enable", bool(true)).toBool();
  QString Map_topic = settings.value("Map/topic", QString("/map")).toString();
  double Map_alpha = settings.value("Map/alpha", double(0.7)).toDouble();
  QString Map_scheme = settings.value("Map/scheme", QString("map")).toString();
  bool Laser_enable = settings.value("Laser/enable", bool(true)).toBool();
  QString Laser_topic =
      settings.value("Laser/topic", QString("/scan")).toString();
  bool Polygon_enable = settings.value("Polygon/enable", bool(true)).toBool();
  QString Polygon_topic =
      settings
      .value("Polygon/topic", QString("/move_base/local_costmap/footprint"))
      .toString();

  bool RobotModel_enable =
      settings.value("RobotModel/enable", bool(true)).toBool();
  bool Navigation_enable =
      settings.value("Navigation/enable", bool(true)).toBool();
  QString GlobalMap_topic =
      settings
      .value("Navigation/GlobalMap/topic",
             QString("/move_base/global_costmap/costmap"))
      .toString();
  QString GlobalMap_paln = settings
      .value("Navigation/GlobalPlan/topic",
             QString("/move_base/NavfnROS/plan"))
      .toString();
  QString LocalMap_topic =
      settings
      .value("Navigation/LocalMap/topic",
             QString("/move_base/local_costmap/costmap"))
      .toString();
  QString LocalMap_plan =
      settings
      .value("Navigation/LocalPlan/topic",
             QString("/move_base/DWAPlannerROS/local_plan"))
      .toString();
}

