# invoke SourceDir generated makefile for mutex.pem4f
mutex.pem4f: .libraries,mutex.pem4f
.libraries,mutex.pem4f: package/cfg/mutex_pem4f.xdl
	$(MAKE) -f C:\Users\WadeJensen\Dropbox\01_EN40\YEAR_4_SEM_1\EGH456\Repos\code_composer\mutex_echo/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\WadeJensen\Dropbox\01_EN40\YEAR_4_SEM_1\EGH456\Repos\code_composer\mutex_echo/src/makefile.libs clean

