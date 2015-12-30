#Install ncurses
wget ftp://ftp.gnu.org/gnu/ncurses/ncurses-6.0.tar.gz<br />
tar xvf ncurses-6.0.tar.gz<br />
cd ncurses-6.0<br />
./configure --prefix=$HOME/<br />
make<br />
make install<br />

#Set terminfo environment variable
echo "TERMINFO=/usr/share/terminfo/" >> ~/.bash_profile<br />
echo "export TERMINFO" >> ~/.bash_profile<br />
echo "LANG=ko_KR.eucKR" >> ~/.bash_profile<br />
echo "export LANG" >> ~/.bash_profile<br />
source ~/.bash_profile
