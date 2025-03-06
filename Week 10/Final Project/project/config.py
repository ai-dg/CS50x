# Try password recovery via email, but no success
class Config:
    MAIL_SERVER = "smtp-relay.gmail.com"
    MAIL_PORT = 587
    MAIL_USE_TLS = True
    MAIL_USE_SSL = False

    MAIL_USERNAME = "diegoagudeloa@gmail.com"
    MAIL_PASSWORD = "rzlgnuutlrlkfzii"

    MAIL_DEBUG = True
    MAIL_SUPPRESS_SEND = False

    MAIL_DEFAULT_SENDER = ("Flask", "fausse.adresse@gmail.com")
    MAIL_MAX_EMAILS = None
    MAIL_ASCII_ATTACHMENTS = False
