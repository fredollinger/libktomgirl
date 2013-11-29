require 'rake/clean'

CLEAN.include("*.deb", "*.changes", "*.dsc", "libktomgirl_0.0.9-1.debian.tar.gz")

task :default => [:build]

desc "Build the project (default)"
task :build  do
	puts "default"
end

desc "Upload ppa to ubuntu"
task :ppa  do
	puts "dput ppa:follinge/precise-kde4-unasked-ppa libktomgirl_0.0.9-1_amd64.changes"
end

desc "Upload ppa to ubuntu"
task :deb do
    sh "debuild -i -us -uc -b"
end

namespace :test do
desc "Public api"
task :public do
    sh "cd test/public-api/build && rm -f api-test && make && ./api-test"
end 
end # namespace :test
