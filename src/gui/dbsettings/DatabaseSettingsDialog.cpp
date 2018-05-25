/*
 *  Copyright (C) 2018 KeePassXC Team <team@keepassxc.org>
 *  Copyright (C) 2012 Felix Geyer <debfx@fobos.de>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 or (at your option)
 *  version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "DatabaseSettingsDialog.h"
#include "ui_DatabaseSettingsDialog.h"
#include "DatabaseSettingsWidgetGeneral.h"
#include "DatabaseSettingsWidgetEncryption.h"

#include "core/FilePath.h"

#include <QWizardPage>

DatabaseSettingsDialog::DatabaseSettingsDialog(QWidget* parent)
    : DialogyWidget(parent)
    , m_ui(new Ui::DatabaseSettingsDialog())
    , m_generalPage(new DatabaseSettingsWidgetGeneral())
    , m_encryptionPage(new DatabaseSettingsWidgetEncryption())
{
    m_ui->setupUi(this);

    connect(m_ui->buttonBox, SIGNAL(accepted()), SLOT(save()));
    connect(m_ui->buttonBox, SIGNAL(rejected()), SLOT(reject()));

    m_ui->categoryList->addCategory(tr("General"), FilePath::instance()->icon("categories", "preferences-other"));
    m_ui->categoryList->addCategory(tr("Encryption"), FilePath::instance()->icon("actions", "document-encrypt"));
    m_ui->stackedWidget->addWidget(m_generalPage);
    m_ui->stackedWidget->addWidget(m_encryptionPage);

    connect(m_ui->categoryList, SIGNAL(categoryChanged(int)), m_ui->stackedWidget, SLOT(setCurrentIndex(int)));
}

DatabaseSettingsDialog::~DatabaseSettingsDialog()
{
}

void DatabaseSettingsDialog::load(Database* db)
{
    m_ui->categoryList->setCurrentCategory(0);
    m_generalPage->load(db);
    m_encryptionPage->load(db);
}

void DatabaseSettingsDialog::save()
{
    m_generalPage->save();
    m_encryptionPage->save();
    emit editFinished(true);
}

void DatabaseSettingsDialog::reject()
{
    emit editFinished(false);
}
