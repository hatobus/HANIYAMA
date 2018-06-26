sudo usermod -a -G dialout $USER && \
if [ `python --version 2>&1 | grep '2.7' | wc -l` = "1" ]; then \
sudo zypper install git python-pip python-pyserial; \
else \
sudo zypper install git python3-pip python3-pyserial; \
fi && \
mkdir -p ~/Arduino/hardware/espressif && \
cd ~/Arduino/hardware/espressif && \
git clone https://github.com/espressif/arduino-esp32.git esp32 && \
cd esp32 && \
git submodule update --init --recursive && \
cd tools && \
python get.py