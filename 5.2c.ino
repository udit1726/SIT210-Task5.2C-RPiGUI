import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QRadioButton, QPushButton, QVBoxLayout, QWidget
import RPi.GPIO as GPIO
# GPIO pins for LEDs
RED_LED_PIN = 17
GREEN_LED_PIN = 18
BLUE_LED_PIN = 27

# Initialize GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(RED_LED_PIN, GPIO.OUT)
GPIO.setup(GREEN_LED_PIN, GPIO.OUT)
GPIO.setup(BLUE_LED_PIN, GPIO.OUT)

class LEDController(QMainWindow):
    def _init_(self):
        super()._init_()

        # Create central widget
        central_widget = QWidget(self)

        # Create layout
        layout = QVBoxLayout()

        # Create radio buttons
        self.red_button = QRadioButton("Red LED", central_widget)
        self.green_button = QRadioButton("Green LED", central_widget)
        self.blue_button = QRadioButton("Blue LED", central_widget)

        # Create exit button
        self.exit_button = QPushButton("Exit", central_widget)

        # Connect button signals to slots
        self.red_button.clicked.connect(self.set_red_led)
        self.green_button.clicked.connect(self.set_green_led)
        self.blue_button.clicked.connect(self.set_blue_led)
        self.exit_button.clicked.connect(self.close)

        # Add widgets to layout
        layout.addWidget(self.red_button)
        layout.addWidget(self.green_button)
        layout.addWidget(self.blue_button)
        layout.addWidget(self.exit_button)

        # Set layout for central widget
        central_widget.setLayout(layout)

        # Set central widget
        self.setCentralWidget(central_widget)

    def set_red_led(self):
        GPIO.output(RED_LED_PIN, True)
        GPIO.output(GREEN_LED_PIN, False)
        GPIO.output(BLUE_LED_PIN, False)

    def set_green_led(self):
        GPIO.output(RED_LED_PIN, False)
        GPIO.output(GREEN_LED_PIN, True)
        GPIO.output(BLUE_LED_PIN, False)

    def set_blue_led(self):
        GPIO.output(RED_LED_PIN, False)
        GPIO.output(GREEN_LED_PIN, False)
        GPIO.output(BLUE_LED_PIN, True)

if _name_ == "_main_":
    app = QApplication(sys.argv)
    window = LEDController()
    window.show()
    sys.exit(app.exec_())

# Cleanup GPIO on exit
GPIO.cleanup()