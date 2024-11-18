import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
import argparse

def send_email(sender_email, password, recipient_email, subject, body):
    try:
        msg = MIMEMultipart()
        msg['From'] = sender_email
        msg['To'] = recipient_email
        msg['Subject'] = subject
        msg.attach(MIMEText(body, 'plain'))

        # Connect to Gmail's SMTP server
        server = smtplib.SMTP('smtp.gmail.com', 587)
        server.starttls()
        server.login(sender_email, password)
        text = msg.as_string()
        server.sendmail(sender_email, recipient_email, text)
        server.quit()

        print("Email sent successfully!")
    except Exception as e:
        print(f"Failed to send email: {e}")

# Main function to parse arguments and send email
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Send email via CLI")
    parser.add_argument("--sender", required=True, help="Sender email address")
    parser.add_argument("--password", required=True, help="Sender email password")
    parser.add_argument("--recipient", required=True, help="Recipient email address")
    parser.add_argument("--subject", required=True, help="Email subject")
    parser.add_argument("--body", required=True, help="Email body")

    args = parser.parse_args()
    send_email(args.sender, args.password, args.recipient, args.subject, args.body)
