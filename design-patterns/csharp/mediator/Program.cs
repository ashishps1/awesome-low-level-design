using System;

namespace Mediator
{
    class Program
    {
        static void Main(string[] args)
        {
            var mediator = new FormMediator();

            var usernameField = new TextField(mediator);
            var passwordField = new TextField(mediator);
            var loginButton = new Button(mediator);
            var statusLabel = new Label(mediator);

            mediator.SetUsernameField(usernameField);
            mediator.SetPasswordField(passwordField);
            mediator.SetLoginButton(loginButton);
            mediator.SetStatusLabel(statusLabel);

            // Simulate user interaction
            usernameField.SetText("admin");
            passwordField.SetText("1234");
            loginButton.Click();  // Should succeed

            Console.WriteLine("\n--- New Attempt with Wrong Password ---");
            passwordField.SetText("wrong");
            loginButton.Click();  // Should fail
        }
    }
} 