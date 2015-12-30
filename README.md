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
      NCURSES_PATH=$PWD
      echo "NCURSES_PATH="$PWD >> ~/.bash_profile
    fi
    
    # ncurses header file link
    ln -s $NCURSES_PATH/include/ncurses/ncurses.h $NCURSES_PATH/include/
    source $PROFILE_PATH

#Set terminfo environment variable

    echo "TERMINFO="$NCURSES_PATH"/share/terminfo/" >> $PROFILE_PATH
    echo "export TERMINFO" >> $PROFILE_PATH
    echo "LANG=ko_KR.eucKR" >> $PROFILE_PATH
    echo "export LANG" >> $PROFILE_PATH
    source $PROFILE_PATH
