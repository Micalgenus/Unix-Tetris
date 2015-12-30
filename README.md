#Install ncurses

    wget ftp://ftp.gnu.org/gnu/ncurses/ncurses-6.0.tar.gz
    tar xvf ncurses-6.0.tar.gz
    cd ncurses-6.0
    ./configure --prefix=$PWD/../
    make
    make install
    cd ..
    
    if [ -f ~/.bash_profile ] || [ -f /etc/issue ]; then
      PROFILE_PATH="~/.bash_profile"
    elif [ -f ~/.profile ] || [ -f /etc/version ]; then
      PROFILE_PATH="~/.profile"
    fi
    
    if [ -n $PROFILE_PATH ]; then
      echo "NCURSES_PATH="$PWD >> ~/.bash_profile
    fi
    
    # ncurses header file link
    ln -s $NCURSES_PATH/include/ncurses/ncurses.h $NCURSES_PATH/include/

#Set terminfo environment variable
echo "TERMINFO="$NCURSES_PATH"/share/terminfo/" >> ~/.bash_profile<br />
echo "export TERMINFO" >> ~/.bash_profile<br />
echo "LANG=ko_KR.eucKR" >> ~/.bash_profile<br />
echo "export LANG" >> ~/.bash_profile<br />
source ~/.bash_profile
