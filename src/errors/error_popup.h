#ifndef ERRPOPUP_H
#define ERRPOPUP_H

#include "includes/libs_file.h"

class Error_PopUp : public QWidget {
    public:
        Error_PopUp (QWidget* window = nullptr);
        ~Error_PopUp ();

        static Error_PopUp* get_instance ();

        void show_err (QString err_msg);

    private:
        QLabel*  mp_err_txt_label;
        QWidget* mp_main_window;
        QTimer*  mp_popup_timer;

        static Error_PopUp* instance;
};

#endif // ERRPOPUP_H
