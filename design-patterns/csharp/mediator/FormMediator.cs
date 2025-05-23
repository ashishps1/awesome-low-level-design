namespace Mediator
{
    public class FormMediator : IUIMediator
    {
        private TextField usernameField;
        private TextField passwordField;
        private Button loginButton;
        private Label statusLabel;

        public void SetUsernameField(TextField usernameField)
        {
            this.usernameField = usernameField;
        }

        public void SetPasswordField(TextField passwordField)
        {
            this.passwordField = passwordField;
        }

        public void SetLoginButton(Button loginButton)
        {
            this.loginButton = loginButton;
        }

        public void SetStatusLabel(Label statusLabel)
        {
            this.statusLabel = statusLabel;
        }

        public void ComponentChanged(UIComponent component)
        {
            if (component == usernameField || component == passwordField)
            {
                bool enableButton = !string.IsNullOrEmpty(usernameField.GetText()) && 
                                  !string.IsNullOrEmpty(passwordField.GetText());
                loginButton.SetEnabled(enableButton);
            }
            else if (component == loginButton)
            {
                string username = usernameField.GetText();
                string password = passwordField.GetText();

                if (username == "admin" && password == "1234")
                {
                    statusLabel.SetText("✅ Login successful!");
                }
                else
                {
                    statusLabel.SetText("❌ Invalid credentials.");
                }
            }
        }
    }
} 