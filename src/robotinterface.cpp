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

  //need more ?
}

//// Video topic init
//void RobotInterface::initVideos()
//{
//  QSettings video_topic_setting("junbot_gui", "settings");
//  QStringList names = video_topic_setting.value("video/names").toStringList();
//  QStringList topics = video_topic_setting.value("video/topics").toStringList();
//  if (topics.size() == 4) {
//    if (topics[0] != "")
//    {
//      m_qnode.Sub_Image(topics[0], 0);
//    }
//    if (topics[1] != "")
//    {
//      m_qnode.Sub_Image(topics[1], 1);
//    }
//    if (topics[2] != "")
//    {
//      m_qnode.Sub_Image(topics[2], 2);
//    }
//    if (topics[3] != "")
//    {
//      m_qnode.Sub_Image(topics[3], 3);
//    }
//  }

//  connect(&m_qnode, &QNode::Show_image, this,
//          &MainWindow::slot_show_image);
//}

//// Read and display topic list
//void RobotInterface::initTopicList()
//{
//  ui->topic_listWidget->clear();
//  ui->topic_listWidget->addItem(QString("%1   (%2)").arg("Name", "Type"));
//  QMap<QString, QString> topic_list = m_qnode.get_topic_list();
//  for (QMap<QString, QString>::iterator iter = topic_list.begin();
//       iter != topic_list.end(); iter++) {
//    ui->topic_listWidget->addItem(
//          QString("%1   (%2)").arg(iter.key(), iter.value()));
//  }
//}

// Other setting
void RobotInterface::initOthers()
{
  m_timerChart = new QTimer;
  m_timerPubImageMap = new QTimer;
  m_timerPubImageMap->setInterval(100);
  m_timerChart->setInterval(100);

  connect(m_timerPubImageMap, SIGNAL(timeout()), this,
          SLOT(slot_pubImageMapTimeOut()));

  m_timerPubImageMap->start();
  m_timerChart->start();
}

bool RobotInterface::connectMaster(QString master_ip, QString ros_ip, bool use_envirment)
{
  if (use_envirment) {
    if (!m_qnode.init()) {
      return false;
    } else {
//      initVideos();
//      initTopicList();
      initOthers();
    }
  }
  else {
    if (!m_qnode.init(master_ip.toStdString(), ros_ip.toStdString())) {
      return false;
    } else {
//      initVideos();
//      initTopicList();
      initOthers();
    }
  }
  readSettings();
  return true;
}

void RobotInterface::slot_batteryState(sensor_msgs::BatteryState)
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

void RobotInterface::slot_cmd_control()
{
  QPushButton *btn = qobject_cast<QPushButton *>(sender());
  char key = btn->text().toStdString()[0];
  QString button_key = btn->objectName();

  float liner = ui->horizontalSlider_linear->value() * 0.01;
  float turn = ui->horizontalSlider_raw->value() * 0.01;
  bool is_all = false;

  CONSOLE << "Key: " << key;
  CONSOLE << "Name: " << button_key;

  if(button_key == "forward"){
    // forward
    m_qnode.move_base(is_all ? 'I' : 'i', liner, turn);
  } else if(button_key == "back"){
    // backward
    m_qnode.move_base(is_all ? '<' : ',', liner, turn);
  } else if (button_key == "r_left") {
    // rotate left
    m_qnode.move_base(is_all ? 'J' : 'j', liner, turn);
  } else if (button_key == "r_right") {
    // rotate right
    m_qnode.move_base(is_all ? 'L' : 'l', liner, turn);
  } else {
    // stop
    m_qnode.move_base(is_all ? 'K' : 'k', liner, turn);
  }
}

void RobotInterface::mousePressEvent(QMouseEvent *event)
{
  m_lastPos = event->globalPos();
  isPressedWidget = true;
}

void RobotInterface::mouseMoveEvent(QMouseEvent *event)
{
  if (isPressedWidget) {
    this->move(this->x() + (event->globalX() - m_lastPos.x()),
               this->y() + (event->globalY() - m_lastPos.y()));
    m_lastPos = event->globalPos();
  }
}

void RobotInterface::mouseReleaseEvent(QMouseEvent *event)
{
  m_lastPos = event->globalPos();
  isPressedWidget = false;
}

