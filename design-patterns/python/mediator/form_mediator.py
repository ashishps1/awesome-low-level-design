from typing import Optional
from .ui_mediator import UIMediator
from .ui_component import UIComponent
from .text_field import TextField
from .button import Button
from .label import Label

class FormMediator(UIMediator):
    def __init__(self):
        self.username_field: Optional[TextField] = None
        self.password_field: Optional[TextField] = None
        self.login_button: Optional[Button] = None
        self.status_label: Optional[Label] = None

    def set_username_field(self, field: TextField) -> None:
        self.username_field = field

    def set_password_field(self, field: TextField) -> None:
        self.password_field = field

    def set_login_button(self, button: Button) -> None:
        self.login_button = button

    def set_status_label(self, label: Label) -> None:
        self.status_label = label

    def component_changed(self, component: UIComponent) -> None:
        if component in (self.username_field, self.password_field):
            if self.username_field and self.password_field and self.login_button:
                enable_button = bool(self.username_field.text and self.password_field.text)
                self.login_button.enabled = enable_button
        elif component == self.login_button:
            if (self.username_field and self.password_field and 
                self.status_label and self.login_button):
                username = self.username_field.text
                password = self.password_field.text

                if username == "admin" and password == "1234":
                    self.status_label.text = "✅ Login successful!"
                else:
                    self.status_label.text = "❌ Invalid credentials." 