# install ncurses
wget ftp://ftp.gnu.org/gnu/ncurses/ncurses-6.0.tar.gz
tar xvf ncurses-6.0.tar.gz
cd ncurses-6.0
./configure --prefix=$HOME/
make
make install

# set terminfo environment variable
echo "TERMINFO=/usr/share/terminfo/" >> ~/.bash_profile
echo "export TERMINFO" >> ~/.bash_profile
echo "LANG=ko_KR.eucKR" >> ~/.bash_profile
echo "export LANG" >> ~/.bash_profile
source ~/.bash_profile

# Please This command Execute.
