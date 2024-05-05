/** ICP Project 2023/2024
 * @file robot_info.cpp
 * @author Tomáš Daniel (xdanie14)
 * @brief Widget displaying selected robot editable details to the user.
 */

#include "robot_info.h"

Robot_Info* Robot_Info::instance = nullptr;

Robot_Info::Robot_Info (QGraphicsScene* scene, QWidget* window)
    : QWidget     (window),
      scene       (scene),
      main_window (window),
      robot       (nullptr),
      visible     (false)
{
    // Create container widget to hold all user menu items
    info_container = new QWidget();
    // Create a layout for the widget
    QVBoxLayout* info_layout = new QVBoxLayout(info_container);

    // Robot type
    QLabel* typeLabel = new QLabel("Robot type:");
    typeComboBox = new QComboBox();
    typeComboBox->addItems({"Manual", "Automatic"});

    // Create a group for grouping all automatic controls of robot
    auto_mode_items = new QGroupBox();
    auto_mode_items->setTitle("Automatic Controls");
    // Create separate layout for adding the items
    QVBoxLayout* auto_items_layout = new QVBoxLayout(auto_mode_items);

    // Collision threshold
    QLabel* collisionLabel = new QLabel("Collision threshold:");
    collisionLineEdit = new QLineEdit(main_window);
    auto_items_layout->addWidget(collisionLabel);
    auto_items_layout->addWidget(collisionLineEdit);

    // Rotation angle
    QLabel* rotationLabel = new QLabel("Rotation angle:");
    rotationLineEdit = new QLineEdit(main_window);

    // Rotation direction
    QLabel* directionLabel = new QLabel("Rotation direction:");
    directionComboBox = new QComboBox();
    directionComboBox->addItems({"Clockwise", "Counter-clockwise"});
    auto_items_layout->addWidget(directionLabel);
    auto_items_layout->addWidget(directionComboBox);

    // Add the buttons layout to the group box
    auto_mode_items->setLayout(auto_items_layout);

    QPushButton* okButton = new QPushButton("OK");

    // Add all items to widget
    info_layout->addWidget(typeLabel);
    info_layout->addWidget(typeComboBox);
    info_layout->addWidget(rotationLabel);
    info_layout->addWidget(rotationLineEdit);
    info_layout->addWidget(auto_mode_items);
    info_layout->addWidget(okButton);

    info_container->setLayout(info_layout);

    // Set the position of the container widget below menu button
    proxy = scene->addWidget(info_container);

    // Set hidden intially
    info_container->setVisible(visible);

    // Connect item event actions
    connect(okButton, &QPushButton::clicked, this, &Robot_Info::ok_click);
    connect(typeComboBox, SIGNAL(activated(int)), this, SLOT(robot_type(int)));
    connect(collisionLineEdit, &QLineEdit::textChanged, this, &Robot_Info::collision_value);
    connect(rotationLineEdit, &QLineEdit::textChanged, this, &Robot_Info::rotation_value);
    connect(directionComboBox, SIGNAL(activated(int)), this, SLOT(rotation_direction(int)));

    // Set static variable representing current instance of this class
    if (Robot_Info::instance != nullptr) {
        // Instance already exists, so delete it and replace it with this new one
        delete Robot_Info::instance;
    }
    Robot_Info::instance = this;
}

Robot_Info::~Robot_Info() {
    delete proxy;
}

void Robot_Info::show_widget (Robot* cur_robot) {
    Robot_Info* cur_instance = Robot_Info::instance;
    // If already shown, hide it
    if (cur_instance->visible) {
        cur_instance->visible = false;
        cur_instance->info_container->setVisible(false);
    }
    // Update class robot property
    cur_instance->robot = cur_robot;
    // Load robot info
    cur_instance->process_robot_info();

    // Calculate new position of popup to ensure it fits inside window
    QPointF new_pos(
        cur_instance->main_window->rect().topRight().x() - 200,
        cur_instance->main_window->rect().topRight().y() - 5
    );
    // Apply calculated position
    cur_instance->proxy->setPos(new_pos);

    // Show the widget
    cur_instance->visible = true;
    cur_instance->info_container->setVisible(true);
}

void Robot_Info::hide_related_widget (class Robot* cur_robot) {
    // If given robot widget is shown, hide it
    Robot_Info* cur_instance = Robot_Info::instance;
    if (cur_instance->robot == cur_robot) {
        // Hide the widget
        cur_instance->info_container->setVisible(false);
        cur_instance->visible = false;
    }
}

void Robot_Info::process_robot_info () {
    // Load values vector from robot
    QVector<QString> info_from_robot = robot->get_robot_info();
    // Update widget items with given info from robot
    typeComboBox->setCurrentIndex(info_from_robot.at(0).toInt());
    collisionLineEdit->setText(info_from_robot.at(1));
    rotationLineEdit->setText(info_from_robot.at(2));
    directionComboBox->setCurrentIndex(info_from_robot.at(3).toInt());
    // Set visible items based of robot current mode
    update_visible_items(typeComboBox->currentIndex());
}

void Robot_Info::update_visible_items (int mode) {
    if (mode == MANUAL) {
        auto_mode_items->hide();
    }
    else { // Automatic
        auto_mode_items->show();
    }
    Robot_Info::instance->info_container->adjustSize();
}

void Robot_Info::ok_click () {
    // Hide the widget
    Robot_Info::instance->info_container->setVisible(false);
    Robot_Info::instance->visible = false;
}

void Robot_Info::robot_type (int index) {
    // Update robot mode
    robot->set_mode((enum Mode)index);
    // set visible items base of robot current mode
    update_visible_items(index);
}

void Robot_Info::collision_value (const QString& text) {
    if (text.isEmpty()) {
        return;
    }
    bool ok;
    double new_threshold = text.trimmed().toDouble(&ok);
    if (ok == false) {
        new_threshold = robot->get_rotation_step();
    }
    collisionLineEdit->setText(QString::number(new_threshold));
    robot->set_detect_threshold(new_threshold);
}

void Robot_Info::rotation_value (const QString& text) {
    if (text.isEmpty()) {
        return;
    }
    bool ok;
    double new_rotation = text.trimmed().toDouble(&ok);
    if (ok == false) {
        new_rotation = robot->get_rotation_step();
    }
    rotationLineEdit->setText(QString::number(new_rotation));
    robot->set_rotation_step(new_rotation);
}

void Robot_Info::rotation_direction (int index) {
    // Update robot rotation angle direction
    robot->set_rotation_direction((enum Direction)index);
}

void Robot_Info::clean_up () {
    delete Robot_Info::instance;
    Robot_Info::instance = nullptr;
}
