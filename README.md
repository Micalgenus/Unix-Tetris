#Install ncurses
wget ftp://ftp.gnu.org/gnu/ncurses/ncurses-6.0.tar.gz

tar xvf ncurses-6.0.tar.gz<br />
cd ncurses-6.0<br />
./configure --prefix=$PWD/../<br />
make<br />
make install<br />
cd ..<br />
<br />
if [ -f ~/.bash_profile ] || [ -f /etc/issue ]; then<br />
&nbsp;&nbsp;PROFILE_PATH="~/.bash_profile"<br />
elif [ -f ~/.profile ] || [ -f /etc/version ]; then<br />
&nbsp;&nbsp;PROFILE_PATH="~/.profile"<br />
fi<br />
<br />
if [ -n $PROFILE_PATH ]; then<br />
&nbsp;&nbsp;echo "NCURSES_PATH="$PWD >> ~/.bash_profile<br />
fi

&#35; ncurses header file link<br />
ln -s $NCURSES_PATH/include/ncurses/ncurses.h $NCURSES_PATH/include/<br />

#Set terminfo environment variable
echo "TERMINFO="$NCURSES_PATH"/share/terminfo/" >> ~/.bash_profile<br />
echo "export TERMINFO" >> ~/.bash_profile<br />
echo "LANG=ko_KR.eucKR" >> ~/.bash_profile<br />
echo "export LANG" >> ~/.bash_profile<br />
source ~/.bash_profile
