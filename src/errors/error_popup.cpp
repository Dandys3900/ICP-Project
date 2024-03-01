#include "error_popup.h"

Error_PopUp* Error_PopUp::instance = nullptr;

Error_PopUp::Error_PopUp (QWidget* window)
    : QWidget          (window),
      mp_err_txt_label (nullptr),
      mp_main_window   (window),
      mp_popup_timer   (nullptr)
{
    // Create label to store given error message to
    mp_err_txt_label = new QLabel(this);

    // Create pop-up layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    // Add label to layout
    layout->addWidget(mp_err_txt_label);
    layout->setAlignment(Qt::AlignCenter);

    // Create timer to show popup only given time
    mp_popup_timer = new QTimer(this);
    // Hide popup when timeout happens
    connect(mp_popup_timer, &QTimer::timeout, this, &Error_PopUp::hide);

    // Set red background color with black foreground
    setStyleSheet("background-color: red; color: black;");

    // Set static variable representing current instance of this class
    Error_PopUp::instance = this;
}

Error_PopUp::~Error_PopUp() {
}

Error_PopUp* Error_PopUp::get_instance () {
    return instance;
}

void Error_PopUp::show_err (QString err_msg) {
    // Add error message to label
    mp_err_txt_label->setText(err_msg);
    // Adjust size for message to fit in label
    adjustSize();

    // Calculate new position of popup to ensure it fits inside window
    QPointF new_pos(
        mp_main_window->rect().bottomRight().x() - width(),
        mp_main_window->rect().bottomRight().y() - height()
    );
    // Apply calculated position
    move(new_pos.x(), new_pos.y());

    // Start timer for 5s
    mp_popup_timer->start(5000);
    // Show popup
    this->show();
}