void RobotInterface::connections()
{
  connect(&m_qnode, &QNode::loggingUpdated, this, &RobotInterface::updateLoggingView);
//  connect(&m_qnode, &QNode::rosShutdown, this, &RobotInterface::slot_rosShutdown);
//  connect(&m_qnode, &QNode::Master_shutdown, this, &RobotInterface::slot_rosShutdown);

  // Main display screen

//  // Control screen
//  connect(ui->btn_control, &QPushButton::clicked, [=]() {
//    ui->stackedWidget_left->setCurrentIndex(1);
//    setCurrentMenu(ui->btn_control);
//  });

//  // Status screen
//  connect(ui->btn_status, &QPushButton::clicked, [=]() {
//    ui->stackedWidget_left->setCurrentIndex(0);
//    setCurrentMenu(ui->btn_status);
//  });

//  // Map screen
//  connect(ui->btn_map, &QPushButton::clicked, [=]() {
//    ui->stackedWidget_main->setCurrentIndex(0);
//    setCurrentMenu(ui->btn_map);
//  });

//  // Other screen
//  connect(ui->btn_other, &QPushButton::clicked, [=]() {
//    ui->stackedWidget_main->setCurrentIndex(1);
//    setCurrentMenu(ui->btn_other);
//  });

//  connect(ui->pushButton_status, &QPushButton::clicked, [=]() {
//    ui->btn_other->click();
//  });

  connect(m_timerCurrentTime, &QTimer::timeout, [=]() {
    ui->label_time->setText(
          QDateTime::currentDateTime().toString("  hh:mm:ss  "));
  });

//  // Robot status
//  connect(&m_qnode, &QNode::updateRobotStatus, this, &RobotInterface::slot_updateRobotStatus);

//  // Robot battery
//  connect(&m_qnode, &QNode::batteryState, this, &RobotInterface::slot_batteryState);

//  // Function to bind slider
//  connect(ui->horizontalSlider_raw, SIGNAL(valueChanged(int)), this,
//          SLOT(Slider_raw_valueChanged(int)));
//  connect(ui->horizontalSlider_linear, SIGNAL(valueChanged(int)), this,
//          SLOT(Slider_linear_valueChanged(int)));

//  // Set interface
//  connect(ui->settings_btn, SIGNAL(clicked()), this, SLOT(slot_setting_frame()));

  // Bind the speed control buttons
  connect(ui->back, SIGNAL(clicked()), this, SLOT(slot_cmd_control()));
  connect(ui->r_left, SIGNAL(clicked()), this, SLOT(slot_cmd_control()));
  connect(ui->stop, SIGNAL(clicked()), this, SLOT(slot_cmd_control()));
  connect(ui->forward, SIGNAL(clicked()), this, SLOT(slot_cmd_control()));
  connect(ui->r_right, SIGNAL(clicked()), this, SLOT(slot_cmd_control()));


//  connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slot_dis_connect()));
//  connect(ui->set_pos_btn, SIGNAL(clicked()), this, SLOT(slot_set_2D_Pos()));
//  connect(ui->set_goal_btn, SIGNAL(clicked()), this, SLOT(slot_set_2D_Goal()));

//  // return flight
//  connect(ui->return_btn, SIGNAL(clicked()), this, SLOT(slot_return_point()));

//  // refresh thread list
//  connect(ui->refresh_topic_btn, SIGNAL(clicked()), this,
//          SLOT(refreshTopicList()));

//  connect(ui->close_btn, SIGNAL(clicked()), this, SLOT(slot_closeWindows()));
//  connect(ui->min_btn, SIGNAL(clicked()), this, SLOT(slot_minWindows()));
//  connect(ui->max_btn, SIGNAL(clicked()), this, SLOT(slot_maxWindows()));

//  // Map and Path display
//  connect(&m_qnode, SIGNAL(updateMap(QImage)), m_roboItem,
//          SLOT(paintMaps(QImage)));
//  connect(&m_qnode, SIGNAL(plannerPath(QPolygonF)), m_roboItem,
//          SLOT(paintPlannerPath(QPolygonF)));
//  connect(&m_qnode, SIGNAL(updateRoboPose(QRobotPose)), m_roboItem,
//          SLOT(paintRoboPos(QRobotPose)));
//  connect(&m_qnode, SIGNAL(updateLaserScan(QPolygonF)), m_roboItem,
//          SLOT(paintLaserScan(QPolygonF)));
//  connect(m_roboItem, SIGNAL(cursorPos(QPointF)), this,
//          SLOT(slot_updateCursorPos(QPointF)));

//  // map
//  connect(m_roboItem, SIGNAL(signalPub2DPos(QRobotPose)), &m_qnode,
//          SLOT(slot_pub2DPos(QRobotPose)));
//  connect(m_roboItem, SIGNAL(signalPub2DGoal(QRobotPose)), &m_qnode,
//          SLOT(slot_pub2DGoal(QRobotPose)));
//  connect(this, SIGNAL(signalSet2DPose()), m_roboItem, SLOT(slot_set2DPos()));
//  connect(this, SIGNAL(signalSet2DGoal()), m_roboItem, SLOT(slot_set2DGoal()));
//  connect(this, SIGNAL(signalSetMoveCamera()), m_roboItem,
//          SLOT(slot_setMoveCamera()));
//  //    connect(ui.stackedWidget_2,SIGNAL())
}

