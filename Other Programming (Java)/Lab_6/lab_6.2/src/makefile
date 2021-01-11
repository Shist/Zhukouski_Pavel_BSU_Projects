# makefile
# converts properties from UTF-16 to ISO-8859-1 

OUT=.
DEF_RES=Msg_en_GB

all:	$(OUT)\Msg.properties \
	$(OUT)\Msg_be_BY.properties \
	$(OUT)\Msg_en_GB.properties \
	$(OUT)\Msg_ru_RU.properties 

$(OUT)\Msg.properties: $(DEF_RES).properties.utf16.txt
	native2ascii -encoding UTF-16 $(DEF_RES).properties.utf16.txt $(OUT)\Msg.properties 

$(OUT)\Msg_be_BY.properties: Msg_be_BY.properties.utf16.txt
	native2ascii -encoding UTF-16 Msg_be_BY.properties.utf16.txt $(OUT)\Msg_be_BY.properties 

$(OUT)\Msg_en_GB.properties: Msg_en_GB.properties.utf16.txt
	native2ascii -encoding UTF-16 Msg_en_GB.properties.utf16.txt $(OUT)\Msg_en_GB.properties 

$(OUT)\Msg_ru_RU.properties: Msg_ru_RU.properties.utf16.txt 
	native2ascii -encoding UTF-16 Msg_ru_RU.properties.utf16.txt $(OUT)\Msg_ru_RU.properties 

# eof makefile