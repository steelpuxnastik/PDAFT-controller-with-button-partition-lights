# PDAFT controller with button/partition lights

<img src="PDAFT_BPL_PCB/images/1.webp" alt="front" width="30%" height="30%" /> <img src="PDAFT_BPL_PCB/images/2.webp" alt="back" width="30%" height="30%" />

Hatsune Miku Project DIVA Arcade Future Tone controller with button/partition lights support (like on official arcade) controlled by game. Only buttons (TRIANGLE, SQUARE, CROSS, CIRCLE, START) + abitily to connect 4 button LED and left/right partition RGB LED strip (without slider, for slider I recomend to use LKP https://github.com/Project-Alpaca/LKP). LED info obtained by UART, special PD-Loader plugin activation needed (coming soon).

Contains PCB and firmware for Arduino Pro Micro that used in it.

Board has two possibilities to receive serial data: throught USB (serial) or using TTL (serial1).
Why is that? Because ATMEGA32U4 chip directly supports USB connections and supports USB-Serial connection, but USB-Serial doesn't supports interuptions. Interuptions can be realized only throught direct connection to RX/TX pins using, for example, USB-TTL converter. It theoreticaly can make using gamepad without delays and Serial1 will be used only when new data will appear, but in real work with Serial data optimized as far as I know at this moment and works very fast (direct write to registers used), so needs only few cycles to work with that, so in reality maybe there will be no difference in use USB-Serial or TTL.

To use USB-Serial connection flash `firmware/firmware_USB-Serial/firmware_USB-Serial.ino`

To use TTL - `firmware/firmware_TTL/firmware_TTL.ino`

Work in progress