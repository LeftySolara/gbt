#ifndef DIALOGADDGAME_H
#define DIALOGADDGAME_H

#include "gamesdatabasemodel.h"
#include "uniquefiltermodel.h"

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QCompleter>

namespace Ui {
class DialogAddGame;
}

class DialogAddGame : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddGame(QWidget *parent = nullptr, GamesDatabaseModel *model = nullptr);
    ~DialogAddGame();

    QLineEdit *line_edit_title;
    QLineEdit *line_edit_series;
    QComboBox *combo_box_status;

private:
    Ui::DialogAddGame *ui;
    QStringList status_list;
    QCompleter *completer;
    UniqueFilterModel *proxy_model;
};

#endif // DIALOGADDGAME_H
