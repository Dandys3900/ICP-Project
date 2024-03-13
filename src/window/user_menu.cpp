#include "user_menu.h"

UserMenu::UserMenu (QGraphicsScene* scene, PlayGround* playground, QWidget* window)
    : QWidget        (window),
      mp_playground  (playground),
      mp_scene       (scene),
      mp_expanded    (false)
{
    // Create menu button
    QPushButton* menu_button = new QPushButton();
    QGraphicsProxyWidget* proxy_button = mp_scene->addWidget(menu_button);

    // Set button position to window's top left corner
    proxy_button->setPos(5, 5);
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
    sim_select_box->addItem("Manual");
    sim_select_box->addItem("Automatic");

    // Create a group for grouping all automatic simulation related items and control their visibility centrally
    mp_sim_mode_items = new QGroupBox();
    mp_sim_mode_items->setTitle("Simulation Controls");

    // Add buttons for user to control automatic simulation process
    QPushButton* stop_sim_btn = new QPushButton("Stop");
    QPushButton* start_sim_btn = new QPushButton("Start");
    // Set corresponding icons
    stop_sim_btn->setIcon(QIcon(":/icons/stop_icon.png"));
    start_sim_btn->setIcon(QIcon(":/icons/play_icon.png"));

    // Create horizontal layout for start and stop buttons
    QHBoxLayout* sim_buttons_layout = new QHBoxLayout;
    sim_buttons_layout->addWidget(stop_sim_btn);
    sim_buttons_layout->addWidget(start_sim_btn);

    // Slider for user to regulate automatic simulation Robots movement speed
    QSlider* speed_slider = new QSlider(Qt::Horizontal);
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
    QGraphicsProxyWidget* container_proxy = mp_scene->addWidget(mp_menu_container);
    container_proxy->setPos(5, 35);

    // Hide user menu initially
    mp_menu_container->hide();

    // Connect buttons event actions
    QObject::connect(menu_button, &QPushButton::clicked, this, &UserMenu::btn_click);
    QObject::connect(load_conf_btn, &QPushButton::clicked, this, &UserMenu::load_config);
    QObject::connect(store_conf_btn, &QPushButton::clicked, this, &UserMenu::store_config);
    QObject::connect(add_robot_btn, &QPushButton::clicked, this, &UserMenu::add_robot);
    QObject::connect(add_obstacle_btn, &QPushButton::clicked, this, &UserMenu::add_obstacle);
    QObject::connect(sim_select_box, QOverload<int>::of(&QComboBox::activated), this, &UserMenu::mode_select);
    QObject::connect(stop_sim_btn, &QPushButton::clicked, this, &UserMenu::stop_sim);
    QObject::connect(start_sim_btn, &QPushButton::clicked, this, &UserMenu::start_sim);
    QObject::connect(speed_slider, &QSlider::valueChanged, this, &UserMenu::sim_speed_set);
}

UserMenu::~UserMenu() {
}

void UserMenu::btn_click () {
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
    // Placeholder for handling "Add Robot" button click
}

void UserMenu::add_obstacle () {
    // Placeholder for handling "Add Obstacle" button click
}

void UserMenu::mode_select (int index) {
    if (index == 0) { // Hide simulation controls
        mp_sim_mode_items->hide();
    }
    else { // Show simulation controls
        mp_sim_mode_items->show();
    }
    mp_menu_container->adjustSize();
}

void UserMenu::sim_speed_set (int slider_value) {
    // Placeholder for actions related to simulation speed change
}

void UserMenu::start_sim () {
    // Placeholder for actions related to starting the simulation
}

void UserMenu::stop_sim () {
    // Placeholder for actions related to stopping the simulation
}
