/** ICP Project 2023/2024
 * @file error_popup.cpp
 * @author Tomáš Daniel (xdanie14)
 * @brief Displaying error widget with given error message to the user.
 */

#include "error_popup.h"

Error_PopUp* Error_PopUp::instance = nullptr;

Error_PopUp::Error_PopUp (QWidget* window)
    : QWidget          (window),
      mp_main_window   (window),
      mp_popup_timer   (nullptr)
{
    // Create label to store given error message to
    mp_err_txt_label = new QLabel(this);

    // Create pop-up layout
    mp_layout = new QVBoxLayout(this);
    // Add label to layout
    mp_layout->addWidget(mp_err_txt_label);
    mp_layout->setAlignment(Qt::AlignCenter);

    // Create timer to show popup only given time
    mp_popup_timer = new QTimer(this);
    // Hide popup when timeout happens
    connect(mp_popup_timer, &QTimer::timeout, this, &Error_PopUp::hide);

    // Set red background color with black foreground
    setStyleSheet("background-color: red; color: black;");

    // Set static variable representing current instance of this class
    if (Error_PopUp::instance != nullptr) {
        // Instance already exists, so delete it and replace it with this new one
        delete Error_PopUp::instance;
    }
    Error_PopUp::instance = this;
}

Error_PopUp::~Error_PopUp() {
    delete mp_popup_timer;
    delete mp_layout;
}

void Error_PopUp::show_err (QString err_msg) {
    Error_PopUp* cur_instance = Error_PopUp::instance;

    // Add error message to label
    cur_instance->mp_err_txt_label->setText(err_msg);
    // Adjust size for message to fit in label
    cur_instance->adjustSize();

    // Calculate new position of popup to ensure it fits inside window
    QPoint new_pos(
        cur_instance->mp_main_window->rect().bottomRight().x() - cur_instance->width(),
        cur_instance->mp_main_window->rect().bottomRight().y() - cur_instance->height()
    );
    // Apply calculated position
    cur_instance->move(new_pos);

    // Start timer for 5s
    cur_instance->mp_popup_timer->start(5000);
    // Show popup
    cur_instance->show();
}

void Error_PopUp::clean_up () {
    delete Error_PopUp::instance;
    Error_PopUp::instance = nullptr;
}
