from PyQt5.QtWidgets import QDialog, QFileDialog, QMessageBox
from playground.engine import cetechproject

from playground.ui.addexistingdialog import Ui_Dialog


class AddExistItemDialog(QDialog, Ui_Dialog):
    def __init__(self, parent):
        super(AddExistItemDialog, self).__init__(parent)
        self.setupUi(self)

    def get_project_settings(self):
        return self.project_name_edit.text(), self.project_dir_edit.text()

    def open_dir(self):
        selected_dir = QFileDialog.getExistingDirectory(self, "Select Directory")

        if cetechproject.validate_project(selected_dir):
            self.project_dir_edit.setText(selected_dir)

    def done(self, r):
        if r == QDialog.Accepted:
            if self.project_name_edit.text() == '':
                QMessageBox.critical(None, 'Project validation error', 'Project name is empty',
                                     QMessageBox.Yes, QMessageBox.Yes)
                return

            if not cetechproject.validate_project(self.project_dir_edit.text()):
                return
            else:
                super(AddExistItemDialog, self).done(r)

        super(AddExistItemDialog, self).done(r)
