/** ICP Project 2023/2024
 * @file user_menu.cpp
 * @author Tomáš Daniel (xdanie14)
 * @brief Displaying program and simulation controls to the user.
 */

#include "user_menu.h"

UserMenu::UserMenu (QGraphicsScene* scene, PlayGround* playground, QWidget* window)
    : QWidget        (window),
      mp_playground  (playground),
      mp_scene       (scene),
      mp_expanded    (false)
{
    // Create menu button
    QPushButton* menu_button = new QPushButton();
    mp_proxy_button = mp_scene->addWidget(menu_button);

    // Set button position to window's top left corner
    mp_proxy_button->setPos(5, 5);
    // Set hamburger icon for menu button
    menu_button->setIcon(QIcon(":/icons/menu_icon.png"));

    // Create container widget to hold all user menu items
    mp_menu_container = new QWidget();
    QVBoxLayout* menu_layout = new QVBoxLayout(mp_menu_container);

    // Add buttons for user to load/store configuration
    QPushButton* load_conf_btn = new QPushButton("Load");
    QPushButton* store_conf_btn = new QPushButton("Save");

    // Add load/store buttons to top of menu
    QHBoxLayout* conf_items_layout = new QHBoxLayout(mp_menu_container);
    conf_items_layout->addWidget(load_conf_btn);
    conf_items_layout->addWidget(store_conf_btn);

    // Add buttons for user to create new scene_objects
    QPushButton* add_robot_btn = new QPushButton("Add Robot");
    QPushButton* add_obstacle_btn = new QPushButton("Add Obstacle");

    // Combo box for user to select between manual control of the simulation or automatic
    QComboBox* sim_select_box = new QComboBox();
    sim_select_box->addItems({"Manual", "Automatic"});

    // Create a group for grouping all automatic simulation related items and control their visibility centrally
    mp_sim_mode_items = new QGroupBox();
    mp_sim_mode_items->setTitle("Simulation Controls");

    // Add buttons for user to control automatic simulation process
    QPushButton* stop_sim_btn = new QPushButton("Stop");
    QPushButton* start_sim_btn = new QPushButton("Start");
    this->mp_stop_sim_button = stop_sim_btn;
    this->mp_start_sim_button = start_sim_btn;
    // Set corresponding icons
    stop_sim_btn->setIcon(QIcon(":/icons/stop_icon.png"));
    stop_sim_btn->setEnabled(false);
    start_sim_btn->setIcon(QIcon(":/icons/play_icon.png"));

    // Create horizontal layout for start and stop buttons
    QHBoxLayout* sim_buttons_layout = new QHBoxLayout;
    sim_buttons_layout->addWidget(stop_sim_btn);
    sim_buttons_layout->addWidget(start_sim_btn);

    // Slider for user to regulate automatic simulation Robots movement speed
    QSlider* speed_slider = new QSlider(Qt::Horizontal);
    speed_slider->setMinimum(1);
    speed_slider->setMaximum(100);
    speed_slider->setSingleStep(1);
    speed_slider->setValue(50);
    mp_playground->set_automatic_mode_speed(speed_slider->value());
    // Add the speed slider above the buttons within the same group box
    QVBoxLayout* sim_items_layout = new QVBoxLayout(mp_sim_mode_items);
    sim_items_layout->addWidget(speed_slider);
    sim_items_layout->addLayout(sim_buttons_layout);

    // Add the buttons layout to the group box
    mp_sim_mode_items->setLayout(sim_items_layout);
    // Hide initially (default is manual control)
    mp_sim_mode_items->hide();

    // Add all widgets to the main user menu vertical layout
    menu_layout->addLayout(conf_items_layout);
    menu_layout->addWidget(add_robot_btn);
    menu_layout->addWidget(add_obstacle_btn);
    menu_layout->addWidget(sim_select_box);
    menu_layout->addWidget(mp_sim_mode_items);

    // Set the main menu layout as the layout for the menu container
    mp_menu_container->setLayout(menu_layout);

    // Set the position of the container widget below menu button
    mp_container_proxy = mp_scene->addWidget(mp_menu_container);
    mp_container_proxy->setPos(5, 35);

    // Hide user menu initially
    mp_menu_container->hide();

    // Connect buttons event actions
    connect(menu_button, &QPushButton::clicked, this, &UserMenu::btn_click);
    connect(load_conf_btn, &QPushButton::clicked, this, &UserMenu::load_config);
    connect(store_conf_btn, &QPushButton::clicked, this, &UserMenu::store_config);
    connect(add_robot_btn, &QPushButton::clicked, this, &UserMenu::add_robot);
    connect(add_obstacle_btn, &QPushButton::clicked, this, &UserMenu::add_obstacle);
    connect(sim_select_box, SIGNAL(activated(int)), this, SLOT(mode_select(int)));
    connect(stop_sim_btn, &QPushButton::clicked, this, &UserMenu::stop_sim);
    connect(start_sim_btn, &QPushButton::clicked, this, &UserMenu::start_sim);
    connect(speed_slider, &QSlider::valueChanged, this, &UserMenu::sim_speed_set);
}

UserMenu::~UserMenu() {
    delete mp_container_proxy;
    delete mp_proxy_button;
}

void UserMenu::btn_click () {
    // Take focus away from focused scene object (if any)
    mp_playground->set_active_obj(nullptr, NO_ACTION);
    // Update user menu status and set its visibility accordingly
    mp_expanded = !mp_expanded;
    mp_menu_container->setVisible(mp_expanded);
}

void UserMenu::load_config () {
    mp_playground->load_config();
}

void UserMenu::store_config () {
    mp_playground->store_config();
}

void UserMenu::add_robot () {
    // Initial position is not important, mouse click to scene will place it later
    Robot* new_robot = new Robot(100, 0, 0, mp_playground);
    mp_playground->set_toplace_obj(new_robot);
}

void UserMenu::add_obstacle () {
    // Initial position is not important, mouse click to scene will place it later
    Obstacle* new_obstacle = new Obstacle(70, 70, 0, 0, mp_playground);
    mp_playground->set_toplace_obj(new_obstacle);
}

void UserMenu::mode_select (int index) {
    if (index == MANUAL) { // Hide simulation controls
        mp_sim_mode_items->hide();
    }
    else { // Show simulation controls
        mp_sim_mode_items->show();
    }
    mp_menu_container->adjustSize();
    mp_playground->set_mode(index == MANUAL ? MANUAL : AUTOMATIC);
}

void UserMenu::sim_speed_set (int slider_value) {
    mp_playground->set_automatic_mode_speed(slider_value);
}

void UserMenu::start_sim () {
    mp_playground->set_automatic_mode_running(true);
    this->mp_stop_sim_button->setEnabled(true);
    this->mp_start_sim_button->setEnabled(false);
}

void UserMenu::stop_sim () {
    mp_playground->set_automatic_mode_running(false);
    this->mp_stop_sim_button->setEnabled(false);
    this->mp_start_sim_button->setEnabled(true);
}
