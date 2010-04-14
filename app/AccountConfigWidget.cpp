#include "AccountConfigWidget.h"
#include "ui_AccountConfigWidget.h"
#include <QSettings>

AccountConfigWidget::AccountConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountConfigWidget)
{
    ui->setupUi(this);
}

AccountConfigWidget::~AccountConfigWidget()
{
    delete ui;
}

void AccountConfigWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void AccountConfigWidget::readSetting()
{
    QSettings setting;
    setting.beginGroup("account");
    ui->jidLineEdit->setText(setting.value("jid").toString());
    ui->passwordLineEdit->clear();
    if (setting.value("isStorePassword", false).toBool())
        ui->passwordLineEdit->setText(setting.value("password").toString());
    ui->hostLineEdit->setText(setting.value("host").toString());
    ui->portSpinBox->setValue(setting.value("port", 5222).toInt());
    ui->storePasswordCheckBox->setChecked(setting.value("isStorePassword", false).toBool());
    ui->autoLoginCheckBox->setChecked(setting.value("isAutoLogin", false).toBool());;
    setting.endGroup();
}

void AccountConfigWidget::writeSetting()
{
    QSettings setting;
    setting.beginGroup("account");
    setting.setValue("jid", ui->jidLineEdit->text());
    if (ui->storePasswordCheckBox->isChecked())
        setting.setValue("password", ui->passwordLineEdit->text());
    else
        setting.remove("password");
    setting.setValue("host", ui->hostLineEdit->text());
    setting.setValue("port", ui->portSpinBox->value());
    setting.setValue("isStorePassword", ui->storePasswordCheckBox->isChecked());
    setting.setValue("isAutoLogin", ui->autoLoginCheckBox->isChecked());
    setting.endGroup();
    emit settingChanged();
}
