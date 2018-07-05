sudo usermod -a -G dialout $USER &&
# To judge exist of git command
git --help > /dev/null 2>&1

if [ $? -eq 127 ] ; then
    echo " Git has not been installed. To start install Git. "
    sudo apt-get install git 
fi

wget https://bootstrap.pypa.io/get-pip.py && \
sudo python get-pip.py && \
sudo pip install pyserial && \
mkdir -p ~/Arduino/hardware/espressif && \

if [-d "/Applications/Arduino_*"] ; then
    # If Arduino installed at /Applications folder
    cd /Applications/Arduino_*/Contents/java/hardware/
    mkdir -p espressif && \
    cd espressif && \
    git clone https://github.com/espressif/arduino-esp32.git esp32 && \
    cd esp32 && \
    git submodule update --init --recursive && \
    cd tools && \
    python2 get.py        

else
    cd ~/Arduino/hardware/espressif && \
    git clone https://github.com/espressif/arduino-esp32.git esp32 && \
    cd esp32 && \
    git submodule update --init --recursive && \
    cd tools && \
    python2 get.py
fi
