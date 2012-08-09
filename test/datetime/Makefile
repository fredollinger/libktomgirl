UIC=uic-qt4
UI_HEADERS= ui_searchwindow.h

.PHONY: ktgconfig.h

all: 
	mkdir -p build
	cd build && make 2>err

ui_searchwindow.h:
	$(UIC) searchwindow.ui > ui_searchwindow.h

ui_notesdialog.h:
	$(UIC) notesdialog.ui > ui_notesdialog.h
ui_notebooksdialog.h:
	$(UIC) notebooksdialog.ui > ui_notebooksdialog.h
setup:
	mkdir build
	cd build && cmake ..
err:
	vim build/err
clean:
	cd build && make clean
dist-clean:
	rm $(UI_HEADERS)

build/ktomgirl:
	make all
install: build/ktomgirl
	cd build && su -c "make install"
	#cd build && sudo make install
test:
	build/ktomgirl

newprojectlayout4.h:
	uic-qt4 ui/newprojectlayout4.ui > newprojectlayout4.h 


kgtconfig.h:
	rm -f ktgconfig.h
	kconfig_compiler ktgconfig.kcfg ktgconfig.kcfgc
deps:
	sudo apt-get install kdelibs5-dev g++ cmake
# Sat Mar 17 17:29:13 PDT 2012
