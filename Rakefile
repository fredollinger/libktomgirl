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
