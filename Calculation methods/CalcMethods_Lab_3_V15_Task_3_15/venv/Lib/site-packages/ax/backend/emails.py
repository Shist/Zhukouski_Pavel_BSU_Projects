""" Sends emails
Use like this -
    import backend.emails as ax_emails
    ax_emails.email_sender(to='', text='', html=None, subject='')

"""

import sys
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.header import Header
from loguru import logger
import aiosmtplib

this = sys.modules[__name__]
email_sender = None


def init_email(smtp_host, smtp_login, smtp_password, port=465, ssl=False):
    """ create EmailSender, remember creds """
    this.email_sender = EmailSender(
        smtp_host=smtp_host,
        smtp_login=smtp_login,
        smtp_password=smtp_password,
        port=port,
        ssl=ssl
    )


class EmailSender:
    """ Used to send emails """

    def __init__(self, smtp_host, smtp_login, smtp_password, port=465,
                 ssl=False):
        self.smtp_host = smtp_host
        self.smtp_login = smtp_login
        self.smtp_password = smtp_password
        self.port = port
        self.ssl = ssl

    async def __call__(self,    # pylint: disable=invalid-name
                       to,
                       text='Hello world',
                       html=None,
                       subject='Message from AX'):
        try:
            recipients = []
            if isinstance(to, list):
                recipients = to
            else:
                recipients.append(to)

            msg = MIMEMultipart('alternative')

            msg['Subject'] = Header(subject, "utf-8").encode()
            msg['From'] = self.smtp_login
            msg['To'] = ", ".join(recipients)

            if not html:
                html = text.replace('\n', '<br>')
            part1 = MIMEText(text.encode('utf-8'), 'plain', 'utf-8')
            part2 = MIMEText(html.encode('utf-8'), 'html', 'utf-8')

            msg.attach(part1)
            msg.attach(part2)

            await aiosmtplib.send(
                msg,
                recipients=recipients,
                sender=self.smtp_login,
                hostname=self.smtp_host,
                port=self.port,
                username=self.smtp_login,
                password=self.smtp_password,
                use_tls=self.ssl
            )
        except Exception:
            logger.exception('Error sending email with Ax email sender')
            raise
