make
if [ "$?" = "0" ]; then
    rm *.o
    rm -r dep
    rm *.elf
    rm *.map
fi
