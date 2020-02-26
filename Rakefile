require 'rake/clean'

APP="libktomgirl"
MAJOR_VERSION="0"
MINOR_VERSION="0"
MICRO_VERSION="14"
UBUNTU_VERSION="0"
WHOLE_VERSION=MAJOR_VERSION + "." + MINOR_VERSION + "." + MICRO_VERSION 
DEBIAN_VERSION=MAJOR_VERSION + "." + MINOR_VERSION + "." + MICRO_VERSION + "-" + UBUNTU_VERSION 
APP_DIR=APP + "-" + WHOLE_VERSION
LINKPATH="#{APP}-#{WHOLE_VERSION}"
TARBALL="#{APP}_#{DEBIAN_VERSION}.orig.tar.gz"
BUILD="builddir"
DEPENDENCIES="debhelper cmake libpcre++-dev libstdc++-8-dev libpcre3-dev \
libboost-filesystem-dev libboost-dev libboost-system-dev libboost-date-time-dev \
libsigc++-2.0-dev libxml2-dev"

CLEAN.include("../*.deb", "../#{TARBALL}", "obj-x86_64-linux-gnu", LINKPATH, "builddir")

task :default => [:build]

desc "Build the project (default)"
task :build  do
  sh "mkdir -p builddir && cd builddir && cmake .. && make -j3"
end

desc "Upload ppa to ubuntu"
task :ppa  do
	puts "dput ppa:follinge/precise-kde4-unasked-ppa libktomgirl_0.0.9-1_amd64.changes"
end

desc "Make Debian/Ubuntu Package"
task :deb do
    sh "debuild -i -us -uc -b -j3"
end

desc "install locally"
task :install do
    sh "cd #{BUILD} && sudo make install"
end

namespace :test do
desc "Public api"
task :public do
    sh "cd test/public-api/build && rm -f api-test && make && ./api-test"
end 
end # namespace :test

desc "build tarball package"
task :tgz do
	#ktomgirl_0.0.10.orig.tar.gz
	sh "rm -f ../#{LINKPATH}"
	sh "ln -s #{APP} ../#{LINKPATH}"
	sh "cd .. && tar --exclude #{LINKPATH}/debian --exclude #{LINKPATH}/.git -chzvf #{TARBALL} #{LINKPATH}"
end

desc "install dependencies"
task :deps do
	sh "sudo apt install #{DEPENDENCIES}"
end

