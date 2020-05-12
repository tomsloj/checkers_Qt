#include "settingswidget.h"
#include "ui_settingswidget.h"

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);
    connect(ui->brownRadioButton, SIGNAL(clicked()), SLOT(brownOption()));
    connect(ui->blackRadiokButton, SIGNAL(clicked()), SLOT(blackOption()));
    connect(ui->backButton, SIGNAL(clicked()), SLOT(close()));

    QSettings settings("MySoft", "Star Runner");
    if( settings.value("blackPawn", QColor(Qt::black)).value<QColor>() == Qt::black )
        ui->blackRadiokButton->setChecked(true);
    else
        ui->brownRadioButton->setChecked(true);
}
void SettingsWidget::brownOption()
{
    QSettings settings("MySoft", "Star Runner");
    settings.setValue("blackPawn", QColor("#8B4513"));
    settings.setValue("whitePawn", QColor("#ffecb3"));
}
void SettingsWidget::blackOption()
{
    QSettings settings("MySoft", "Star Runner");
    settings.setValue("blackPawn", QColor(Qt::black));
    settings.setValue("whitePawn", QColor(Qt::white));
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}
