
from "./modules/std.yara" import std end
from "./modules/math.yara" import math end
from "./modules/logging.yara" import logging end

module program do
	export procedure main in p64 i64 out i64 do
		drop drop
		10 20 30 add3
		69 420 666 add3
		add
		"Hello, World!\n" io.stdout log
		"Hello, World!\n" io.stdout log
		0
	end
end
