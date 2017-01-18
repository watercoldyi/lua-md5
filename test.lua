local md5 = require "lmd5"

print("--test sumhex---")
print(md5.sumhex("123"))

print("--test stream---")
local obj = md5.create()

local f = io.open("./lmd5.so","rb")

local s 
local n = 0
while true do
	s = f:read(4096)
	if not s then 
		break
	end
	n = n + #s
	obj:input(s)
end

print(obj:final(),n)



