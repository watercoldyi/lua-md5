all:
	echo "press os,linux or mingw"
linux:lmd5.so

mingw:lmd5.dll

lmd5.so:md5.c lmd5.c
	gcc -std=c99 -o2 -Wall -fPIC --shared -o $@ $^

lmd5.dll:md5.c lmd5.c
	gcc -std=c99 -o2 -Wall  --shared -o $@ -I/usr/local/include -L/usr/local/bin $^ -llua53
