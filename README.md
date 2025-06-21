# FMRadioTuningSystem  
CSE 462 – Final Project

[Final Report](https://docs.google.com/document/d/1Ere9BFUZ7-QpyjE28P_dVeUl3OzzBQSnGsau3Upfi4o/edit?usp=sharing)

This project simulates a car-style FM radio using an Arduino Mega, RTL-SDR dongle, and Python. Users can manually tune stations using a potentiometer, select preset stations with buttons, and automatically scan for the strongest FM signal. The selected station is displayed on an LCD, and audio is streamed via the RTL-SDR dongle.


### `FMRadio/FMRadio.ino`
This is the **Arduino sketch** that runs on the Arduino Mega.

- Reads **user input** from a potentiometer (for tuning) and buttons (for presets and scan).
- Sends commands to the Python script via **serial communication** (e.g., `FREQ:106.9` or `SCAN`).
- Receives messages back from the Python script and **displays the current frequency or scan** on the LCD screen.


### `FMRadioTunerBoxFinal.ipynb`
A **Python Jupyter Notebook** that acts as the bridge between the Arduino and the RTL-SDR dongle.

- Listens for serial input from the Arduino and processes commands.
- Uses the **RTL-SDR** to tune to FM frequencies based on input.
- Handles **FM signal demodulation** and plays back the audio.
- Performs **auto-scan** functionality by checking signal strength across the FM band and returning the strongest station to the Arduino.
