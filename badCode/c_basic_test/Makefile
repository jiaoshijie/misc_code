V := @
names := a b c d

exe_bin_01 := array copy_on_write ext main terminal_color class_fun unsign_minus sanmu pipe_use banker_al

nothing: clean
	$(V)echo "make clean"

all-%:
	$(V)echo "jiaoshijie_$*_endl"


second: all-Areyoukidding
	$(V)echo "second is running"

third:
	$(V)echo $(foreach n,$(names),$(n).o)

fourth:
	$(V)echo "$@ $$@@ $$$$ $$$$"

clean:
	$(V)rm -f $(exe_bin_01)
