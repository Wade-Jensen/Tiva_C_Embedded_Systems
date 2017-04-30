# invoke SourceDir generated makefile for testing_station.pem4f
testing_station.pem4f: .libraries,testing_station.pem4f
.libraries,testing_station.pem4f: package/cfg/testing_station_pem4f.xdl
	$(MAKE) -f C:\Users\WadeJensen\Dropbox\01_EN40\YEAR_4_SEM_1\EGH456\Repos\code_composer\testing_station/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\WadeJensen\Dropbox\01_EN40\YEAR_4_SEM_1\EGH456\Repos\code_composer\testing_station/src/makefile.libs clean

