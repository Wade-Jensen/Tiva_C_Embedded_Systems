# invoke SourceDir generated makefile for empty.pem4f
empty.pem4f: .libraries,empty.pem4f
.libraries,empty.pem4f: package/cfg/empty_pem4f.xdl
	$(MAKE) -f C:\Users\WadeJensen\Dropbox\01_EN40\YEAR_4_SEM_1\EGH456\Repos\code_composer\empty_example/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\WadeJensen\Dropbox\01_EN40\YEAR_4_SEM_1\EGH456\Repos\code_composer\empty_example/src/makefile.libs clean

