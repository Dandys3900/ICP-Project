/** ICP Project 2023/2024
 * @file robot_info.cpp
 * @author Tomáš Daniel (xdanie14)
 * @brief Widget displaying selected robot editable details to the user.
 */

#include "robot_info.h"

Robot_Info* Robot_Info::instance = nullptr;

Robot_Info::Robot_Info (QGraphicsScene* scene, QWidget* window)
    : QWidget        (window),
      mp_scene       (scene),
      mp_main_window (window),
      mp_robot       (nullptr),
      mp_visible     (false)
{
    // Create container widget to hold all user menu items
    mp_info_container = new QWidget();
    // Create a layout for the widget
    QVBoxLayout* info_layout = new QVBoxLayout(mp_info_container);

    // Robot type
    QLabel* typeLabel = new QLabel("Robot type:");
    mp_typeComboBox = new QComboBox();
    mp_typeComboBox->addItems({"Manual", "Automatic"});

    // Create a group for grouping all automatic controls of robot
    mp_auto_mode_items = new QGroupBox();
    mp_auto_mode_items->setTitle("Automatic Controls");
    // Create separate layout for adding the items
    QVBoxLayout* auto_items_layout = new QVBoxLayout(mp_auto_mode_items);

    // Collision threshold
    QLabel* collisionLabel = new QLabel("Collision threshold:");
    mp_collisionLineEdit = new QLineEdit(mp_main_window);
    auto_items_layout->addWidget(collisionLabel);
    auto_items_layout->addWidget(mp_collisionLineEdit);

    // Rotation angle
    QLabel* rotationLabel = new QLabel("Rotation angle:");
    mp_rotationLineEdit = new QLineEdit(mp_main_window);

    // Rotation direction
    QLabel* directionLabel = new QLabel("Rotation direction:");
    mp_directionComboBox = new QComboBox();
    mp_directionComboBox->addItems({"Clockwise", "Counter-clockwise"});
    auto_items_layout->addWidget(directionLabel);
    auto_items_layout->addWidget(mp_directionComboBox);

    // Add the buttons layout to the group box
    mp_auto_mode_items->setLayout(auto_items_layout);

    QPushButton* okButton = new QPushButton("OK");

    // Add all items to widget
    info_layout->addWidget(typeLabel);
    info_layout->addWidget(mp_typeComboBox);
    info_layout->addWidget(rotationLabel);
    info_layout->addWidget(mp_rotationLineEdit);
    info_layout->addWidget(mp_auto_mode_items);
    info_layout->addWidget(okButton);

    mp_info_container->setLayout(info_layout);

    // Set the position of the container widget below menu button
    mp_proxy = mp_scene->addWidget(mp_info_container);

    // Set hidden intially
    mp_info_container->setVisible(mp_visible);

    // Connect item event actions
    connect(okButton, &QPushButton::clicked, this, &Robot_Info::ok_click);
    connect(mp_typeComboBox, SIGNAL(activated(int)), this, SLOT(robot_type(int)));
    connect(mp_collisionLineEdit, &QLineEdit::textChanged, this, &Robot_Info::collision_value);
    connect(mp_rotationLineEdit, &QLineEdit::textChanged, this, &Robot_Info::rotation_value);
    connect(mp_directionComboBox, SIGNAL(activated(int)), this, SLOT(rotation_direction(int)));

    // Set static variable representing current instance of this class
    if (Robot_Info::instance != nullptr) {
        // Instance already exists, so delete it and replace it with this new one
        delete Robot_Info::instance;
    }
    Robot_Info::instance = this;
}

Robot_Info::~Robot_Info() {
    delete mp_proxy;
}

void Robot_Info::show_widget (Robot* cur_robot) {
    Robot_Info* cur_instance = Robot_Info::instance;
    // If already shown, hide it
    if (cur_instance->mp_visible) {
        cur_instance->mp_visible = false;
        cur_instance->mp_info_container->setVisible(false);
    }
    // Update class robot property
    cur_instance->mp_robot = cur_robot;
    // Load robot info
    cur_instance->process_robot_info();

    // Calculate new position of popup to ensure it fits inside window
    QPointF new_pos(
        cur_instance->mp_main_window->rect().topRight().x() - 200,
        cur_instance->mp_main_window->rect().topRight().y() - 5
    );
    // Apply calculated position
    cur_instance->mp_proxy->setPos(new_pos);

    // Show the widget
    cur_instance->mp_visible = true;
    cur_instance->mp_info_container->setVisible(true);
}

void Robot_Info::hide_related_widget (class Robot* cur_robot) {
    // If given robot widget is shown, hide it
    Robot_Info* cur_instance = Robot_Info::instance;
    if (cur_instance->mp_robot == cur_robot) {
        // Hide the widget
        cur_instance->mp_info_container->setVisible(false);
        cur_instance->mp_visible = false;
    }
}

void Robot_Info::process_robot_info () {
    // Load values vector from robot
    QVector<QString> info_from_robot = mp_robot->get_robot_info();
    // Update widget items with given info from robot
    mp_typeComboBox->setCurrentIndex(info_from_robot.at(0).toInt());
    mp_collisionLineEdit->setText(info_from_robot.at(1));
    mp_rotationLineEdit->setText(info_from_robot.at(2));
    mp_directionComboBox->setCurrentIndex(info_from_robot.at(3).toInt());
    // set visible items base of robot current mode
    update_visible_items(mp_typeComboBox->currentIndex());
}

void Robot_Info::update_visible_items (int mode) {
    if (mode == MANUAL) {
        mp_rotationLineEdit->setReadOnly(true);
        mp_auto_mode_items->hide();
    }
    else { // Automatic
        mp_rotationLineEdit->setReadOnly(false);
        mp_auto_mode_items->show();
    }
    Robot_Info::instance->mp_info_container->adjustSize();
}

void Robot_Info::ok_click () {
    // Hide the widget
    Robot_Info::instance->mp_info_container->setVisible(false);
    Robot_Info::instance->mp_visible = false;
}

void Robot_Info::robot_type (int index) {
    // Update robot mode
    mp_robot->set_mode(index);
    // set visible items base of robot current mode
    update_visible_items(index);
}

void Robot_Info::collision_value (const QString& text) {
    // Update robot collision distance threshold
    mp_robot->set_detect_threshold(text.toDouble());
}

void Robot_Info::rotation_value (const QString& text) {
    // Update robot rotation angle
    mp_robot->set_rotation_angle(text.toDouble());
}

void Robot_Info::rotation_direction (int index) {
    // Update robot rotation angle direction
    mp_robot->set_rotation_direction(index);
}

void Robot_Info::clean_up () {
    delete Robot_Info::instance;
    Robot_Info::instance = nullptr;
}
